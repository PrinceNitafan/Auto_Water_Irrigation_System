#pragma once
#include <Arduino.h>

// Pairs one soil moisture sensor with one pump relay channel
class IrrigationZone {
private:
    int zoneNumber;
    int sensorPin;
    int relayPin;
    int dryThreshold;
    int wetThreshold;
    bool isPumping;

public:
    IrrigationZone();

    void begin(int number, int sPin, int rPin, int dryThresh, int wetThresh);
    int readMoisture() const;
    void update();
    void turnPumpOn();
    void turnPumpOff();
    bool isPumpRunning() const;
};
