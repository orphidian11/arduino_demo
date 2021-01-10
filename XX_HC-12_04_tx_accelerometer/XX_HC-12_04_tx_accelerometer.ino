/**
 * https://www.youtube.com/watch?v=vqRqtgvltOI&t=490s
 * HC-12 
 * Transmit angle captured from MPU-6050 accelerometer
 * 
 * ==========
 * = PINOUT =
 * ==========
 * Arduino GND
 * - to HC-12 GND
 * - to MPU-6050 GND
 * 
 * Arduino 5V
 * - to HC-12 GND
 * - to MPU-6050 GND
 * 
 * Arduino D11 
 * - to HC-12 RX
 * 
 * Arduino D10
 * - to HC-12 TX
 * 
 * Arduino D5
 * - to 220 ohm resistor + green LED
 * 
 * Arduino D4
 * - to 220 ohm resistor + yellow LED
 * 
 * Arduino D3
 * - to 220 ohm resistor + red LED
 * 
 * Arduino D2
 * - to MPU-6050 INT
 * 
 * Arduino A4
 * - to MPU-6050 SDA
 * 
 * Arduino A5
 * - to MPU-6050 SCL
 */

#include <SoftwareSerial.h>
#include <Wire.h>

#define HC12_TX 10
#define HC12_RX 11
#define RED_PIN 3
#define YEL_PIN 4
#define GRN_PIN 5

// MPU-6050 address
const int MPU6050_ADDR = 0x68; 
int outputValuesEveryX = 100;

const int calNum = 1000; // number of times to run calibration on setup
const float gyroAngleCalc = 0.0000611; // 0.0000611 = 1 / (250Hz x 65.5)
const float gyroAngleXferCalc = 0.0000611; // 0.000001066 = 0.0000611 * (3.142(PI) / 180degr) The Arduino sin function is in radians
const float accAngleCalc = 57.296;  // 57.296 = 1 / (3.142 / 180) The Arduino asin function is in radians

// gyroscope
int gyroX, gyroY, gyroZ;
long gyroXCal, gyroYCal, gyroZCal;
boolean setGyroAngles;

// accelerometer
long accX, accY, accZ, accVectorT;
float angleRollAcc, anglePitchAcc;

float finalAnglePitch, finalAngleRoll, anglePitch, angleRoll;
int anglePitchBuff, angleRollBuff;
float anglePitchOut, angleRollOut;

long loopTimer;
int temp;

int displayCtr = 0;

SoftwareSerial hc12(HC12_TX,HC12_RX); 

/**********************BEGIN SETUP***********************/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
//  hc12.begin(9600);
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(YEL_PIN, OUTPUT);
  pinMode(GRN_PIN, OUTPUT);

  setupMpu6050Registers();
  calibrateMpu6050();

  loopTimer = micros(); // time since arduino startup
}
/*********************END SETUP**************************/

/**********************BEGIN LOOP************************/
void loop() {
  // put your main code here, to run repeatedly:

  // LED is always ON to maintain power draw 
  // and prevent power bank from auto-shutoff
  digitalWrite(RED_PIN, HIGH); 
  digitalWrite(YEL_PIN, HIGH); 
  digitalWrite(GRN_PIN, HIGH); 

  // capture MPU-6050 data
  readMpu6050Data();
  computeMpu6050Data();

  Serial.print("Pitch: " + String(finalAnglePitch));
  Serial.print("Roll: " + String(finalAngleRoll));
  Serial.println();
  
  // transmit
//  hc12.write("hello from the other side\r\n");
//  delay(2000);
}
/*********************END LOOP***************************/

/******************BEGIN INTERNAL FUNCTIONS**************/

/**
 * Compute MPU-6050 data
 * Computed values for pitch angle are stored in global variable finalAnglePitch
 * Computed values for roll angle are stored in global variable finalAngleRoll;
 */
void computeMpu6050Data(){
  // GYRO ANGLE CALCULATIONS
  // adjust the captured values using the calibration values
  gyroX -= gyroXCal;
  gyroY -= gyroYCal;
  gyroZ -= gyroZCal;

  anglePitch += gyroX * gyroAngleCalc;
  angleRoll += gyroY * gyroAngleCalc;

  anglePitch += angleRoll * sin(gyroZ * gyroAngleXferCalc);
  angleRoll += anglePitch * sin(gyroZ * gyroAngleXferCalc);

  // ACCELEROMETER ANGLE CALCULATIONS
  accVectorT = sqrt((accX * accX) + (accY * accY) + (accZ * accZ));
  anglePitchAcc = asin((float) accY / accVectorT) * accAngleCalc;
  angleRollAcc = asin((float) accX / accVectorT) * -(accAngleCalc);

  // calibrate
  anglePitchAcc -= 0.0;
  angleRollAcc -= 0.0;

  // adjustments on startup
  if (setGyroAngles){
    // system is already running
    anglePitch = anglePitch * 0.9996 + anglePitchAcc * 0.0004;
    angleRoll = angleRoll * 0.9996 + angleRollAcc * 0.0004;
  } else {
    // system has just started
    anglePitch = anglePitchAcc;
    angleRoll = angleRollAcc;
    setGyroAngles = true;
  }

  // dampen pitch and roll angles
  // take 90% from value and add 10% of raw value
  anglePitchOut = (anglePitchOut * 0.9) + (anglePitch * 0.1);
  angleRollOut = (angleRollOut * 0.9) + (angleRoll * 0.1);

//  displayCtr++;

  // display only after every X measurements
//  if (displayCtr > outputValuesEveryX){
    finalAnglePitch = anglePitchOut;
    finalAngleRoll = angleRollOut;
//    displayCtr = 0; // reset the counter
//  }

  while(micros() - loopTimer <  4000);
  loopTimer = micros();
}

/**
 * Calibrate MPU-6050 before using. Get the average of 1000 
 * readings as calibration data when reading the values
 */
void calibrateMpu6050(){
  // calibrate gyro. read acc and gyro data 1000 times
  for (int x = 0; x < calNum; x++){
    readMpu6050Data();

    gyroXCal += gyroX;
    gyroYCal += gyroY;
    gyroZCal += gyroZ;

    delay(3);
  }

  // get the average
  gyroXCal /= calNum;
  gyroYCal /= calNum;
  gyroZCal /= calNum;
}

/**
 * Setup MPU-6050 sensor
 */
void setupMpu6050Registers(){
  // Activate MPU-6050
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  // Configure accelerometer
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();

  // Configure gyro
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();
}

/**
 * Capture raw MPU-6050 data
 */
void readMpu6050Data(){
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission();

  // request 14 bytes. wait until all are received
  Wire.requestFrom(MPU6050_ADDR, 14);
  while(Wire.available() < 14);

  accX = Wire.read() << 8 | Wire.read();
  accY = Wire.read() << 8 | Wire.read();
  accZ = Wire.read() << 8 | Wire.read();
  
  temp = Wire.read() << 8 | Wire.read();

  gyroX = Wire.read() << 8 | Wire.read();
  gyroY = Wire.read() << 8 | Wire.read();
  gyroZ = Wire.read() << 8 | Wire.read();
}

/******************END INTERNAL FUNCTIONS****************/
