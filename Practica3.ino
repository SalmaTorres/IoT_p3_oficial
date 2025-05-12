#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>
#include "IoTClient.h"

IoTClient ioTClient;

void setup() {
  Serial.begin(115200);
  ioTClient.begin();
}

void loop() {
  ioTClient.loop();
}