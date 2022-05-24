int val;
int tempPin = 3;
int fan = 3;


void setup(){
  Serial.begin(9600);
  pinMode(fan, OUTPUT);
}


void loop(){
  val = analogRead(A3);
  float mv = ( val/1024.0)*5000;
  float cel = mv/10;
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();

  if( cel > 25 )
    digitalWrite(fan, HIGH); //Turns on the fan when temperature is high

  else
    digitalWrite(fan, LOW); //Turns off the fan when temperature is low
  
  delay(1000);
}
