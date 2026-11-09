#include <Arduino.h>
#include <ESP32Servo.h>
#include "pinDefontions.h"

//  function declarations  //
int averageRead(int pin){
  // takes 8 readings and averages them to allow for smooth readings
  int sum=0;
  for(int i=0; i < 8;i++ ){
    sum += analogRead(pin);
  }
  return sum/8;

};
//  class declartions //
Servo servoBase, servoOne, servoTwo,servoThree;

//  global vars //
unsigned long int outputTimer(0), curTime;
const int ADC_MAX(4095); // This is the default ADC max value on the ESP32 (12 bit ADC width);
                        // this width can be set (in low-level oode) from 9-12 bits, for a
                        // a range of max values of 512-4096
                        //SOURCED FROM LIBRARY GITHUB REPO

  

void setup() {
  Serial.begin(115200);

  analogSetAttenuation(ADC_11db); //allows full 3.3v readings from the gpio pins

  servoBase.attach(servoPin1);
  servoOne.attach(servoPin2);
  servoTwo.attach(servoPin3);
  servoThree.attach(servoPin4);
  Serial.print("\n\nBot Started >;)... \n\n");
  delay(100);
}

void loop() {
  curTime = millis();

  int baseReading = averageRead(potPin1);
  int OneReading = averageRead(potPin2);
  int TwoReading = averageRead(potPin3);
  int ThreeReading = averageRead(potPin4);

  int baseAngle = map(baseReading, 0, ADC_MAX, 0, 180);
  int oneAngle = map(OneReading, 0, ADC_MAX, 0, 180);
  int twoAngle = map(TwoReading, 0, ADC_MAX, 0, 180);
  int threeAngle = map(ThreeReading, 0, ADC_MAX, 0, 180);

  servoBase.write(baseAngle);
  servoOne.write(oneAngle);
  servoTwo.write(twoAngle);
  servoThree.write(threeAngle);

  if(curTime - outputTimer >= 1000){
    //timer to output readings and outputs...
    Serial.printf("  ---  POT READINGS  --- \nbase angle pot reading: %d. \npot one reading: %d. \npot two reading: %d. \npot three reading %d\n\n",baseReading,OneReading,TwoReading,ThreeReading);
    Serial.printf("  ---  SERVO OUTPUTS --- \nbase servo output: %d.\nservo one output: %d. \nservo two reading: %d. \nservo three reading: %d.\n\n",baseAngle,oneAngle,twoAngle,threeAngle);
    outputTimer = millis();
  }
}


// Servo s[4];
// const int pins[4] = {servoPin1, servoPin2, servoPin3, servoPin4};

// void setup() {
//   Serial.begin(115200);
//   for (int i = 0; i < 4; i++) s[i].attach(pins[i]);
//   delay(1000);
// }

// void loop() {
//   for (int i = 0; i < 4; i++) {
//     Serial.printf("Moving GPIO %d only\n", pins[i]);
//     s[i].write(30);  delay(1000);
//     s[i].write(150); delay(1000);
//     s[i].write(90);  delay(1500);
//   }
// }
