#ifndef GAS_SENSOR_H
#define GAS_SENSOR_H

#include <Arduino.h>

class GasSensor {
public:
    GasSensor(byte pin = 34);  // Constructor con pin configurable
    void begin();
    void update();
    float getPPM();
    float getRo();
    float getRawResistance();

private:
    byte analogPin;
    float ro;
    float ppm;
    unsigned long previousMillis = 0;
    const unsigned long updateInterval = 1000;
    
    // Curva para LPG en el sensor MQ-2
    const float LPG_Curve[3] = {2.3, 0.21, -0.47};

    float calibrateSensor();
    float readMQ();
    float calculateResistance(int adc_value);
    float getGasPPM(float rs_ro_ratio);
};
#endif