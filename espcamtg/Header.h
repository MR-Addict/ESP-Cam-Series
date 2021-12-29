const char* ssid = "510_2.4GHz";
const char* password = "510lab666";

String BOTtoken = "XXXXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
String CHAT_ID = "";

const uint8_t LED = 4;
bool sendPhoto = false;
bool LEDStatus = LOW;
unsigned long lastTimeBotRan;

WiFiClientSecure clientTCP;
UniversalTelegramBot bot(BOTtoken, clientTCP);
