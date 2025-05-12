#include "GasSensor.h"

#define RL_VALUE 10.0
#define RO_CLEAN_AIR_FACTOR 9.83

GasSensor::GasSensor(byte analogPin)
    : analogPin(analogPin), ro(10.0), ppm(0) {}

void GasSensor::begin() {
    Serial.begin(115200);
    Serial.println("Calibrando sensor MQ-2 en aire limpio...");
    ro = calibrateSensor();
    Serial.print("Calibración completada. Ro = ");
    Serial.print(ro);
    Serial.println(" KΩ");
    delay(500);
}

void GasSensor::update() {
    float rs = readMQ();
    float ratio = rs / ro;
    ppm = getGasPPM(ratio, curve);

    Serial.print("RS: "); Serial.print(rs);
    Serial.print(" | RS/Ro: "); Serial.print(ratio);
    Serial.print(" | Concentración estimada de gas LPG: ");
    Serial.print(ppm);
    Serial.println(" ppm");
}

float GasSensor::getPPM() {
    return ppm;
}

float GasSensor::getRo() {
    return ro;
}

float GasSensor::getRawResistance() {
    return readMQ();
}

float GasSensor::calibrateSensor() {
    float val = 0;
    for (int i = 0; i < 50; i++) {
        int adc = analogRead(analogPin);
        float rs = calculateResistance(adc);
        Serial.print("ADC calibración: "); Serial.print(adc);
        Serial.print(" | RS: "); Serial.println(rs);
        if (rs > 0) val += rs;
        delay(200);
    }
    return (val / 50.0) / RO_CLEAN_AIR_FACTOR;
}

float GasSensor::readMQ() {
    float rs = 0;
    int n = 0;
    for (int i = 0; i < 5; i++) {
        int raw = analogRead(analogPin);
        float r = calculateResistance(raw);
        if (r > 0) {
            rs += r;
            n++;
        }
        delay(50);
    }
    return n ? rs / n : -1;
}

float GasSensor::calculateResistance(int adc_value) {
    if (adc_value <= 0) return -1;
    return ((float)RL_VALUE * (4095.0 - adc_value)) / adc_value;
}

float GasSensor::getGasPPM(float rs_ro_ratio, float* curve) {
    if (rs_ro_ratio <= 0 || curve[2] == 0) return 0;
    float log_ppm = (log10(rs_ro_ratio) - curve[1]) / curve[2] + curve[0];
    float ppm = pow(10, log_ppm);
    if (isnan(ppm) || isinf(ppm) || ppm > 10000) return 0;
    return ppm;
}
