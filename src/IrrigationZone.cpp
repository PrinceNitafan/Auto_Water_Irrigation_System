#include "IrrigationZone.h"
#include "Config.h"

IrrigationZone::IrrigationZone() {
    zoneNumber = 0;
    sensorPin = 0;
    relayPin = 0;
    dryThreshold = DRY_THRESHOLD;
    wetThreshold = WET_THRESHOLD;
    isPumping = false;
}

void IrrigationZone::begin(int number, int sPin, int rPin, int dryThresh, int wetThresh) {
    zoneNumber = number;
    sensorPin = sPin;
    relayPin = rPin;
    dryThreshold = dryThresh;
    wetThreshold = wetThresh;
    isPumping = false;

    // Set pin HIGH before OUTPUT so the active-low relay does not click on startup
    digitalWrite(relayPin, PUMP_OFF);
    pinMode(relayPin, OUTPUT);
    pinMode(sensorPin, INPUT);
}

int IrrigationZone::readMoisture() const {
    // Average 3 samples to filter out brief analog noise
    int total = 0;
    for (int i = 0; i < 3; i++) {
        total += analogRead(sensorPin);
        delay(10);
    }
    return total / 3;
}

void IrrigationZone::update() {
    int currentMoisture = readMoisture();

    Serial.print("Zone ");
    Serial.print(zoneNumber);
    Serial.print(" Moisture Level: ");
    Serial.print(currentMoisture);

    // Start watering once soil is drier than dryThreshold; keep watering until it drops to wetThreshold
    if (!isPumping && currentMoisture > dryThreshold) {
        turnPumpOn();
    } else if (isPumping && currentMoisture <= wetThreshold) {
        turnPumpOff();
    }

    if (isPumping) {
        Serial.println(" -> Pumping");
    } else {
        Serial.println(" -> Not Pumping");
    }
}

void IrrigationZone::turnPumpOn() {
    digitalWrite(relayPin, PUMP_ON);
    isPumping = true;
}

void IrrigationZone::turnPumpOff() {
    digitalWrite(relayPin, PUMP_OFF);
    isPumping = false;
}

bool IrrigationZone::isPumpRunning() const {
    return isPumping;
}
