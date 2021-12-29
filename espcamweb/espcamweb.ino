#include <WiFi.h>
#include <soc/soc.h>
#include <soc/rtc_cntl_reg.h>
#include <esp_camera.h>
#include <esp_timer.h>
#include <img_converters.h>
#include <fb_gfx.h>
#include <soc/soc.h>
#include <soc/rtc_cntl_reg.h>
#include <esp_http_server.h>

#include "Header.h"
#include "CamConfig.h"
#include "CamHandle.h"
#include "Basic.h"

void setup() {
  SetupInit();
  WifiInit();
}

void loop() {
  delay(1);
}
