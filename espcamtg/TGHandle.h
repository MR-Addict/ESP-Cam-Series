void handleNewMessages(uint8_t numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chatid = bot.messages[i].chat_id;
    String message = bot.messages[i].text;
    String fromname = bot.messages[i].from_name;
    String text = bot.messages[i].text;
    CHAT_ID = chatid;

    Serial.println(text);
    String welcome = "Welcome, " + fromname + ".\n";
    welcome += "You can use following commands to control LED:\n";
    welcome += "/photo to take a new photo\n";
    welcome += "/led_on to turn LED ON\n";
    welcome += "/led_off to turn LED OFF\n";
    welcome += "/toggle_led to toggle LED\n";
    welcome += "/led_status to request current LED status\n";
    if (message == "/start")bot.sendMessage(chatid, welcome);
    else if (message == "/led_on")LEDStatus = true;
    else if (message == "/led_off")LEDStatus = false;
    else if (message == "/toggle_led")LEDStatus = !LEDStatus;
    else if (message == "/led_status")bot.sendMessage(chatid, LEDStatus ? "LED ON" : "LED OFF");
    else if (message == "/photo")sendPhoto = true;
    else bot.sendMessage(chatid, message);
    digitalWrite(LED, LEDStatus);
  }
}

String sendPhotoTelegram() {
  const char* myDomain = "api.telegram.org";
  String getAll = "";
  String getBody = "";

  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    delay(1000);
    ESP.restart();
    return "Camera capture failed";
  }

  Serial.println("Connect to " + String(myDomain));


  if (clientTCP.connect(myDomain, 443)) {
    Serial.println("Connection successful");

    String head = "--RandomNerdTutorials\r\nContent-Disposition: form-data; name=\"chat_id\"; \r\n\r\n" + CHAT_ID + "\r\n--RandomNerdTutorials\r\nContent-Disposition: form-data; name=\"photo\"; filename=\"esp32-cam.jpg\"\r\nContent-Type: image/jpeg\r\n\r\n";
    String tail = "\r\n--RandomNerdTutorials--\r\n";

    uint16_t imageLen = fb->len;
    uint16_t extraLen = head.length() + tail.length();
    uint16_t totalLen = imageLen + extraLen;

    clientTCP.println("POST /bot" + BOTtoken + "/sendPhoto HTTP/1.1");
    clientTCP.println("Host: " + String(myDomain));
    clientTCP.println("Content-Length: " + String(totalLen));
    clientTCP.println("Content-Type: multipart/form-data; boundary=RandomNerdTutorials");
    clientTCP.println();
    clientTCP.print(head);

    uint8_t *fbBuf = fb->buf;
    size_t fbLen = fb->len;
    for (size_t n = 0; n < fbLen; n = n + 1024) {
      if (n + 1024 < fbLen) {
        clientTCP.write(fbBuf, 1024);
        fbBuf += 1024;
      }
      else if (fbLen % 1024 > 0) {
        size_t remainder = fbLen % 1024;
        clientTCP.write(fbBuf, remainder);
      }
    }

    clientTCP.print(tail);
    esp_camera_fb_return(fb);

    int waitTime = 10000;   // timeout 10 seconds
    long startTimer = millis();
    boolean state = false;

    while ((startTimer + waitTime) > millis()) {
      Serial.print(".");
      delay(100);
      while (clientTCP.available()) {
        char c = clientTCP.read();
        if (state == true) getBody += String(c);
        if (c == '\n') {
          if (getAll.length() == 0) state = true;
          getAll = "";
        }
        else if (c != '\r')
          getAll += String(c);
        startTimer = millis();
      }
      if (getBody.length() > 0) break;
    }
    clientTCP.stop();
    Serial.println();
    Serial.println(getBody);
  }
  else {
    getBody = "Connected to api.telegram.org failed.";
    Serial.println("Connected to api.telegram.org failed.");
  }
  return getBody;
}
