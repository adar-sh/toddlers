#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

WiFiClient ww;
int i = 0;

void setup() {
 
  Serial.begin(115200);                 //Serial connection
  WiFi.begin("CITTIC Incubates", "CITTIC#TBI#CUSAT");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    Serial.println("Connected");
    i += 1;
 
    HTTPClient http;    //Declare object of class HTTPClient
    Serial.println("http://192.168.0.95:9000/save?data=" + i);
 
    http.begin(ww, "http://192.168.0.95:9000/save?data=" + i);      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
    int httpCode = http.GET();   //Send the request
    String payload = http.getString();                  //Get the response payload
 
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
 
    http.end();  //Close connection
 
  } else {
 
    Serial.println("Error in WiFi connection");
 
  }
 
  delay(3000);  //Send a request every 30 seconds
 
}
