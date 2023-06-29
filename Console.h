#include <ESP8266WiFi.h>
#include <Servo.h>
Servo s1,s2,s3,s4;
 
const char* ssid = "OnePlus Nord2 5G";
const char* password = "sibi12345";
int pos,i=0;  
void recu();

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
  s1.attach(16); //Gpio-2 of nodemcu with pwm pin of servo motor
  s2.attach(5);
  s3.attach(2);
  s4.attach(14);
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address on serial monitor
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");    //URL IP to be typed in mobile/desktop browser
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

 int value = 0;
 // Match the request

if (request.indexOf("/s1=0") != -1)  {
  s1.write(0); //Moving servo to 0 degree
  value=0;
}

if (request.indexOf("/s1=90") != -1)  { 
  s1.write(90); //Moving servo to 180 degree
  value=90;
} 


if (request.indexOf("/s3=start") != -1)  
{
while(i<10)
{
for(pos=0;pos<=90;pos++){
s3.write(pos);
}
delay(750);
for(pos=90;pos>=0;pos--){
s3.write(pos);
}
delay(750);
i++;
}

}

if (request.indexOf("/s3=stop") != -1)  { 
  server.begin(); //Moving servo to 180 degree
}

if (request.indexOf("/s4=0") != -1)  {
  s4.write(0); //Moving servo to 0 degree
  value=0;
}

if (request.indexOf("/s4=1") != -1)  { 
  s4.write(0); //Moving servo to 180 degree
  value=0;
}

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<h1 align=center>FARM AUTOMATION over WiFi</h1><br><br>");
  client.println("<br><br>");
  client.println("<h1 align=left>PLOUGHING</h1><br><br>");
  client.println("<a href=\"/s1=0\"\"><button>UP</button></a>");
  client.println("<a href=\"/s1=90\"\"><button>DOWN</button></a><br/>");
  client.println("<br><br>");
  client.println("<h1 align=left>SOWING</h1><br><br>");
  client.println("<a href=\"/s3=start\"\"><button>Start</button></a>");
  client.println("<a href=\"/s3=stop\"\"><button>Stop</button></a><br/>");
  client.println("<br><br>");
  client.println("<h1 align=left>ROBOT</h1><br><br>");
  client.println("<a href=\"/s4=1\"\"><button>START</button></a>");
  client.println("<a href=\"/s4=0\"\"><button>STOP</button></a><br/>");

  client.println("</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
