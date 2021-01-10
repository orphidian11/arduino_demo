/**
 * https://www.youtube.com/watch?v=XCyRXMvVSCw
 * https://dronebotworkshop.com/mpu-6050-level/
 * 
 * MPU-6050 Accelerometer and Gyroscope
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LED_RED_NEG 9
#define LED_YEL_NEG 10
#define LED_GRN 11
#define LED_YEL_POS 12
#define LED_RED_POS 13

// i2c to lcd pinout
const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

// LCD i2c adapter address
const int LCD_I2C_ADDR = 0x27;

// MPU-6050 address
const int MPU6050_ADDR = 0x68;

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

float anglePitch, angleRoll;
int anglePitchBuff, angleRollBuff;
float anglePitchOut, angleRollOut;

long loopTimer;
int temp;

int outputValuesEveryX = 100;
int displayCtr = 0;

LiquidCrystal_I2C lcd(LCD_I2C_ADDR, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

void setup() {
  // Start i2c
  Wire.begin();
  
  // put your setup code here, to run once:
  lcd.begin(16,2); // 16 cols, 2 rows

  pinMode(LED_RED_NEG, OUTPUT);
  pinMode(LED_YEL_NEG, OUTPUT);
  pinMode(LED_GRN, OUTPUT);
  pinMode(LED_YEL_POS, OUTPUT);
  pinMode(LED_RED_POS, OUTPUT);

  setupMpu6050Registers();

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

//  Serial.begin(115200);

  loopTimer = micros(); // time since arduino startup
}

void loop() {
  // put your main code here, to run repeatedly:
  readMpu6050Data();

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

  displayCtr++;

  // display only after every X measurements
  if (displayCtr > outputValuesEveryX){
    lcd.clear();
    
    lcd.setCursor(0,0);
    lcd.print("Pitch: ");
    lcd.print(anglePitchOut);
    
    lcd.setCursor(0,1);
    lcd.print("Roll: ");
    lcd.print(angleRollOut);

    displayCtr = 0; // reset the counter
  }

  while(micros() - loopTimer <  4000);
  loopTimer = micros();
}

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
