
#ifndef _DEF_H_
#define _DEF_H_

#define motorBoard 4
// #define interruptPin 2

#include <Wire.h>
#include <LiquidCrystal.h>
#include <TimerOne.h>

// RC communication
#define I2Caddr_RC_Unit 3
#define cmndLength 1
char Rfdata[cmndLength];
char flagRF = 0;

// commands list:
#define cmndForward      0x30
#define cmndForwardRight 0x31
#define cmndForwardLeft  0x32
#define cmndBackward     0x33
#define cmndStop         0x34

#define forwardRight  0
#define forwardLeft   1
#define forwardCenter 2
#define forwardHole   3

#define fire      0
#define tempLeft  1
#define tempRight 2

// sonar communication
#define I2Caddr_US_Unit 2
#define UsdataLength    4
char Usdata[UsdataLength];
char flagSonar = 0;

// Temp and Fire communication
#define I2Caddr_Temp_Unit 5
#define TmdataLength      3
char Tmdata[TmdataLength];
char flagTemp = 0;

// Battery monitoring
bool  flagBatMonitoring = 0;
float Vbat, Ibat;

// LCD pins
const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Function declarations
void readTempFire();
void readSonar();
void readRC();

#endif
