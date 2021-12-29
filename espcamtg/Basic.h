void SetupInit() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  configInitCamera();
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LEDStatus);
}

void WifiInit() {
  WiFi.begin(ssid, password);
  clientTCP.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.println(WiFi.localIP());
}
