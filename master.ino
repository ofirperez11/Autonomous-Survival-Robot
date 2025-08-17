#include "def.h"

void setup() {
    Serial.begin(57600);
    Wire.begin();

    attachInterrupt(0, UsInt, FALLING);
    attachInterrupt(1, RFInt, FALLING);
    attachInterrupt(5, TempInt, FALLING);

    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);

    Timer1.initialize(1000000);
    Timer1.attachInterrupt(batMonitoring);
}

void loop() {
    if (flagBatMonitoring) {
        calcBatIV();
        flagBatMonitoring = 0;

        Serial.print("Vbat=");
        Serial.println(Vbat);
        Serial.print("Ibat=");
        Serial.println(Ibat);

        lcd.setCursor(0, 1);
        lcd.print("V=");
        lcd.print(Vbat);
        lcd.print(",I=");
        lcd.print(Ibat);

        if (Ibat > 1100)
            sendi2c(motorBoard, cmndStop);
    }
    else if (flagTemp) {
        readTempFire();
        flagTemp = 0;
    }
    else if (flagSonar) {
        readSonar();
        flagSonar = 0;
    }

    if (flagRF) {
        readRC();
        flagRF = 0;
    }
}

void TempInt() {
    flagTemp = 1;
}

void UsInt() {
    flagSonar = 1;
}

void RFInt() {
    flagRF = 1;
}

void batMonitoring() {
    flagBatMonitoring = 1;
}

void calcBatIV() {
    int A1 = analogRead(A6);
    int A2 = analogRead(A7);

    Vbat = 400. * A1 / 33792;
    Ibat = 400000. * (A1 - A2) / 33792;
}

void readTempFire() {
    byte cmnd;
    detachInterrupt(TempInt);

    Wire.requestFrom(I2Caddr_Temp_Unit, TmdataLength, true);
    Wire.readBytes(Tmdata, TmdataLength);

    for (int i = 0; i < TmdataLength; i++) {
        Serial.write(Tmdata[i] + 0x30);
        Serial.println(" ");
    }
    Serial.println();

    if (Tmdata[fire] && !Tmdata[tempLeft] && !Tmdata[tempRight]) {
        Serial.println("fire");
        cmnd = cmndBackward;
        lcd.setCursor(0, 0);
        lcd.print(" fire!");
    }
    else if (!Tmdata[fire] && Tmdata[tempLeft] && !Tmdata[tempRight]) {
        Serial.println("hot in the left side");
        cmnd = cmndForwardRight;
        lcd.setCursor(0, 0);
        lcd.print(" hot in left");
    }
    else if (!Tmdata[fire] && !Tmdata[tempLeft] && Tmdata[tempRight]) {
        Serial.println("hot in the right side");
        cmnd = cmndForwardLeft;
        lcd.setCursor(0, 0);
        lcd.print(" hot in right");
    }

    sendi2c(motorBoard, cmnd);
    delay(20);
    attachInterrupt(5, TempInt, FALLING);
}

void readSonar() {
    byte cmnd;
    detachInterrupt(UsInt);

    Wire.requestFrom(I2Caddr_US_Unit, UsdataLength, true);
    Wire.readBytes(Usdata, UsdataLength);

    for (int i = 0; i < UsdataLength; i++) {
        Serial.write(Usdata[i] + 0x30);
        Serial.println(" ");
    }
    Serial.println();

    if (Usdata[forwardHole]) {
        Serial.println("Backward");
        cmnd = cmndBackward;
        lcd.setCursor(0, 0);
        lcd.print(" hole!");
    }
    else if (!Usdata[forwardRight] && !Usdata[forwardCenter] && Usdata[forwardLeft]) {
        Serial.println("turn right");
        cmnd = cmndForwardRight;
        lcd.setCursor(0, 0);
        lcd.print(" go right");
    }
    else if (!Usdata[forwardRight] && Usdata[forwardCenter] && !Usdata[forwardLeft]) {
        Serial.println("go back");
        cmnd = cmndBackward;
        lcd.setCursor(0, 0);
        lcd.print(" go back");
    }
    else if (Usdata[forwardRight] && !Usdata[forwardCenter] && !Usdata[forwardLeft]) {
        Serial.println("turn left");
        cmnd = cmndForwardLeft;
        lcd.setCursor(0, 0);
        lcd.print(" go left");
    }
    else {
        cmnd = cmndStop;
        Serial.println("stop");
        lcd.setCursor(0, 0);
        lcd.print(" i need stop");
    }

    sendi2c(motorBoard, cmnd);
    delay(20);
    attachInterrupt(0, UsInt, FALLING);
}

void readRC() {
    Serial.println("sync master");
    detachInterrupt(RFInt);

    Wire.requestFrom(I2Caddr_RC_Unit, cmndLength, true);
    Wire.readBytes(Rfdata, cmndLength);

    for (int i = 0; i < cmndLength; i++) {
        Serial.println(Rfdata[i]);
        lcd.setCursor(0, 0);
        lcd.print("Beautiful Day ");
        sendi2c(motorBoard, Rfdata[i]);
    }

    attachInterrupt(1, RFInt, FALLING);
}

void sendi2c(char board, char value) {
    Wire.beginTransmission(board); // transmit to device
    Wire.write(value);             // send value
    Wire.endTransmission();        // stop transmitting
}
