#define cmndForward      0x30
#define cmndForwardRight 0x31
#define cmndForwardLeft  0x32
#define cmndBackward     0x33
#define cmndStop         0x34

#define motorBoard  4
#define motor1In1   3
#define motor1In2   4
#define motor1Ena   5
#define motor2In1   10
#define motor2In2   11
#define motor2Ena   9

#include <Wire.h>

volatile uint8_t cmnd;
volatile uint8_t recFlag = 0;

void receiveEvent(int bytes);

void setup() {
    Wire.begin(motorBoard);         // Start the I2C Bus as Slave on address 1
    Wire.onReceive(receiveEvent);   // Attach a function to trigger when something is received

    pinMode(motor1In1, OUTPUT);
    pinMode(motor1In2, OUTPUT);
    pinMode(motor1Ena, OUTPUT);
    pinMode(motor2In1, OUTPUT);
    pinMode(motor2In2, OUTPUT);
    pinMode(motor2Ena, OUTPUT);

    Serial.begin(57600);
    Serial.println("sync");
}

void loop() {
    if (recFlag) {
        Serial.println("hhh");
        cmnd = Wire.read(); // read one character from the I2C
        Serial.println(cmnd);

        switch (cmnd) {
            case (cmndForward):       forward(80);      break;
            case (cmndForwardRight):  forwardRight();   break;
            case (cmndForwardLeft):   forwardLeft();    break;
            case (cmndBackward):      backward(80);     break;
            case (cmndStop):          stop();           break;
        }

        recFlag = 0;
    }
}

void receiveEvent(int bytes) {
    recFlag = 1;
}

void forward(uint8_t speed) {
    digitalWrite(motor1In1, HIGH);
    digitalWrite(motor1In2, LOW);
    analogWrite(motor1Ena, speed);

    digitalWrite(motor2In1, HIGH);
    digitalWrite(motor2In2, LOW);
    analogWrite(motor2Ena, speed);
}

void forwardRight() {
    digitalWrite(motor1In1, HIGH);
    digitalWrite(motor1In2, LOW);
    analogWrite(motor1Ena, 100);

    digitalWrite(motor2In1, HIGH);
    digitalWrite(motor2In2, LOW);
    analogWrite(motor2Ena, 255);
}

void forwardLeft() {
    digitalWrite(motor1In1, HIGH);
    digitalWrite(motor1In2, LOW);
    analogWrite(motor1Ena, 255);

    digitalWrite(motor2In1, HIGH);
    digitalWrite(motor2In2, LOW);
    analogWrite(motor2Ena, 100);
}

void backward(uint8_t speed) {
    digitalWrite(motor1In1, LOW);
    digitalWrite(motor1In2, HIGH);
    analogWrite(motor1Ena, speed);

    digitalWrite(motor2In1, LOW);
    digitalWrite(motor2In2, HIGH);
    digitalWrite(motor2Ena, speed);
}

void stop() {
    digitalWrite(motor1Ena, LOW);
    digitalWrite(motor2Ena, LOW);
}
