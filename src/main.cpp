#include <Arduino.h>

//Motor 1 pin declarations
int en_A{6};             //Digital PWM pin -> speed control for the motor
int en_B{5};

//Polarity control for the motors
int in1_A{10};           //Forward control pin for the motor
// int in2_A{11};           //Backwards control pin for the motor

int chl1{9};              //reading values for power channel for the motor

int va_pwm{0};            //reading pwm ranging
int va2_pwm{0};           //value after calculations done on it

int va_low{1475};         //low value of the undefined range
int va_high{1525};        //high value of the undefined range
int lowest{1000};         //highest value for the receiver
int highest{2000};        //lowest value for the receiver 

bool gate_power{true};
bool curr_dir{true};          //current direction, where true is forwards and false is backwards 
bool prev_dir{true};          //previous direction

void setup() {
  //Setup the motor control pins to output and the power channel to input
  pinMode(en_A, OUTPUT);
  pinMode(in1_A, OUTPUT);
  // pinMode(in2_A, OUTPUT);
  pinMode(en_B, OUTPUT);
  pinMode(chl1, INPUT);

  //Turning all the motors to LOW to begin with
  digitalWrite(in1_A, LOW);
  // digitalWrite(in2_A, LOW);  
}

bool checkSwitch(){
  prev_dir == curr_dir;
  if (va2_pwm > 0){
    curr_dir == true;
  } else {
    curr_dir == false;
  } 
  if (curr_dir != prev_dir){ 
    return true;
  } else{
    return false;
  }
}

void relaySwitch(bool relayState){
  gate_power = false;
  if (relayState != false) {
    digitalWrite(in1_A, HIGH);
  
  } else {
    digitalWrite(in1_A, LOW);
  }

  delay(1);
  gate_power = true;
}

// put function definitions here:
void vectorControl(){
  if (va2_pwm >= 0) {
    analogWrite(en_A, va2_pwm);        //writing the speed when it is forwards
    analogWrite(en_B, va2_pwm);

  } else {
    analogWrite(en_A, -(va2_pwm));     //writing the speed when it is backwardss
    analogWrite(en_B, -(va2_pwm)); 
  }
}

void loop() {
  //recording the pulse width from 1000 to 2000
  va_pwm = pulseIn(chl1, HIGH, 10000);

  //code to normalize the recorded pulse width between (0, 255)  
  if (va_pwm == 0 || (va_pwm > va_low && va_pwm < va_high)){
    va2_pwm = 0;
  } else{
    if (va_pwm >= va_high){
      va2_pwm = map(va_pwm, va_high, highest, 0, 255);
    } else {
      va2_pwm = map(va_pwm, lowest, va_low, -255, 0);
    }
  } 
 
  if (checkSwitch() != false){
    if (va2_pwm >= 0) {
      relaySwitch(true);
    } else {
      relaySwitch(false);
    }
  }
vectorControl(); 
}

