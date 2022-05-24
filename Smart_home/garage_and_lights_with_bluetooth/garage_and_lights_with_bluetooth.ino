#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int light1 = 5;
bool L1 = 0;
int light2 = 6;
bool L2 = 0;
int light3 = 7;
bool L3 = 0;

int pos = 0;
String control;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
  control = Serial.read();
  if( control == "GO"){ // Garage Open
    for (pos = 180; pos >= 0; pos -= 1){ // goes from 180 degrees to 0 degrees
      myservo.write(pos);            // tells servo to go to position 0
      delay(15);                     // waits 15ms for the servo to reach the position
    }
  }
  else if( control == "GC" ){ // Garage Close
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }

  if( control == "L1" ){
    L1 = !L1; //Changes the state of L1 bool variable to switch light
    digitalWrite(light1, L1);
  }
  
  if( control == "L2" ){
    L1 = !L2; //Changes the state of L2 bool variable to switch light
    digitalWrite(light2, L2);
  }
  
  if( control == "L3" ){
    L1 = !L3; //Changes the state of L3 bool variable to switch light
    digitalWrite(light3, L3);
  }

  
}
