#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
LiquidCrystal_I2C lcd(0x27,20,4);


int pos = 0;
char control; 
int sensorPin = 10;



void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  lcd.begin(16,2);
  lcd.backlight();
  pinMode(sensorPin, INPUT);
}



void loop() {
  bool level = digitalRead(sensorPin);

  if (level == 1) {
    Serial.println("There is rain!");
    lcd.setCursor(0,0);
    lcd.print("   There is rain! ");
    for (pos = 180; pos >= 0; pos -= 1){ // goes from 180 degrees to 0 degrees
      myservo.write(pos);            // tells servo to go to position 0
      delay(15);  
  }

  else if (level == 0) {
    Serial.println("There is no rain!");
    lcd.setCursor(0,0);
    lcd.print("   There is no rain! ");
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);
    }
  
  delay(1000);
}
