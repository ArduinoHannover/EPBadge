// Library: https://github.com/ZinggJM/GxEPD/
#include <GxEPD.h>
#include <GxFont_GFX.h>
#include "ESP8266WiFi.h" //WiFi.forceSleepBegin();

#include "hannio.h"
#include "arduinohannover.h"

#include <GxGDEW027C44/GxGDEW027C44.cpp>    // 2.7" b/w/r
//#include <GxGDEW027W3/GxGDEW027W3.cpp>      // 2.7" b/w

#include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
#include <GxIO/GxIO.cpp>

#define SLEEP_TIME   20e6 //20s

#define MODES           5

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
  
  display.init();
  // Taster initialisieren, nachdem SPI initialisiert wurde (MISO)
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
  
  
  display.fillScreen(GxEPD_WHITE);
  display.setTextSize(2);
  display.setTextColor(GxEPD_BLACK);
  display.drawBitmap(arduino_hannover_small, display.width() - 129, display.height() - 46 - 16, 128, 45, GxEPD_BLACK, display.bm_transparent | display.bm_invert);

  switch (rtcData % MODES) {
    case 0:
      break;
    case 1:
      display.fillScreen(GxEPD_BLACK);
      display.drawBitmap(hannio, 8, 58, 248, 59, GxEPD_RED, display.bm_transparent | display.bm_invert);
      break;
    case 2:
      display.setTextSize(2);
      display.setTextColor(GxEPD_BLACK);
      display.setCursor(0, 50);
      display.print("Luca Zimmermann");
      break;
    case 3:
      display.fillScreen(GxEPD_BLACK);
      display.setTextColor(GxEPD_WHITE);
      break;
    case 4:
      break;
  }
  
  display.setCursor(0, display.height() - 16);
  // Spannung berechnen
  display.print(analogRead(A0) * 4.4 / 1000.0);
  display.print(" V, Zyklus: ");
  display.print(rtcData);
  display.update();

  // Schlafen
  ESP.deepSleep(SLEEP_TIME, WAKE_RF_DEFAULT);
}

void loop() {

}
