// #include <Arduino.h>

#include "main.h"

//Motor pin declarations           
int va_pwm{0};                             //reading pwm ranging
float va_L_pwm{0};                            //value after calculations done on it
float va_R_pwm{0};                         //speed value for the second motor with different rpm (shifted from an unknown RPM to 25000rpm)
float ratio_LR{1};                       //ratio that pwmB is being shifted by (assuming that the unknown rpm is 33000)



int va_low{1440};                          //low value of the undefined range
int va_high{1560};                         //high value of the undefined range
int lowest{970};                           //highest value for the receiver
int highest{1940};                         //lowest value for the receiver 

int map_high{255};
int map_low{50};


//controls for changing directions 

bool curr_dir{true};                       //current direction, where true is forwards and false is backwards 
bool prev_dir{true};                       //previous direction

void setup() {
  //Setup the motor control pins to output and the power channel to input
  pinMode(EN_L_PIN, OUTPUT);
  pinMode(in1_A, OUTPUT);
  // pinMode(in2_A, OUTPUT);
  pinMode(EN_R_PIN, OUTPUT);
  pinMode(chl1, INPUT);

  //Turning all the motors to LOW to begin with
  digitalWrite(in1_A, LOW);
  // digitalWrite(in2_A, LOW);


  // bool checkSwitch();
  // checkSwitch();
  Serial.begin(9600);                   //TESTING, COMMENT OUT LATER
  // va_pwm = 1000;                     //TESTING, COMMENT OUT LATER
}

bool checkSwitch(){
  prev_dir = curr_dir;
  if (va2_pwm >= 0){
    curr_dir = true;
  } else {
    curr_dir = false;
  } 
  if (curr_dir != prev_dir){ 
    return true;
  } else{
    return false;
  }
}

// TESTING, COMMENT OUT LATER
void testSpeed(){            
  delay(10);

//     //speed tests
Serial.print("input value is: ");
Serial.println(va_pwm);
Serial.print("speed A is: ");
Serial.println(va2_pwm);
Serial.print("speed B is: ");
Serial.println(va2_pwmB);
//     //direction tests
Serial.print("current direction is: ");
Serial.println(curr_dir);
//     Serial.print("previous direction was: ");
//     Serial.println(prev_dir);
//     Serial.print("check switch triggered: ");
//     Serial.println(checkSwitch());
   
}

//remaking basic functions for cpp 
int map(int input, int low_in, int high_in, int low_out, int high_out){
  return output;
}

long constrain(long input, long low_bounds, long high_bounds){

}

void digitalWrite(int pin, bool value){

}

void analogWrite(int pin, int value){

}

unsigned long pulseIn(int pin, bool value, long timeout){
  if(pin == value){
    while()
  }
  
  return ;
}

void serialPrint(){


}

float pulseOut(){
  HAL_UART_Transmit_IT()

}




void relaySwitch(bool relayState){
  analogWrite(EN_L_PIN, 0);
  analogWrite(EN_R_PIN, 0);

  if (relayState != false) {
    digitalWrite(in1_A, true);
  } else {
    digitalWrite(in1_A, false);
  }
  
}

void vectorControl(){
  if (va2_pwm >= 0) {
    analogWrite(EN_L_PIN, va2_pwm);            //writing the speed when it is forwards
    analogWrite(EN_R_PIN, va2_pwmB);

  } else {
    analogWrite(EN_L_PIN, -(va2_pwm));         //writing the speed when it is backwards
    analogWrite(EN_R_PIN, -(va2_pwmB)); 
  }
}

void loop() {
  testSpeed();                          //TESTING, COMMENT OUT LATER

  va_pwm = pulseIn(chl1, true, 25000);     //recording the pulse width from 1000 to 2000
  va_pwm = constrain(va_pwm, lowest, highest);
  
  //code to normalize the recorded pulse width between (0, 255)
  if (va_pwm == 0 || (va_pwm > va_low && va_pwm < va_high)){
    va2_pwm = 0;
    va2_pwmB =0;
} else{
    if (va_pwm >= va_high){
      va2_pwm  = map(va_pwm, va_high, highest, map_low, map_high);
      va2_pwm = constrain(va2_pwm, map_low, map_high);
      va2_pwmB = map(va_pwm, va_high, highest, map_low, map_highB);
      va2_pwmB = constrain(va2_pwmB, map_low, map_highB);
  } else {
      va2_pwm  = map(va_pwm, lowest, va_low, -(map_high), -(map_low));
      va2_pwm = constrain(va2_pwm, -(map_high), -(map_low));
      va2_pwmB = map(va_pwm, lowest, va_low, map_lowB, -(map_low));
      va2_pwmB =constrain(va2_pwm, map_lowB, -(map_low));
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

