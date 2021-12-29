void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Page Not found");
}

void ServerInit() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/favicon.png", "image/png");
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  server.on("/index.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.js", "text/js");
  });

  server.on("/capturePhoto", HTTP_GET, [](AsyncWebServerRequest * request) {
    takeNewPhoto = true;
    request->send_P(200, "text/plain", "Taking Photo");
  });

  server.on("/photo", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, FILE_PHOTO, "image/jpg", false);
  });

  server.onNotFound(notFound);
  server.begin();
}
