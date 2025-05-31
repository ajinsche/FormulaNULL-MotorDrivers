#include <Arduino.h>

//Motor pin declarations
int en_A{13};             //Speed control for the motor
int in1_A{12};            //Forward control for the motor
int in2_A{11};            //Backwards control for the motor
int chl1{10};             //reading values for power channel for the motor

int va_pwm{0};            //reading pwm ranging
int va_low{1470};         //low value of the undefined range
int va_high{1530};        //high value of the undefined range
int va2_pwm{0};           //value after calculations done on it
int lowest{1000};         //highest value for the receiver
int highest{2000};        //lowest value for the receiver 

void setup() {
  //Setup the motor control pins to output and the power channel to input
  pinMode(en_A, OUTPUT);
  pinMode(in1_A, OUTPUT);
  pinMode(in2_A, OUTPUT);
  pinMode(chl1, INPUT);

  //Turning all the motors to LOW to begin with
  digitalWrite(in1_A, LOW);
  digitalWrite(in2_A, LOW);

  Serial.begin(9600);
}

// put function definitions here:
void directionControl(){
  if (va2_pwm >= 0) {
    digitalWrite(in1_A, LOW);
    digitalWrite(in2_A, HIGH);
    analogWrite(en_A, va2_pwm);
  } else {
    digitalWrite(in1_A, HIGH);
    digitalWrite(in2_A, LOW);
    analogWrite(en_A, -(va2_pwm));
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

  directionControl();
}

