#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
//Board = Arduino Uno
#define __AVR_ATmega328p__
#define __AVR_ATmega328P__
#define _VMDEBUG 1
#define ARDUINO 101
#define ARDUINO_MAIN
#define __AVR__
#define __avr__
#define F_CPU 16000000L
#define __cplusplus
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__

#define __builtin_va_list
#define __builtin_va_start
#define __builtin_va_end
#define __DOXYGEN__
#define __attribute__(x)
#define NOINLINE __attribute__((noinline))
#define prog_void
#define PGM_VOID_P int
            
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}

//
//
void trigger(int period);
void initSerialLogger();
void logError(String message);
void logError(const char message[], int value);
void logDebug(String message);
void logInfo(String message);
void GetLatestReading();
int GetTemperatureF();
int GetTemperatureC();
void initTouch();
void getPoint();
bool pressDetected();
int getZ();
int mapX();
int mapY();
void initScreen();
void setStandby(bool standby);
void drawUIEx();
void updateTitle(char title[]);
void updateTemperature(int temp);
void drawButtons(boolean invert);
void drawLeftButton(boolean invert);
void drawMiddleButton(boolean invert);
void drawRightButton(boolean invert);

#include "C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "C:\Program Files (x86)\Arduino\hardware\arduino\variants\standard\pins_arduino.h" 
#include "D:\Development\Arduino\Garage Door Opener\ArduinoGarageConsole\ArduinoGarageConsole.ino"
#include "D:\Development\Arduino\Garage Door Opener\ArduinoGarageConsole\RelayControl.ino"
#include "D:\Development\Arduino\Garage Door Opener\ArduinoGarageConsole\SerialLogger.ino"
#include "D:\Development\Arduino\Garage Door Opener\ArduinoGarageConsole\TempSensor.ino"
#include "D:\Development\Arduino\Garage Door Opener\ArduinoGarageConsole\TouchScreen.ino"
#include "D:\Development\Arduino\Garage Door Opener\ArduinoGarageConsole\UserInterface.ino"
#endif
