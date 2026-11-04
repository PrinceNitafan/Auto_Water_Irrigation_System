#pragma once
#include <Arduino.h>

// Can be overridden by platformio.ini build_flags (1 for single pump, 4 for multi)
#ifndef NUM_ZONES
#define NUM_ZONES 4
#endif

const long SERIAL_BAUD_RATE = 115200;

// 4-channel relay module is active-low (LOW = pump ON, HIGH = pump OFF)
const int PUMP_ON = LOW;
const int PUMP_OFF = HIGH;

// Capacitive sensor values go up as soil dries out.
// Separate start/stop thresholds keep the relay from chattering right around 425.
const int DRY_THRESHOLD = 425;
const int WET_THRESHOLD = 380;

const unsigned long CHECK_INTERVAL_MS = 1000;

// Zone 1 -> A0 & pin 2, Zone 2 -> A1 & pin 3, etc.
const int SENSOR_PINS[4] = {A0, A1, A2, A3};
const int RELAY_PINS[4] = {2, 3, 4, 5};
