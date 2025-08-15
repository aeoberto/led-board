#include <Adafruit_Protomatter.h>
#include <Adafruit_GFX.h>
#include "Arduino.h"
#include <EEPROM.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
String part1;
String part2;
String part3;
String formattedDate;
String dayStamp;
String timeStamp;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -5 * 3600);
const char* ssid = "ioteqALL2.4";
const char* password = "ioteq2017";
String text;
String id;
int preset;
int adress;
char real_text[100];
boolean newData = false;
int choice;
int color_choice;
int real_choice;
int re = 0;
int size;
int real_size;
char textBuffer[64];
int16_t xx, yy;
uint16_t w, h;
int x;
int16_t y;
uint8_t z = 3;
String past_time;

uint8_t rgbPins[]   = { 42, 41, 40, 38, 39, 37 };   
uint8_t addrPins[]  = { 45, 36, 48, 35 };           
uint8_t clockPin    = 2;
uint8_t latchPin    = 47;
uint8_t oePin       = 14;

Adafruit_Protomatter matrix(
  64,         // Width of panel
  6,          // Bit depth (default is 6)
  1,          // Only one panel
  rgbPins,
  4,          // 4 address lines (for 1:16 scan)
  addrPins,
  clockPin,
  latchPin,
  oePin,
  false,      // Double buffering
  -2
);


//Update anytime you make a change
String Version = "v1.0.1";
//red, green, blue, white, pink, yellow, orange
uint16_t cols[] = { matrix.color565(255, 0, 0), matrix.color565(0, 255, 0),
 matrix.color565(0, 0, 255), matrix.color565(255, 255, 255), matrix.color565(255, 192, 203), matrix.color565(255, 215, 0), matrix.color565(255, 165, 0)};

String pre[4] = { " ", " ", " ", " " };

#include <esp_wifi.h>




void setup(void) {

  Serial.begin(9600);
  EEPROM.begin(512);
  matrix.begin();





  



  matrix.setTextSize(1);
  matrix.getTextBounds("Hi, I'm DotDot. Status? I'm always on point", 0, 0, &xx, &yy, &w, &h);
  x = (matrix.width() - w) / 2;
  matrix.setCursor(0, 0);
  matrix.setTextColor(matrix.color565(255, 255, 255));
  matrix.setTextColor(cols[2]);
  matrix.print("Hi I'm DotDot Status Always on point");
  matrix.show();

  delay(5000);
  matrix.fillScreen(0x000000);

    matrix.setTextSize(1);
  matrix.getTextBounds(Version, 0, 0, &xx, &yy, &w, &h);
  x = (matrix.width() - w) / 2;
  matrix.setCursor(28, 22);
  matrix.setTextColor(matrix.color565(255, 255, 255));
  matrix.setTextColor(cols[2]);
  matrix.print(Version);
  matrix.show();

  delay(2000);
  matrix.fillScreen(0x000000);

    matrix.setTextSize(1);
  matrix.getTextBounds("Connecting to WIFI", 0, 0, &xx, &yy, &w, &h);
  x = (matrix.width() - w) / 2;
  matrix.setCursor(0, 0);
  matrix.setTextColor(matrix.color565(255, 255, 255));
  matrix.setTextColor(cols[2]);
  matrix.print("Connecting to WIFI");
  matrix.show();

 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
    
    id = WiFi.macAddress();
    Serial.println(id);
    timeClient.begin();
    timeClient.update();
  
  // Get time formatted as HH:MM:SS
  String formattedTime = timeClient.getFormattedTime().substring(0, 5);
  
  Serial.print("Time: ");
  Serial.println(formattedTime);

  matrix.fillScreen(0x000000);
  matrix.setTextSize(2);
  matrix.getTextBounds(formattedTime, 0, 0, &xx, &yy, &w, &h);
  x = (matrix.width() - w) / 2;
  matrix.setCursor(0, 0);
  matrix.setTextColor(matrix.color565(255, 255, 255));
  matrix.setTextColor(cols[2]);
  matrix.print(formattedTime);
  matrix.show();
delay(5000);
  matrix.fillScreen(0x000000);






}


void loop(void) {
  if((timeClient.getFormattedTime().substring(4, 5) == "0" || timeClient.getFormattedTime().substring(4, 5) == "5") && timeClient.getFormattedTime().substring(0, 5) != past_time){
    time();
  }
  
 if(re == 0){
    request();
 }
}

void request(){
  re = 1;

  matrix.fillScreen(0x000000);
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://3.12.155.102:3001/hey/" + id);

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      text = http.getString();
      Serial.println(text);
    }
              


    

    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }
    int firstStar = text.indexOf('*');
  int secondStar = text.indexOf('*', firstStar + 1);

   part1 = text.substring(0, firstStar);
   part2 = text.substring(firstStar + 1, secondStar);
   part3 = text.substring(secondStar + 1);
  Serial.println("Part 1: " + part1);
  Serial.println("Part 2: " + part2);
  Serial.println("Part 3: " + part3);
int c =0 ;
if (part3 != " ") {
  while(c < 30){
      if(c%2 == 0){matrix.fillScreen(0x000000);  
      matrix.setTextSize(2);
      matrix.getTextBounds("Im    Here", 0, 0, &xx, &yy, &w, &h);
      x = (matrix.width() - w) / 2;
      matrix.setCursor(x, 0);
      matrix.setTextColor(cols[0]);
      matrix.print("Im    Here");
      matrix.show();
      delay(1000); }else{
        matrix.fillScreen(0x000000);
        matrix.show();
        delay(500);
      }
      c++;
  }
}
matrix.fillScreen(0x000000);  

  matrix.setTextSize(1);
  matrix.getTextBounds(part1, 0, 0, &xx, &yy, &w, &h);
  x = (matrix.width() - w) / 2;
  matrix.setCursor(x, 0);
  matrix.setTextColor(cols[part2.toInt() - 1]);
  matrix.print(part1);
  matrix.show();
    delay(1000 * 30);
  re = 0;

}

void time(){
  String formattedTime = timeClient.getFormattedTime().substring(0, 5);
  past_time = timeClient.getFormattedTime().substring(0, 5);
  
  Serial.print("Time: ");
  Serial.println(formattedTime);

  matrix.fillScreen(0x000000);
  matrix.setTextSize(2);
  matrix.getTextBounds(formattedTime, 0, 0, &xx, &yy, &w, &h);
  x = (matrix.width() - w) / 2;
  matrix.setCursor(0, 0);
  matrix.setTextColor(matrix.color565(255, 255, 255));
  matrix.setTextColor(cols[2]);
  matrix.print(formattedTime);
  matrix.show();
delay(3000);
  matrix.fillScreen(0x000000);
   matrix.setTextSize(1);
  matrix.getTextBounds(part1, 0, 0, &xx, &yy, &w, &h);
  x = (matrix.width() - w) / 2;
  matrix.setCursor(x, 0);
  matrix.setTextColor(cols[part2.toInt() - 1]);
  matrix.print(part1);
  matrix.show();
    
}

