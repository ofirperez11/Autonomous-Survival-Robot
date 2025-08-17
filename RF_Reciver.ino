#include "def.h"

void setup() {
    Wire.begin(I2Caddr_RC_Unit);
    Wire.onRequest(reqEvent);
    Serial.begin(57600);
    pinMode(interruptPin, OUTPUT);

    Mirf.spi = &MirfHardwareSpi;
    Mirf.cePin = 9;
    Mirf.csnPin = 10;
    Mirf.init();
    Mirf.setRADDR((byte *)"ROBOT");
    Mirf.payload = cmndLength;
    Mirf.config();

    Serial.print("listening...");
}

void loop() {
    if (!Mirf.isSending() && Mirf.dataReady()) {
        // Serial.println("Got packet");
        Mirf.getData(dataRx);

        int x, y;
        x = dataRx[0] * 100 + dataRx[1];
        y = dataRx[2] * 100 + dataRx[3];

        // Serial.print("x="); Serial.println(x);
        // Serial.print("y="); Serial.println(y);

        if (x < 480 && y < 635 && y > 385) {
            Serial.println("forward");
            cmnd = cmndForward;
        }
        else if (x > 540 && y < 635 && y > 385) {
            Serial.println("backward");
            cmnd = cmndBackward;
        }
        else if (x < 540 && x > 480) {
            Serial.println("stop");
            cmnd = cmndStop;
        }
        else if (x < 480 && y < 385) {
            Serial.println("farwardRight");
            cmnd = cmndForwardRight;
        }
        else if (x < 480 && y > 635) {
            Serial.println("farwardLeft");
            cmnd = cmndForwardLeft;
        }
        else if (x > 540 && y < 385) {
            Serial.println("backwardRight");
            cmnd = cmndBackward;
        }
        else if (x > 540 && y > 635) {
            Serial.println("backwardLeft");
            cmnd = cmndBackward;
        }

        sendInt();
    }
}

void reqEvent(int bytes) {
    Wire.write(&cmnd, 1);
}

void sendInt() {
    digitalWrite(interruptPin, LOW);
    delayMicroseconds(5);
    digitalWrite(interruptPin, HIGH);
}
