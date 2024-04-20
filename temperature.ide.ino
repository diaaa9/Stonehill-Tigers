#define BLYNK_TEMPLATE_ID "TMPL327PCf4FD"
#define BLYNK_TEMPLATE_NAME "Ventilation dashboard"
#include <Blynk>
#include <ESP8266WiFi.h>
#include <PulseSensorPlayground.h>

const int PULSE_SENSOR_PIN = 0;  // Analog PIN where the PulseSensor is connected
const int THRESHOLD = 550;  

PulseSensorPlayground pulseSensor;

char auth[] = "CjKntDt9Mp3HEzpuvPZZNYo-A_cIjqcy";
char ssid[] = "Posiedon"; 
char pass[] = "123qweas";            

void setup()
{
  Serial.begin(115200);    

  pulseSensor.analogInput(PULSE_SENSOR_PIN);
  pulseSensor.setThreshold(THRESHOLD);

  if (pulseSensor.begin()) 
  {
    Serial.println("PulseSensor object created successfully!");
  }        

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  int currentBPM = pulseSensor.getBeatsPerMinute();
 
  // Check if a heartbeat is detected
  if (pulseSensor.sawStartOfBeat()) 
  {
    Serial.println("♥ A HeartBeat Happened!");
    Serial.print("BPM: ");
    Serial.println(currentBPM);
  }
 
  // Add a small delay to reduce CPU usage
  delay(20);

  Blynk.virtualWrite(V0, currentBPM);
  Blynk.run();
  delay(500);
}