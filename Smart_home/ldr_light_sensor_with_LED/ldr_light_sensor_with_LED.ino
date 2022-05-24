int ldr=A0;
int value=0;
int LED = 3;


void setup() {
Serial.begin(9600);
pinMode(LED,OUTPUT);
}


void loop() {
value=analogRead(ldr);//Reads the Value of LDR(light).
Serial.println("LDR value is :");//Prints the value of LDR to Serial Monitor.
Serial.println(value);
if(value<300)
  {
    digitalWrite(LED,HIGH);//Turns on the light in the dark.
  }
  else
  {
    digitalWrite(LED,LOW);//Turns off the light in light.
  }
}
