// =====================================================
//   ESP32 PIR Sensor IoT Notification Project
//   Developer: Tugay Akdemir
//   Description: Detects motion using HC-SR501 PIR
//   and sends real-time notification via Blynk IoT.
//
//   Board: ESP32 DevKit V1
//   Sensor: HC-SR501
//   Pin: PIR OUT -> GPIO13
// =====================================================

#define BLYNK_TEMPLATE_NAME "TugayAkdemir Pir Sensor"
#define BLYNK_AUTH_TOKEN "BURAYA_KENDI_TOKENINI_YAZ"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// -----------------------------------------
// Hotspot / WiFi Information
// -----------------------------------------
char ssid[] = "Tugay";      // Hotspot Name
char pass[] = "tugayay1";   // Hotspot Password

// -----------------------------------------
// PIR Sensor Configuration
// -----------------------------------------
const int PIR_PIN = 13;     // GPIO13 = PIR OUT
int lastPirState = LOW;     // Last sensor state
unsigned long lastNotify = 0;

// Notify every 10 seconds max
const unsigned long COOLDOWN = 10000;

// -----------------------------------------
// SETUP
// -----------------------------------------
void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);

  Serial.println("Connecting to WiFi...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("Waiting 30s for PIR calibration...");
  delay(30000); // PIR warm-up
  Serial.println("Calibration complete, ready.");
}

// -----------------------------------------
// LOOP
// -----------------------------------------
void loop() {
  Blynk.run();

  int pirState = digitalRead(PIR_PIN);

  // Detect rising edge (LOW -> HIGH)
  if (pirState == HIGH && lastPirState == LOW) {
    unsigned long now = millis();

    if (now - lastNotify > COOLDOWN) {
      Serial.println("Motion detected -> Sending notification!");

      // Blynk event name must match Blynk settings
      Blynk.logEvent("pir_sensor", "Motion detected!");

      lastNotify = now;
    }
  }

  lastPirState = pirState;

  delay(100);
}
