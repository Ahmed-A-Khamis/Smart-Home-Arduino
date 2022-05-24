int sensorPin = A0;
int sensorValue = 0;
int buzzer = 12;


void setup() {
pinMode(buzzer,OUTPUT);
Serial.begin(9600);
}



void loop(){
  sensorValue = analogRead(sensorPin);
  
  Serial.println(sensorValue);
  
  if (sensorValue < 100){
    Serial.println("Fire Detected");  
    tone(buzzer, 1000, 200);
    delay(1000);
    }
  else  
    noTone(buzzer);  
    
}
