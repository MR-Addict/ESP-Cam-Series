#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define WIFI_SSID "HIPAA"
#define WIFI_PASSWORD "123456789"
#define BOT_TOKEN "5045007315:AAGusC_6QdXNPKai5cX93WWUNby9wpisaCc"

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

unsigned long lastTimeBotRan;
const uint8_t LED = 2;
bool LEDStatus;

void handleNewMessages(uint8_t numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chatid = bot.messages[i].chat_id;
    String message = bot.messages[i].text;
    String fromname = bot.messages[i].from_name;

    Serial.println(message);
    String welcome = "Welcome, " + fromname + ".\n";
    welcome += "You can use following commands to control LED:\n";
    welcome += "/led_on to turn LED ON\n";
    welcome += "/led_off to turn LED OFF\n";
    welcome += "/toggle_led to toggle LED\n";
    welcome += "/led_status to request current LED status\n";

    if (message == "/start")bot.sendMessage(chatid, welcome);
    else if (message == "/led_on")LEDStatus = true;
    else if (message == "/led_off")LEDStatus = false;
    else if (message == "/toggle_led")LEDStatus = !LEDStatus;
    else if (message == "/led_status")bot.sendMessage(chatid, LEDStatus ? "LED ON" : "LED OFF", "");
    else bot.sendMessage(chatid, message);
    digitalWrite(LED, LEDStatus);
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.println(WiFi.localIP());

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LEDStatus);
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
}
