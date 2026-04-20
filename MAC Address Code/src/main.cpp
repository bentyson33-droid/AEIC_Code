// MAC OBTAINED
#include <Arduino.h>
#include <WiFi.h>

void setup() {
  Serial.begin(9600);
  delay(5000);  // wait for Serial to attach
  Serial.println("START TEST");
}

void loop() {
  delay(5000);
  Serial.println(WiFi.status());
  Serial.println(WiFi.macAddress());
}