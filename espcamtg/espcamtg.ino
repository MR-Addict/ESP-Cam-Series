#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <esp_camera.h>
#include <esp_timer.h>
#include <img_converters.h>
#include <fb_gfx.h>
#include <soc/soc.h>
#include <soc/rtc_cntl_reg.h>

#include "Header.h"
#include "CamConfig.h"
#include "TGHandle.h"
#include "Basic.h"

void setup() {
  SetupInit();
  WifiInit();
}

void loop() {
  if (millis() - lastTimeBotRan > 1000) {
    uint8_t numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
  if (sendPhoto) {
    Serial.println("Preparing photo");
    sendPhotoTelegram();
    sendPhoto = false;
  }
}
