#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <esp_camera.h>

#include <esp_timer.h>
#include <soc/soc.h>
#include <soc/rtc_cntl_reg.h>
#include <img_converters.h>
#include <StringArray.h>
#include <fb_gfx.h>
#include <FS.h>

#include "Header.h"
#include "CamConfig.h"
#include "CamHandle.h"
#include "Web.h"
#include "Basic.h"

void setup() {
  SetupInit();
  ServerInit();
}

void loop() {
  if (takeNewPhoto) {
    capturePhotoSaveSpiffs();
    takeNewPhoto = false;
  }
}
