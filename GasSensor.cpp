#include "GasSensor.h"

#define RL_VALUE 10.0       // Resistencia de carga en kilo-ohms
#define RO_CLEAN_AIR_FACTOR 9.83  // RS/RO en aire limpio
#define CALIBRATION_SAMPLE_TIMES 50
#define CALIBRATION_SAMPLE_INTERVAL 500
#define READ_SAMPLE_INTERVAL 50
#define READ_SAMPLE_TIMES 5

GasSensor::GasSensor(byte pin)
    : analogPin(pin), ro(10.0), ppm(0) {}

void GasSensor::begin() {
    pinMode(analogPin, INPUT);
    Serial.println("Calibrando sensor MQ-2... (Espere 20 segundos)");
    ro = calibrateSensor();
    if (ro > 0) {
        Serial.print("Calibración completada. Ro = ");
        Serial.print(ro);
        Serial.println(" KΩ");
    } else {
        Serial.println("Error en calibración. Usando valor por defecto.");
    }
}

void GasSensor::update() {
    unsigned long currentMillis = millis();
    
    if (currentMillis - previousMillis >= updateInterval) {
        previousMillis = currentMillis;
        
        float rs = readMQ();
        if (rs > 0) {
            float ratio = rs / ro;
            ppm = getGasPPM(ratio);
            
            Serial.print("ADC: "); Serial.print(analogRead(analogPin));
            Serial.print(" | RS: "); Serial.print(rs);
            Serial.print(" Ω | Ratio: "); Serial.print(ratio);
            Serial.print(" | PPM: "); Serial.print(ppm);
            Serial.println(" ppm");
        } else {
            Serial.println("Error en lectura del sensor");
        }
    }
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
    float val = 0.0;
    
    for (int i = 0; i < CALIBRATION_SAMPLE_TIMES; i++) {
        val += calculateResistance(analogRead(analogPin));
        delay(CALIBRATION_SAMPLE_INTERVAL);
    }
    
    val = val / CALIBRATION_SAMPLE_TIMES;                 // Calcular el valor medio
    val = val / RO_CLEAN_AIR_FACTOR;                      // Calcular Rs/Ro
    return val;
}

float GasSensor::readMQ() {
    float rs = 0.0;
    
    for (int i = 0; i < READ_SAMPLE_TIMES; i++) {
        rs += calculateResistance(analogRead(analogPin));
        delay(READ_SAMPLE_INTERVAL);
    }
    
    rs = rs / READ_SAMPLE_TIMES;
    return rs;
}

float GasSensor::calculateResistance(int adc_value) {
    if (adc_value <= 0) return -1;
    float voltage = adc_value * (3.3 / 4095.0);  // Convertir a voltaje (ESP32)
    return RL_VALUE * (3.3 - voltage) / voltage;  // Calcular resistencia
}

float GasSensor::getGasPPM(float rs_ro_ratio) {
    if (rs_ro_ratio <= 0) return 0;
    float log_ppm = (log10(rs_ro_ratio) - LPG_Curve[1]) / LPG_Curve[2];
    float ppm = pow(10, log_ppm) * LPG_Curve[0];
    return (isnan(ppm) || isinf(ppm)) ? 0 : ppm;
}