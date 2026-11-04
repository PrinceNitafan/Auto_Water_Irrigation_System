#include <Arduino.h>
#include "Config.h"
#include "IrrigationZone.h"

IrrigationZone zones[NUM_ZONES];
unsigned long lastCheckTime = 0;

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);

    for (int i = 0; i < NUM_ZONES; i++) {
        zones[i].begin(i + 1, SENSOR_PINS[i], RELAY_PINS[i], DRY_THRESHOLD, WET_THRESHOLD);
    }

    Serial.println("Irrigation System Initialized.");
}

void loop() {
    unsigned long currentTime = millis();

    // Non-blocking interval check so the board is not paused with a long delay()
    if (currentTime - lastCheckTime >= CHECK_INTERVAL_MS) {
        lastCheckTime = currentTime;

        for (int i = 0; i < NUM_ZONES; i++) {
            zones[i].update();
        }
        Serial.println("--------------------------------");
    }
}
