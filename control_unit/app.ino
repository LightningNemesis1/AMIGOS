/*
    Team Amigos
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WS2812FX.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_NeoPixel.h>

#define DEBUG false

#define WIFI_SSID "WHSP"
#define WIFI_PASS "111111112"
#define NUMPIXELS 300

#define DHTPIN D4
#define LED_PIN D5
#define DHTTYPE DHT11

#define HOST_NAME "http://demo.thingsboard.io"
#define AUTH_TOKEN "f0bM3zH6uZuINqGL6J6X"

DHT_Unified dht_internal(DHTPIN, DHTTYPE);
HTTPClient http;
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

float temp_env;
float humidity_env;

float temp_water;

void read_env_data()
{
    sensors_event_t event;
    dht_internal.temperature().getEvent(&event);
#if DEBUG
    if (isnan(event.temperature))
    {
        Serial.println(F("Error reading temperature!"));
    }
#endif
    temp_env = event.temperature;
    dht_internal.humidity().getEvent(&event);
#if DEBUG
    if (isnan(event.relative_humidity))
    {
        Serial.println(F("Error reading humidity!"));
    }
#endif
    humidity_env = event.relative_humidity;
}

void send_data_to_server()
{
    http.begin((String)HOST_NAME + "/api/v1/" + (String)AUTH_TOKEN + "/telemetry");
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST("{\"temperature\": 27.5,\"humidity\": 80.5}");
    String payload = http.getString();
    http.end();
#if DEBUG
    Serial.println("RECVD PAYLOAD : " payload);
#endif
}

void set_led(uint32_t color)
{
    for (int i = 4; i < NUMPIXELS; i++)
        pixels.setPixelColor(i, pixels.Color(color >> 8 & 0xFF, color >> 4 & 0xFF, color & 0xFF));
    pixels.show();
}