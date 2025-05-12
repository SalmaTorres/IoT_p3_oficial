#ifndef BUZZERCONTROLLER_H
#define BUZZERCONTROLLER_H

#include <Arduino.h>

class BuzzerController {
public:
    void begin();
    void setState(String state);
    String getState();
    void apply();

private:
    String buzzerState;
};

#endif