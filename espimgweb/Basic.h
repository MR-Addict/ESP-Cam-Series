void SetupInit() {
  SPIFFS.begin();
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.println(WiFi.localIP());
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  ConfigInitCamera();
}
