#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>

#define left   9
#define right  8
#define fireInt 4

OneWire sensor_1(right);
OneWire sensor_2(left);
DallasTemperature sensor_right(&sensor_1);
DallasTemperature sensor_left(&sensor_2);

char danger[3] = {0, 0, 0};

void setup(void) {
    Serial.begin(57600);

    Wire.begin(5);
    Wire.onRequest(reqEvent);

    sensor_right.begin();
    sensor_left.begin();

    pinMode(fireInt, OUTPUT);
    digitalWrite(fireInt, HIGH);
}

void loop(void) {
    int x, tempLeft, tempRight;

    x = analogRead(A0);

    sensor_left.requestTemperatures();
    sensor_right.requestTemperatures();

    Serial.print("temp in right side: ");
    Serial.println(sensor_right.getTempCByIndex(0));
    Serial.print("temp in left side: ");
    Serial.println(sensor_left.getTempCByIndex(0));

    tempLeft  = sensor_left.getTempCByIndex(0);
    tempRight = sensor_right.getTempCByIndex(0);

    if (x < 250) danger[0] = 1;
    else         danger[0] = 0;

    if (tempLeft > 27) danger[1] = 1;
    else               danger[1] = 0;

    if (tempRight > 27) danger[2] = 1;
    else                danger[2] = 0;

    if (danger[0] || danger[1] || danger[2]) sendInt();

    delay(300);
}

void sendInt() {
    digitalWrite(fireInt, LOW);
    delayMicroseconds(5);
    digitalWrite(fireInt, HIGH);
}

void reqEvent() {
    Wire.write(danger, 3);
}
