#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include "./wifi_config.h"

U8G2_SSD1309_128X64_NONAME0_F_SW_I2C u8g2(U8G2_R0, D1, D2, U8X8_PIN_NONE);
const char* city = "Centennial";
const char* state = ",CO";
const char* country = ",US";
String weather = "";
String forecast1 = "";
String forecast2 = "";
String forecast3 = "";
String cityName = "";
const char* daysOfWeek[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" . . .");

  u8g2.begin();
  u8g2.enableUTF8Print();


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println('\n');
  Serial.println("Connection Established");
  Serial.print("IP address: \t");
  Serial.println(WiFi.localIP());

  fetchWeather();
  displayWeather();
}

void loop() {
}

void fetchWeather() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;

    String url = "http://api.openweathermap.org/data/2.5/weather?q=";
    url += city;
    url += state;
    url += country;
    url += "&appid=";
    url += apiKey;
    url += "&units=imperial";

    http.begin(client, url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);

      JsonDocument doc;
      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {
        float temp = doc["main"]["temp"];
        const char* desc = doc["weather"][0]["main"];
        weather = String(temp, 1) + "F " + desc;
        cityName = doc["name"].as<String>();
      } else {
        weather = "JSON error";
      }
    } else {
      weather = "HTTP error";
    }

    http.end();

    // --- Get Forecast ---
    String forecastUrl = "http://api.openweathermap.org/data/2.5/forecast?q=";
    forecastUrl += city;
    forecastUrl += state;
    forecastUrl += country;
    forecastUrl += "&appid=";
    forecastUrl += apiKey;
    forecastUrl += "&units=imperial";

    http.begin(client, forecastUrl);
    httpCode = http.GET();


    if (httpCode > 0) {
      WiFiClient* stream = http.getStreamPtr();
      JsonDocument doc;
      DeserializationError error = deserializeJson(doc, *stream);

      if (!error) {
        for (int i = 0; i < 3; i++) {
          const char* dt_txt = doc["list"][i]["dt_txt"];
          String dateStr = String(dt_txt).substring(0, 10);
          String timeStr = String(dt_txt).substring(11, 16);

          int weekday = getWeekday(dateStr.c_str());
          const char* dayName = daysOfWeek[weekday];

          float temp = doc["list"][i]["main"]["temp"];
          String forecastStr = String(dayName) + " " + timeStr + ": " + String(temp, 0) + "F";

          if (i == 0) forecast1 = forecastStr;
          else if (i == 1) forecast2 = forecastStr;
          else if (i == 2) forecast3 = forecastStr;
        }
      } else {
        Serial.print("JSON ERROR: ");
        Serial.println(error.c_str());
        forecast1 = "JSON error";
        forecast2 = "";
        forecast3 = "";
      }
    } else {
      Serial.print("HTTP error: ");
      Serial.println(httpCode);
      forecast1 = "HTTP error";
      forecast2 = "";
      forecast3 = "";
    }

    http.end();
  } else {
    weather = "No WiFi";
    forecast1 = forecast2 = forecast3 = "";
    cityName = "Offline";
  }
}


void displayWeather() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);

  u8g2.drawStr(0, 10, cityName.c_str());
  u8g2.drawStr(0, 25, weather.c_str());
  u8g2.drawStr(0, 40, forecast1.c_str());
  u8g2.drawStr(0, 51, forecast2.c_str());
  u8g2.drawStr(0, 62, forecast3.c_str());

  u8g2.sendBuffer();
}


String formatTimeWithAmPm(const char* dtTxt) {
  // dtTxt example: "2025-06-07 03:00:00"
  String timeStr = String(dtTxt);

  // Extract hour and minute
  int hour = timeStr.substring(11, 13).toInt();
  int minute = timeStr.substring(14, 16).toInt();

  // Determine AM or PM
  String suffix = "AM";
  if (hour >= 12) {
    suffix = "PM";
    if (hour > 12) hour -= 12;
  } else if (hour == 0) {
    hour = 12;  // midnight hour
  }

  // Format time string (e.g. "3:00PM")
  String hourStr = String(hour);
  String minuteStr = (minute < 10) ? "0" + String(minute) : String(minute);

  return hourStr + ":" + minuteStr + suffix;
}

int getWeekday(const char* dateStr) {
  // Extract year, month, day from dateStr: "YYYY-MM-DD"
  int year = atoi(String(dateStr).substring(0, 4).c_str());
  int month = atoi(String(dateStr).substring(5, 7).c_str());
  int day = atoi(String(dateStr).substring(8, 10).c_str());

  // Zeller's Congruence algorithm to calculate day of week
  if (month < 3) {
    month += 12;
    year -= 1;
  }
  int K = year % 100;
  int J = year / 100;
  int h = (day + 13 * (month + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
  // h = 0: Saturday, 1: Sunday, 2: Monday, ..., 6: Friday

  int d = ((h + 6) % 7);  // Convert to 0=Sunday..6=Saturday
  return d;
}
