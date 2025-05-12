#ifndef IOTCLIENT_H
#define IOTCLIENT_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "BuzzerController.h"
#include "GasSensor.h"

class IoTClient {
public:
    IoTClient();
    void begin();
    void loop();
    void reportState();
    void applyState();
    void onMessageReceived(char* topic, byte* payload, unsigned int length);

private: 
    String getGasLevelStatus(int ppm);

    int    lastGasPPM;
    String lastGasStatus;

    WiFiClientSecure wiFiClient;
    PubSubClient mqttClient;

    String buzzerState;
    String valveState;

    BuzzerController buzzerController;
    ValveController valveController;
    GasSensor gasSensor;

    void setupWiFi();
    void setupMQTT();
    void reconnect();
    void updateSensor();
};

#endif