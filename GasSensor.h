#ifndef GASSENSOR_H
#define GASSENSOR_H

#include <Arduino.h>

class GasSensor {
public:
    GasSensor(byte analogPin);
    void begin();
    void update();

    float getPPM();
    float getRawResistance();
    float getRo();
    float readMQ();
    
private:
    byte analogPin;
    float ro;
    float ppm;
    float curve[3] = {2.3, 0.21, -0.47}; // LPG curve

    float calibrateSensor();
    float calculateResistance(int adc_value);
    float getGasPPM(float rs_ro_ratio, float* curve); // ← corregido: float en vez de int
};

#endif
