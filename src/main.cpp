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

#include <Arduino.h>
#include <SimpleTimer.h>
#include <Bounce2.h>
#include <Encoder.h>
#include <U8g2lib.h>
#include <TimerOne.h>
#include "main.h"

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

Bounce debounce = Bounce();
Encoder myEnc(ENCODER_A, ENCODER_B);
SimpleTimer simpTimer1;

// Spotlight VirtSpot[MAX_LIGHTS + 1];

U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C u8g2(U8G2_R2, /* reset=*/U8X8_PIN_NONE); // Adafruit ESP8266/32u4/ARM Boards + FeatherWing OLED

void setup() {

  Timer1.initialize(255); // Initialize Timer1 with a period of 255uS
  Timer1.pwm(LED_PIN, 0); // Duty cycle of 0%

  u8g2.begin();

  //Display Splash
  drawSplash();

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  debounce.attach(BUTTON_PIN);
  debounce.interval(30);

  simpTimer1.setInterval(50UL, updateDisplay);
  sleepTimer = simpTimer1.setInterval(SLEEP_DELAY, fallAsleep);
}

void loop() {
  int16_t encoderNewPos = myEnc.read() >> 2;
  if (encoderNewPos != encoderPos) {
    encoderMove = encoderNewPos - encoderPos;
    encoderPos = encoderNewPos;
    if (asleep) {
      wakeUp();
    } else {
      encoderHandle();
      simpTimer1.restartTimer(sleepTimer);
    }
  }

  simpTimer1.run();
  debounce.update();

  if (debounce.rose()) {
    //button up
    if (asleep) {
      wakeUp();
    } else {
      knobAction = 0;
      simpTimer1.restartTimer(sleepTimer);
    }
  }
  if (debounce.fell()) {
    //button down
    if (asleep) {
      wakeUp();
    } else {
      knobAction = 1;
      simpTimer1.restartTimer(sleepTimer);
    }
  }

}

void updateDisplay() {
  if (displayDirty) {
    u8g2.firstPage();
    do {
      draw();
    } while (u8g2.nextPage());
    displayDirty = false;
  }
}

void drawSplash() {
  u8g2.firstPage();
  do {
    u8g2.setDrawColor(1);
    u8g2.setFont(u8g2_font_helvR08_tf);
    u8g2.setCursor(0, 10);
    u8g2.print(F("LED Dimmer Control"));
    u8g2.setCursor(0, 20);
    u8g2.print(F("Version "));
    u8g2.print(F(LEDDIMMERCONTROL_VERSION));
    u8g2.setCursor(0, 30);
    u8g2.print(compile_date);
  } while (u8g2.nextPage());
  delay(SPLASH_DELAY);
}

void draw() {
  u8g2.setDrawColor(1);
  u8g2.setCursor(68, 9);
  u8g2.setFont(u8g2_font_helvR08_tf);
}

void encoderHandle() {
  ledDirty = true;
  displayDirty = true;
}

void fallAsleep()
{
  if (!asleep)
  {
    asleep = 1;
    simpTimer1.disable(sleepTimer);
    u8g2.setPowerSave(1);
  }
}

void wakeUp()
{
  if (asleep)
  {
    asleep = 0;
    simpTimer1.restartTimer(sleepTimer);
    simpTimer1.enable(sleepTimer);
    u8g2.setPowerSave(0);
  }
}
