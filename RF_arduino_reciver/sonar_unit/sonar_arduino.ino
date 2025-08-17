#include "def.h"

void setup() {
    Serial.begin(57600);

    Wire.begin(2);
    Wire.onRequest(reqEvent);

    pinMode(intOutPin, OUTPUT);
    digitalWrite(intOutPin, HIGH);

    for (int i = 0; i < 4; i++)
        range_cm[i] = sonar[i].ping_cm();
}

void loop() {
    volatile uint8_t range_cm_old[4];

    for (int i = 0; i < 4; i++) {
        range_cm_old[i] = range_cm[i];
        range_cm[i] = sonar[i].ping_cm();
        Serial.print(range_cm[i]);
        Serial.print("cm ");
        delay(50);
    }

    if (range_cm[3] > 25) {
        Serial.println("HOLE");
        RANGE[3] = 1;
    } else {
        RANGE[3] = 0;

        for (int i = 0; i < 3; i++) {
            if (range_cm[i] < range_cm_collision && range_cm[i] > 0) {
                RANGE[i] = 1;
                Serial.print("error with");
                Serial.print(i);
            } else {
                RANGE[i] = 0;
            }
        }
    }

    if (RANGE[0] || RANGE[1] || RANGE[2] || RANGE[3])
        sendInt();

    delay(10);
    Serial.println();
}

void reqEvent(int bytes) {
    Wire.write(RANGE, 4);
}

void sendInt() {
    digitalWrite(intOutPin, LOW);
    delayMicroseconds(5);
    digitalWrite(intOutPin, HIGH);
}
