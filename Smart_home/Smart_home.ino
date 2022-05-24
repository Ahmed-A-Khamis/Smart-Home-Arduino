
//KEYPAD
void(* resetFunc) (void) = 0;

#include <Keypad.h>



#define Password_Length 8


int signalPin = 12;

char Data[Password_Length];
char Master[Password_Length] = "1234567";
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {38, 40, 42, 44};
byte colPins[COLS] = {46, 48, 50, 52};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);




/////////////////////////////////////////////////////////////////////////////////////////







// flame with buzzer
int flame = 1;
int flameValue = 0;
int buzzer = 12;
/////////////////////////////////////////////////////////////////////////////////////////

//temp with fan
int temp;
int tempPin = 3;
int fan = 3;
/////////////////////////////////////////////////////////////////////////////////////////

// ldr with led
bool light = 1;
int ldr = 2;
int ldrValue = 0;
int LED = 4;
/////////////////////////////////////////////////////////////////////////////////////////

//smoke with buzzer
//int buzzer = 10;
int smoke = 0;
// Your threshold value
int smokeSensorThres = 100;
/////////////////////////////////////////////////////////////////////////////////////////

//water with servo with lcd
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
LiquidCrystal_I2C lcd(0x27, 20, 4);

bool cover = 1;
int pos = 0;
char control;
int water = 10;
/////////////////////////////////////////////////////////////////////////////////////////

//pir with led
int ledPin = 13;                // LED
int pirPin = 5;                 // PIR Out pin
int pirStat = 0;                   // PIR status
/////////////////////////////////////////////////////////////////////////////////////////



void setup() {
  // flame with buzzer
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  /////////////////////////////////////////////////////////////////////////////////////////

  //temp with fan
  pinMode(tempPin, INPUT);
  pinMode(fan, OUTPUT);
  /////////////////////////////////////////////////////////////////////////////////////////

  // ldr with led
  pinMode(LED, OUTPUT);
  /////////////////////////////////////////////////////////////////////////////////////////

  //smoke with buzzer
  pinMode(buzzer, OUTPUT);
  pinMode(smoke, INPUT);
  /////////////////////////////////////////////////////////////////////////////////////////

  //water with servo with lcd
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  lcd.init();
  lcd.init();
  lcd.backlight();
  pinMode(water, INPUT);
  /////////////////////////////////////////////////////////////////////////////////////////

  //pir with led
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  /////////////////////////////////////////////////////////////////////////////////////////

  //KEYPAD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password");
  lcd.setCursor(0, 1);
  lcd.print("Press A to start");
  customKeypad.waitForKey();
  lcd.clear();
  while (data_count != Password_Length - 1) {
    customKey = customKeypad.getKey();

    if (customKey) {
      Data[data_count] = customKey;
      Serial.println(Data[data_count]);
      lcd.setCursor(data_count, 0);
      lcd.print(Data[data_count]);
      data_count++;
    }
    if (data_count == Password_Length - 1) {
      if (!strcmp(Data, Master)) {
        Serial.println("Correct");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Access Granted!");
        delay(2000);

      }
      else {
        Serial.println("Incorrect");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Access denied!");
        delay(2000);
        resetFunc();
      }
    }
  }
  clearData();
  /////////////////////////////////////////////////////////////////////////////////////////
}




void loop() {

  // flame with buzzer
  flameValue = analogRead(flame);
  Serial.print("flame= ");
  Serial.println(flameValue);

  if (flameValue < 100) {
    Serial.println("Fire Detected");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fire detected!");
    tone(buzzer, 100);
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Fire");
    noTone(buzzer);
  }
  delay(1000);

  /////////////////////////////////////////////////////////////////////////////////////////


  //temp with fan
  temp = analogRead(tempPin);
  float mv = ( temp / 1024.0) * 5000;
  float cel = mv / 10;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TEMPRATURE = ");
  lcd.print(cel);
  lcd.print(" C");
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print(" C");
  Serial.println();
  delay(1000);

  if ( cel > 25 ) {
    digitalWrite(fan, HIGH); //Turns on the fan when temperature is high
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fan On");
  }

  else {
    digitalWrite(fan, LOW); //Turns off the fan when temperature is low
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fan Off");
  }
  delay(1000);

  /////////////////////////////////////////////////////////////////////////////////////////

  // ldr with led
  ldrValue = analogRead(ldr); //Reads the Value of LDR(light).
  Serial.print("LDR value is :");//Prints the value of LDR to Serial Monitor.
  Serial.println(ldrValue);
  if (ldrValue > 300)
  {
    digitalWrite(LED, HIGH); //Turns on the light in the dark.
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Night time");
    Serial.println("Night time");
    if (light == 0) {
      lcd.setCursor(0, 1);
      lcd.print("Night lights off!");
      Serial.println("Night lights off!");
      light = 1;
    }
  }
  else
  {
    digitalWrite(LED, LOW); //Turns off the light in light.
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Day time");
    Serial.println("Day time");
    if (light == 1) {
      lcd.setCursor(0, 1);
      lcd.print("Night lights on!");
      Serial.println("Night lights on!");
      light = 0;
    }
  }
  delay(1000);

  /////////////////////////////////////////////////////////////////////////////////////////


  //Smoke with buzzer
  int analogSensor = analogRead(smoke);

  Serial.print("smoke: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > smokeSensorThres) {
    tone(buzzer, 100);
    digitalWrite(buzzer, 1);
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Smoke Detected!");
    Serial.println("Smoke Detected!");
  }
  else {
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Smoke");
  }
  delay(1000);
  /////////////////////////////////////////////////////////////////////////////////////////

  //water with servo with lcd
  bool level = digitalRead(water);

  if (level == 0) {
    Serial.println("There is rain!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("There is rain!");
    if (cover == 0) {
      lcd.setCursor(0, 1);
      lcd.print("Deploying Cover");
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);            // tells servo to go to position 0
        delay(15);
      }
      cover = 1;
    }
  }

  else if (level == 1) {
    Serial.println("There is no rain!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("There is no rain!");
    if (cover == 1) {
      lcd.setCursor(0, 1);
      lcd.print("Retracting Cover");
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);
      }
      cover = 0;
    }
  }
  delay(1000);

  /////////////////////////////////////////////////////////////////////////////////////////

  //pir with led
  pirStat = digitalRead(pirPin);
  if (pirStat == HIGH) {            // if motion detected
    digitalWrite(ledPin, HIGH);  // turn LED ON
    Serial.println("Hey I got you!!!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Movement Detected!");
  }

  else {
    digitalWrite(ledPin, LOW); // turn LED OFF if we have no motion
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Movement");
  }

  delay(1000);

  /////////////////////////////////////////////////////////////////////////////////////////

  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
}



//KEYPAD
void clearData() {
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
  return;
}
