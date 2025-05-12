#ifndef GAS_SENSOR_H
#define GAS_SENSOR_H

#include <Arduino.h>

class GasSensor {
public:
    GasSensor(byte analogPin);
    void begin();
    void update();
    float getPPM();
    float getRo();
    float getRawResistance();

private:
    byte analogPin;
    float ro;
    float ppm;
    float curve[3] = { 2.3, 0.21, -0.47 }; // Curva típica para LPG con MQ-2

    float calibrateSensor();
    float readMQ();
    float calculateResistance(int adc_value);
    float getGasPPM(float rs_ro_ratio, float* curve);
};

#endif
