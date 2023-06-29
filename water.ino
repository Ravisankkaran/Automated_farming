int ACWATERPUMP = 12; //You can remove this line, it has no use in the program.
int sensor = 8; //You can remove this line, it has no use in the program.
int val; //This variable stores the value received from Soil moisture sensor.
void setup() {
  pinMode(12,OUTPUT); //Set pin 13 as OUTPUT pin, to send signal to relay
  pinMode(8,INPUT); //Set pin 8 as input pin, to receive data from Soil moisture sensor.
}
void loop() { 
  val = digitalRead(8);  //Read data from soil moisture sensor  
  if(val == HIGH) 
  {
  digitalWrite(12,HIGH); //if soil moisture sensor provides LOW value send LOW value to relay
  }
  else
  {
  digitalWrite(12,LOW); //if soil moisture sensor provides HIGH value send HIGH value to relay
  }
  delay(400); //Wait for few second and then continue the loop.
}
