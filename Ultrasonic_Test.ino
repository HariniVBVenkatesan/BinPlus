#include <WiFi.h>
#include "HX711.h"

//===================== PIN DEFINITIONS =====================

// Ultrasonic Sensor
#define TRIG_PIN 5
#define ECHO_PIN 18

// HX711
#define DT 4
#define SCK 2

// Buzzer
#define BUZZER_PIN 14

// LEDs

#define GREEN_LED 26
#define RED_LED 27

//===========================================================
// WiFi Credentials
//===========================================================

const char* ssid = "VB";
const char* password = "harini@2006";

//===========================================================
// Settings
//===========================================================

const float BIN_HEIGHT = 30.0;      // Dustbin height (cm)
float calibration_factor = -7050.0; // Change after calibration

HX711 scale;

//===========================================================
// Connect WiFi
//===========================================================

void connectWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  delay(1000);

  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int retry = 0;

  while (WiFi.status() != WL_CONNECTED && retry < 30)
  {
    delay(500);
    Serial.print(".");
    retry++;
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("=================================");
    Serial.println("WiFi Connected Successfully!");
    Serial.print("IP Address : ");
    Serial.println(WiFi.localIP());
    Serial.println("=================================");
  }
  else
  {
    Serial.println("=================================");
    Serial.println("WiFi Connection Failed!");
    Serial.print("WiFi Status = ");
    Serial.println(WiFi.status());
    Serial.println("=================================");
  }
}

//===========================================================
// Setup
//===========================================================

void setup()
{
  Serial.begin(115200);

  // Ultrasonic
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // HX711
  scale.begin(DT, SCK);
  scale.set_scale(calibration_factor);
  scale.tare();

  // LEDs
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // Buzzer
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  connectWiFi();

  Serial.println();
  Serial.println("=================================");
  Serial.println("     BINPULSE SMART DUSTBIN");
  Serial.println("=================================");
}

//===========================================================
// Loop
//===========================================================

void loop()
{
  //================ Ultrasonic ==================

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0)
  {
    Serial.println("Ultrasonic Timeout!");
    delay(1000);
    return;
  }

  float distance = duration * 0.0343 / 2.0;

  //================ Fill Percentage ==================

  float fill = ((BIN_HEIGHT - distance) / BIN_HEIGHT) * 100;

  if (fill < 0) fill = 0;
  if (fill > 100) fill = 100;

  //================ Weight ==================

  float weight = scale.get_units(10);

  //================ Status ==================

  String status;

  if (fill >= 100)
    status = "OVERFLOW";
  else if (fill >= 80)
    status = "FULL";
  else if (fill >= 50)
    status = "HALF FULL";
  else
    status = "EMPTY";

  //================ Priority ==================

  String priority;

  if (fill >= 80 && weight >= 4)
    priority = "HIGH";
  else if (fill >= 80 || weight >= 2)
    priority = "MEDIUM";
  else
    priority = "LOW";

  //================ LEDs & Buzzer ==================

  if (fill < 50)
  {
    digitalWrite(GREEN_LED, HIGH);
    
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
  else if (fill < 80)
  {
    digitalWrite(GREEN_LED, LOW);
  
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
  else
  {
    digitalWrite(GREEN_LED, LOW);
 
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  }

  //================ Serial Output ==================

  Serial.println();
  Serial.println("=================================");
  Serial.println("        BINPULSE STATUS");
  Serial.println("=================================");

  Serial.print("Distance      : ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.print("Fill Level    : ");
  Serial.print(fill);
  Serial.println(" %");

  Serial.print("Weight        : ");
  Serial.print(weight);
  Serial.println(" kg");

  Serial.print("Status        : ");
  Serial.println(status);

  Serial.print("Priority      : ");
  Serial.println(priority);

  Serial.println("=================================");

  delay(2000);
}