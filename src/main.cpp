#include <Arduino.h>

int en_A1{9};
int in_A1{8};
int in_A1{7};

int en_A2{6};
int in_A2{5};
int in_A2{4};

int en_B1{3};
int in_B1{2};
int in_B1{1};

int en_B2{0}


// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}