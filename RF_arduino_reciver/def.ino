#ifndef _DEF_H_
#define _DEF_H_

#include <Wire.h>
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

// I2C & pins
#define I2Caddr_RC_Unit 3
#define interruptPin    8

// commands
#define cmndForward       0x30
#define cmndForwardRight  0x31
#define cmndForwardLeft   0x32
#define cmndBackward      0x33
#define cmndStop          0x34

// RF payload
#define cmndLength 4
byte dataRx[cmndLength];

char cmnd;
byte movment;

#endif
