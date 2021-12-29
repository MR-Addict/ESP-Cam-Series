const char* ssid = "510_2.4GHz";
const char* password = "510lab666";

String BOTtoken = "5045007315:AAGusC_6QdXNPKai5cX93WWUNby9wpisaCc";
String CHAT_ID = "";

const uint8_t LED = 4;
bool sendPhoto = false;
bool LEDStatus = LOW;
unsigned long lastTimeBotRan;

WiFiClientSecure clientTCP;
UniversalTelegramBot bot(BOTtoken, clientTCP);
