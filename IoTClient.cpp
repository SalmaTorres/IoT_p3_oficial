#include "IoTClient.h"

const char* WIFI_SSID = "holi holi holi";
const char* WIFI_PASS = "acasapete";

const char* MQTT_BROKER = "a2qtonmyilc0yl-ats.iot.us-east-2.amazonaws.com"; 
const int MQTT_PORT = 8883;
const char* CLIENT_ID = "ESP-32";

const char AMAZON_ROOT_CA1[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

const char CERTIFICATE[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUUiX7CfJzJiE6/FUqBbMdwQolj9YwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI1MDUwNjE5NTk1
OFoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAK1xbqWwql3gop7fq65P
olfIxYRjN/6tdKhdKmK03TtAOWS412zykI5dLiEkDLOtFbn3lO/4H9MkScgqH/4F
DeBvpfPKXOuZVWLk/25IxV4fqePNhxUnaYvJ5iI5b8hF4yxGc/ccd4ZLKvkYg7oN
/OQ7HLcy6pADnHTlp9ZFA54SetjXm84evM7jiSuKRej/YIUgv0RRJP49uPZnCE8p
ToZz8s7gztcwqxFI+JGhWpBxTT7gGeQqn+iOOgqCCbJ8mcSkTmDj+EmyI5DA/bG8
Gv8eqtm1zput931YDr09Sx4YZmqywT8rZe2F5+Ia+joXpsIXnafIpVfTVXQcBiD/
Bm8CAwEAAaNgMF4wHwYDVR0jBBgwFoAUYgTr4R+NW886ZU03e/VL0vFV6nswHQYD
VR0OBBYEFCm3USAXsgowv7SSlQ3akwnsKOrMMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAjICr9crCqGErZTGH8kPFctdbq
+vdHxO/zq6NWVULlnRGYjjDIzxIKpwlNwITGN9JTG516eOO/Ivk8omG4GewSgNpF
z98zINth3CU2+csTBUqj3Rey+gwS5TuCjWAPF4Dwy/f/Ttbkv6n2PUaHP9mnh6J6
djWS1UNAP4NQkaiPBQ74IqjVKT4rzwwgSlel5AJDCDqI/jAXOL2TmmAjkg3GYy/e
T1sLrrhByEzq8ZhhWWSmFobH96/BRlWs02qWxDFPZEy/H5L/YD2sTtQJz3APGB8k
PKMAxRxIeSPCmI/yB4sqGihozUdtxvz5U0gnZwX+OoxMAZH3QQndj76pfRDr
-----END CERTIFICATE-----
)KEY";

const char PRIVATE_KEY[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEArXFupbCqXeCint+rrk+iV8jFhGM3/q10qF0qYrTdO0A5ZLjX
bPKQjl0uISQMs60VufeU7/gf0yRJyCof/gUN4G+l88pc65lVYuT/bkjFXh+p482H
FSdpi8nmIjlvyEXjLEZz9xx3hksq+RiDug385DsctzLqkAOcdOWn1kUDnhJ62Neb
zh68zuOJK4pF6P9ghSC/RFEk/j249mcITylOhnPyzuDO1zCrEUj4kaFakHFNPuAZ
5Cqf6I46CoIJsnyZxKROYOP4SbIjkMD9sbwa/x6q2bXOm633fVgOvT1LHhhmarLB
Pytl7YXn4hr6Ohemwhedp8ilV9NVdBwGIP8GbwIDAQABAoIBAFN8eGA1C6yohl6n
F4KOPny23ax9/eQPJkosnkxo9tyga3/6IWgF0mNUovG84ohSVlTvwbdI3jjKDOHW
tROW5zkTRPR2gge+BQXXaMRzLt3BrAtFUTJziDCLfMUYlJ/4VANp3kQiZb40zHie
vjl+pi5N7eKZFaNAubzjFsji63zYaXoA1+VhH9FN07GndY3cZySHwNZjimF3oS1/
JBLlHRuYhlQO6wwFirU99iqKd1yOm2KVqFQj2Mv7M+7cvUE0GiEmqVQd8Cev9ABz
9kSFn9JdoL9eHhGG4TErq2aidZ8kXd8QNzFli9dppqvw48wgkzyrGVv2lX3b9V/7
UtDxrwECgYEA1mq9OMNzhBs8n6GIpzuLZSR54WkC4d/P+548LlId1C9Lh3mMBREb
t2sOZzdgopw/EbAeR8gA/fvd+F0ZtIIX5eY5t3lmoIX0C0V90EiJIvco/owunbHR
xMctPkjko1g1N9G+i4Lcey2Uj/Jhz6ULgQKoGIGddOzsBO76f9Akua8CgYEAzxRx
yaXKGRTsQY9egxd0CemL/pNi5p1Iy1eMTTDLJB6ZMBJnWL0Ru3QrUO44EZGx6qgE
6MTkHFWqdonwX7kS29mbFOS8hmnXnITIY7rORgSBz/gJR/7vgZtERmGRq5L5IiMj
QmX5NgzpKarQKrAE5c6CxNxJ+3yyR71tluanb0ECgYEAqPkfO5+T5lUMloRXS+s5
9DAluMTn15dosVNG+/4Msc2/yPi5priPziEZDbBvgFZ/wXG4uzrbxUx65iKAgmdP
bAbeD0Al53UJGOTfvIedQyfib4+LoQykUl3gwsfxHuUBs4agkhNDq/MEs9gAywG3
KikszXs/2ghoC49Fa/pdJtMCgYB3TjIYmVoMhU9wnic3o8WJCHNNoqCyeR+9d50v
w9Ll5nMfjRrZt2SF+XITWIwZIzW8Gj1p1jYOVRS24tYIcFp7K637paUwU76TQLUr
MC8zi9k2dpLyVeCrbUcyvXftv+mlT1U7JgEksN+M0ArK7UqFFCunO7usFrWoO2zu
KcmBgQKBgQDSRS9Quk9uxm5G6T4hf9hnWAYmJSaJ/zOfhJ9Nb/18t3n0XQPmcBCI
T09WPyl5yoI8uIoaFXM9tHVHLZzHz/zqIC9sxKQGP3nSf3rOhBZfPEHH15eyfVpZ
duLO6z4WDiiKZX65uInjpLZPVLlANOOlMb43AHOjtJNnnaV3lHQQKA==
-----END RSA PRIVATE KEY-----
)KEY";

const char* UPDATE_TOPIC = "$aws/things/iot_thing/shadow/update";
const char* UPDATE_DELTA_TOPIC = "$aws/things/iot_thing/shadow/update/delta";

StaticJsonDocument<JSON_OBJECT_SIZE(64)> inputDoc;
StaticJsonDocument<JSON_OBJECT_SIZE(4)> outputDoc;
char output[256];

IoTClient::IoTClient() 
    : wiFiClient(), mqttClient(wiFiClient),
      buzzerState("Off"), valveState("Closed"),
      gasSensor(34),  // Pin analógico 34 para el sensor MQ-2
      lastGasPPM(-1), lastGasStatus("") {}

void IoTClient::begin() {
    Serial.begin(115200);
    buzzerController.begin();
    gasSensor.begin();  // Inicia la calibración automática
    setupWiFi();
    setupMQTT();
}

void IoTClient::loop() {
    if (!mqttClient.connected()) reconnect();
    mqttClient.loop();

    gasSensor.update();  // Actualiza las lecturas del sensor
    updateSensor();
}

String IoTClient::getGasLevelStatus(float ppm) {  // Esto ahora coincide con el .h
    if (ppm < 200) return "Normal";
    if (ppm < 1000) return "Precaucion";
    return "Ventilar";
}

void IoTClient::updateSensor() {
    float ppm = gasSensor.getPPM();       
    String status = getGasLevelStatus(ppm);

    // Mostrar información detallada en el monitor serial
    static unsigned long lastPrint = 0;
    if (millis() - lastPrint > 2000) {  // Mostrar cada 2 segundos
        lastPrint = millis();
        
        Serial.print("Resistencia: ");
        Serial.print(gasSensor.getRawResistance());
        Serial.print(" Ω | Ro: ");
        Serial.print(gasSensor.getRo());
        Serial.print(" KΩ | PPM: ");
        Serial.print(ppm);
        Serial.print(" | Estado: ");
        Serial.println(status);
    }

    // Actualizar el estado solo si hay un cambio significativo
    if (abs(ppm - lastGasPPM) > 10 || status != lastGasStatus) {
        lastGasPPM = ppm;
        lastGasStatus = status;
        reportState();
    }
}

void IoTClient::reportState() {
    outputDoc.clear();
    JsonObject state = outputDoc.createNestedObject("state");
    JsonObject reported = state.createNestedObject("reported");

    reported["buzzerStatus"] = buzzerState;
    reported["valveStatus"] = valveState;
    reported["gasLevelPPM"] = lastGasPPM;
    reported["gasLevelStatus"] = lastGasStatus;

    serializeJson(outputDoc, output);
    if (!mqttClient.publish(UPDATE_TOPIC, output)) {
        Serial.println("Error al publicar en MQTT");
    }
}

void IoTClient::onMessageReceived(char* topic, byte* payload, unsigned int length) {
    String message;
    for (int i = 0; i < length; i++) message += (char)payload[i];
    Serial.println("Message from topic " + String(topic) + ": " + message);

    DeserializationError err = deserializeJson(inputDoc, payload, length);
    if (err) {
        Serial.print("Deserialization failed: ");
        Serial.println(err.c_str());
        return;
    }

    if (String(topic) == UPDATE_DELTA_TOPIC) {
        JsonObject state = inputDoc["state"];
        if (state.containsKey("buzzerStatus")) {
            String newBuzzerState = state["buzzerStatus"].as<String>();
            if (newBuzzerState != buzzerState) {
                buzzerState = newBuzzerState;
                buzzerController.setState(buzzerState);
                buzzerController.apply();
                reportState();
            }
        }
    }
}

void IoTClient::setupWiFi() {
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected. IP address: " + WiFi.localIP().toString());
}

void IoTClient::setupMQTT() {
    wiFiClient.setCACert(AMAZON_ROOT_CA1);
    wiFiClient.setCertificate(CERTIFICATE);
    wiFiClient.setPrivateKey(PRIVATE_KEY);

    mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
    mqttClient.setCallback([this](char* topic, byte* payload, unsigned int length) {
        onMessageReceived(topic, payload, length);
    });
}

void IoTClient::reconnect() {
    while (!mqttClient.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (mqttClient.connect(CLIENT_ID)) {
            Serial.println("connected");
            mqttClient.subscribe(UPDATE_DELTA_TOPIC);
        } else {
            Serial.print("failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}
