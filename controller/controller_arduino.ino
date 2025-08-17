#include "def.h"

//***********************************************************
void setup() {
    initMirf();
    Serial.begin(9600);
}
//***********************************************************
void loop() {
    int  x, y;
    byte x1, x2, y1, y2;

    x = analogRead(A0);
    y = analogRead(A1);

    x1 = x / 100;
    x2 = x % 100;
    y1 = y / 100;
    y2 = y % 100;

    // if (x < 450) cmnd = cmndForward;
    // else if (x > 570) cmnd = cmndBackward;

    byte dataRF[4];
    dataRF[0] = x1;
    dataRF[1] = x2;
    dataRF[2] = y1;
    dataRF[3] = y2;

    Mirf.send(dataRF);
    while (Mirf.isSending());

    delay(100);
}
//***********************************************************
void initMirf() {
    Mirf.cePin = 9;
    Mirf.csnPin = 10;
    Mirf.spi    = &MirfHardwareSpi;

    Mirf.init();
    Mirf.setTADDR((byte *)"ROBOT");
    Mirf.payload = 4;
    Mirf.config();  // Write channel and payload config then power up receiver.
}
//************************************************************
