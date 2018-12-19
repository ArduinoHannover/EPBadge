// Library: https://github.com/ZinggJM/GxEPD/
#include <GxEPD.h>
#include <GxFont_GFX.h>
#include "ESP8266WiFi.h"

#define SWR

#include "Fonts/FreeSans18pt7b.h"

#include "35c3.h"

#define NAME "Super Mario"

#ifdef SWR
#include <GxGDEW027C44/GxGDEW027C44.cpp>    // 2.7" b/w/r
const bool HAS_RED = 1;
#else
#include <GxGDEW027W3/GxGDEW027W3.cpp>      // 2.7" b/w
const bool HAS_RED = 0;
#endif

#include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
#include <GxIO/GxIO.cpp>

#define SLEEP_TIME   20e6 //20s

#define MODES           2

const uint8_t
MOSI_PIN = 13,
CLK_PIN  = 14,
CS_PIN   = 15,
BUSY_PIN =  5,
RST_PIN  =  2,
DC_PIN   =  4,
BTN_O    =  0,
BTN_UP   =  1,
BTN_DOWN =  3,
BTN_X    = 12;

GxIO_Class io(SPI, CS_PIN, DC_PIN, RST_PIN);
GxEPD_Class display(io, RST_PIN, BUSY_PIN);

uint32_t rtcData;

void setup() {
  WiFi.forceSleepBegin();
  Serial.begin(115200);

  display.init();

  pinMode(BTN_O, INPUT_PULLUP);
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_X, INPUT_PULLUP);

  display.setRotation(3); // 1 = Anhänger unten; 3 = Anhänger oben

  //COUNTER LESEN
  ESP.rtcUserMemoryRead(0, (uint32_t*) &rtcData, sizeof(rtcData));
  //RESET DES COUNTERS
  if (!digitalRead(BTN_X)) rtcData = 0;
  rtcData++;
  //COUNTER SCHREIBEN
  ESP.rtcUserMemoryWrite(0, (uint32_t*) &rtcData, sizeof(rtcData));

  display.fillScreen(GxEPD_BLACK);
  
  display.setTextColor(GxEPD_WHITE);
  display.setFont(&FreeSans18pt7b);

  switch (rtcData % MODES) {
    case 0:
      display.drawBitmap(CC35c3_1, 20, 0, 224, 176, HAS_RED ? GxEPD_RED : GxEPD_WHITE, display.bm_transparent /*| display.bm_invert*/);
      break;
    case 1:
      display.drawBitmap(CC35c3_2, 20, 49, 224, 77, HAS_RED ? GxEPD_RED : GxEPD_WHITE, display.bm_transparent /*| display.bm_invert*/);
	  display.setCursor(15, 176);
	  display.print(NAME);
      break;
  }
  display.update();

  // Schlafen
  ESP.deepSleep(SLEEP_TIME, WAKE_RF_DEFAULT);
}

void loop() {

}
