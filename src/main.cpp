/*
   LED Dimmer Control
   by J. Lance Cotton <joe@lightningflash.net>

   For use with single-channel LED strip lights on Arduino Pro Mini

   Connections:
     Dimmer pin: 10
     Encoder A: 2
     Encoder B: 3
     Encoder Pushbutton: 4 (with pullup)
     I2C Display SDA: A4 (closest to ATMega328p)
     I2C Display SDC: A5
*/

#define LEDDIMMERCONTROL_VERSION "0.10"

#include <Arduino.h>
#include <SimpleTimer.h>
#include <Bounce2.h>
#include <Encoder.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

const char compile_date[] = __DATE__ " " __TIME__;

const uint8_t UPDATES_PER_SECOND = 15;
const uint8_t BUTTON_PIN = 4;
const uint8_t ENCODER_A = 2;
const uint8_t ENCODER_B = 3;
const uint8_t LED_PIN = 10;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}