
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define WIFI_SSID "SSID"                                                  //SSID WiFi 
#define WIFI_PASSWORD "PASS"                                              //PASSWORD 
#define BOT_TOKEN "XXXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"        //isi token bot disni
#define chat_id "XXXXXXXXX"                                              //untuk mengathui chat id mengunakan bot @userinfobot

#define MAGNET_SENSOR 02
uint8_t VALUE_SENSOR;
bool FLAG = true;

const unsigned long BOT_MTBS = 1000;

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime;
bool Start = false;

//Fungsi pesan masuk dari teleram
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));


  for (int i = 0; i < numNewMessages; i++) {
    // String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    //fungsi about
    if (text == "/about") {
      String messAbout = "Bot ini bertujuan untuk memantau keamanan rumah yang berfokus pada pintu rumah. \n";
      messAbout += "Command bot \n";
      messAbout += "/log untuk mengatahui kapan data dikirim. \n";
      messAbout += "/temp untuk req tempratur. \n";
      bot.sendChatAction(chat_id, "typing");
      delay(2000);
      bot.sendMessage(chat_id, messAbout);
    }

    //fungsi log
    if (text == "/log") {
      String messLog = "Maaf untuk saat ini fitur log belum tersedia. \n";
      bot.sendChatAction(chat_id, "typing");
      delay(2000);
      bot.sendMessage(chat_id, messLog);
    }

    //fungsi temp
    if (text == "/temp") {
      String messTemp = "Maaf untuk saat ini fitur temp belum tersedia. \n";
      bot.sendChatAction(chat_id, "typing");
      delay(2000);
      bot.sendMessage(chat_id, messTemp);
    }

    //fungsi awal jika dari telegram mengirim /start
    if (text == "/start") {
      String welcome = "Selamat datang di bot telegram, " + from_name + ".\n";
      welcome += "/about untuk informasi tentang bot ini atau untuk mengetahui lebih lanjut.\n\n";
      welcome += "Terima Kasih\n";
      bot.sendMessage(chat_id, welcome);
    }
  }
}

//Fungsi Sensor
void SensorAction() {
  VALUE_SENSOR = digitalRead(MAGNET_SENSOR);
  // Serial.print(F("Button: "));
  // Serial.println(VALUE_SENSOR);

  //Fungsi jika sensor magnet tidak aktif
  if (VALUE_SENSOR == false && FLAG == true) {
    String sendMessJikaFalse = "Pintu Terbuka.\n";
    sendMessJikaFalse += "Pastikan orang yang membuka pintu adalah orang yang kamu kenal.";
    bot.sendChatAction(chat_id, "typing");
    delay(2000);
    bot.sendMessage(chat_id, sendMessJikaFalse);
    delay(50);
    FLAG = false;
  }

  //Fungsi jika sensor magnet aktif
  if (VALUE_SENSOR == true && FLAG == false) {
    String sendMessJikaTrue = "Pintu Tertutup.\n";
    sendMessJikaTrue += "Pastikan orang yang menutup pintu adalah orang yang kamu kenal.";
    bot.sendChatAction(chat_id, "typing");
    delay(2000);
    bot.sendMessage(chat_id, sendMessJikaTrue);
    delay(50);
    FLAG = true;
  }
  delay(500);
}


void setup() {
  Serial.begin(115200);

  pinMode(MAGNET_SENSOR, INPUT);

  //connect ke wifi
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  //mendapatkan waktu dari internet
  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org");
  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}

void loop() {

  SensorAction();

  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_lasttime = millis();
  }
}
