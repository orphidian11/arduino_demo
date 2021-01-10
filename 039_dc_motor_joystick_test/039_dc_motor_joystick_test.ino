/**
 * https://www.youtube.com/watch?v=wSjZIHMDczk&list=PLQJqki0RCuBsA2Gk_KRSY8kKNXzXGadHy&index=4
 * 
 * ========================================
 * MOTOR TESTING CODE
 * ========================================
 * DC Motor with L293D driver plus Joystick
 * Control 2 DC motors using a joystick
 * 
 * 1. When joystick is at neutral position, both wheels stop
 * 
 * 2. When joystick tilts forward, both wheels turn forward
 * Inputs
 * - Y < neutral range
 * Outputs
 * - L and R motor forward is HIGH(?)
 * - L and R motor reverse is LOW(?)
 * - As Y goes down, L and R motor speed goes up
 * - As Y goes up, L and R motor speed goes down
 *  
 * 3. When joystick tilts backward, both weels turn backward
 * Inputs
 * - Y > neutral range
 * Outputs
 * - L and R motor forward is LOW(?)
 * - L and R motor reverse is HIGH(?)
 * - As Y goes up, L and R motor speed goes up
 * - As Y goes down, L and R motor speed goes down
 * 
 * 5. When joystick tilts left, left wheel stops and right wheel runs
 * Inputs
 * - X  < neutral range
 * Outputs
 * - As X goes down, L motor speed reduction increases
 * - As X goes up, L motor speed reduction decreases
 * 
 * 6. When joystick tilts right, left wheel runs and right wheel stops
 * Inputs
 * - X  > neutral range
 * Outputs
 * - As X goes up, R motor speed reduction increases
 * - As X goes down, R motor speed reduction decreases
 * 
 * 7. When joystick button is pressed, sound the buzzer (BONUS)
 * Inputs
 * - Joystick button 
 * Outputs
 * - When 0 beep
 * - When 1 stop
 * 
 */

/** PIN CONFIG **/
// Left Motor pins
#define L_SPD_PIN 6
#define L_FWD_PIN 7
#define L_REV_PIN 8

// Right Motor pins
#define R_SPD_PIN 11
#define R_FWD_PIN 10
#define R_REV_PIN 9

// Joystick pins
#define J_X_PIN A0
#define J_Y_PIN A1
#define J_BTN_PIN 2

/** CONSTANTS **/
// joystick neutral range tolerance 
const float jNeutralMin = 498;
const float jNeutralMax = 501;

// joystick ranges
const float jMin = 0;
const float jMax = 1023;

// motor speed ranges
const float spdStop = 0;
const float spdMin = 100;
const float spdMax = 255;
const float spdReduxMin = 0;
float spdReduxMax;
const int kickDelay = 10;

/** INPUTS **/
int xV; // x-axis
int yV; // y-axis
int jV; // button push (0: down, 1: up)

// slope value
float mSpd;
float mSpdRedux;

/** OUTPUTS **/
int lSpd;
int lSpdRedux = 0;
int rSpd;
int rSpdRedux = 0;

int lFwdPin;
int lRevPin;
int rFwdPin;
int rRevPin;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(J_X_PIN, INPUT);
  pinMode(J_Y_PIN, INPUT);
  pinMode(J_BTN_PIN, INPUT_PULLUP);

  lSpd = rSpd = spdStop;
  lSpdRedux = rSpdRedux = 0;

  lFwdPin = rFwdPin = HIGH;
  lRevPin = rRevPin = LOW;
}

void loop() {
  // put your main code here, to run repeatedly:

  /** OUTPUT **/
  lSpd = spdMax;
  lSpdRedux = 0;
  digitalWrite(L_FWD_PIN, lFwdPin);
  digitalWrite(L_REV_PIN, lRevPin);
  if ((lSpd - lSpdRedux) > 0){
    analogWrite(L_SPD_PIN, spdMax); // a little kick
    delay(kickDelay);
  }
  analogWrite(L_SPD_PIN, lSpd - lSpdRedux);
  
  // Right Motor pins
  rSpd = spdMax;
  rSpdRedux = 0;
  digitalWrite(R_FWD_PIN, rFwdPin);
  digitalWrite(R_REV_PIN, rRevPin);
  if ((rSpd - rSpdRedux) > 0){
    analogWrite(R_SPD_PIN, spdMax); // a little kick
    delay(kickDelay);
  }
  analogWrite(R_SPD_PIN, rSpd - rSpdRedux);

  Serial.print("x,y,z = [" + String(xV) + "," + String(yV) + "," + String(jV) + "] => ");
//  Serial.print("L,R = [" + String(lSpd) + "," + String(rSpd) + "] ");
//  Serial.print("Lr,Rr = [" + String(lSpdRedux) + "," + String(rSpdRedux) + "] ");
  Serial.print("Lf,Rf = [" + String(lSpd - lSpdRedux) + "," + String(rSpd - rSpdRedux) + "] ");
  Serial.print("LDir,RDir = [(" + String(lFwdPin) + "," + String(lRevPin) + "),(" + String(rFwdPin) + "," + String(rRevPin) + ")]");
//  Serial.print(String(mFwd) + ":" + String(mRev));
  Serial.println();
}
