


#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#define BLYNK_PRINT Serial


#include <BlynkSimpleEsp8266.h>
static const int RXPin = 4, TXPin = 5;   
static const uint32_t GPSBaud = 4800;
TinyGPSPlus gps;
WidgetMap myMap(V0);

SoftwareSerial ss(RXPin, TXPin); 
BlynkTimer timer;

float velocity;      
float sats;      
String bearing;  
char token[] = "chIMM_Ho2Jkgyq2Ksqi2gAw35krrS2FP";              
char wifi[] = "CITTIC Incubates";                                       
char pass[] = "CITTIC#TBI#CUSAT";                                      
unsigned int move_index = 1;       


void setup()
{
  Serial.begin(115200);
  Serial.println();
  ss.begin(GPSBaud);
  Blynk.begin(token, wifi, pass);
  timer.setInterval(5000L, checkGPS); 
}

void checkGPS() {
  if (gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    Blynk.virtualWrite(V4, "GPS ERROR");  
  }
}

void loop()
{
  while (ss.available() > 0)
  {
     if (gps.encode(ss.read()))
      displayInfo();
  }
  Blynk.run();
  timer.run();
}

void displayInfo()
{
  if (gps.location.isValid() )
  {
    float latitude = (gps.location.lat());     
    float longitude = (gps.location.lng());

    Serial.print("LATITUDE:  ");
    Serial.println(latitude, 6); 
    Serial.print("LONGITUDE: ");
    Serial.println(longitude, 6);
    Blynk.virtualWrite(V1, String(latitude, 6));
    Blynk.virtualWrite(V2, String(longitude, 6));
    myMap.location(move_index, latitude, longitude, "GPS_Location");
    velocity = gps.speed.kmph();              
    Blynk.virtualWrite(V3, velocity);

    sats = gps.satellites.value();    
    Blynk.virtualWrite(V4, sats);

    bearing = TinyGPSPlus::cardinal(gps.course.value());
    Blynk.virtualWrite(V5, bearing);
  }

  Serial.println();
}
