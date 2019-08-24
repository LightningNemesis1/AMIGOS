/*
    Team Amigos
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_NeoPixel.h>
#include <PID_v1.h>

#define DEBUG true

#define WIFI_SSID "WHSP"
#define WIFI_PASS "111111112"
#define NUMPIXELS 300

#define DHTPIN D8
#define LED_PIN D4
#define WATER_LEV_IND_PIN D6
#define PRESET_PIN1 D7
#define PRESET_PIN2 D8
#define DHTTYPE DHT11

#define HOST_NAME "http://demo.thingsboard.io"
#define AUTH_TOKEN "f0bM3zH6uZuINqGL6J6X"

double input, output, setpoint;

DHT_Unified dht_internal(DHTPIN, DHTTYPE);
HTTPClient http;
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
PID temp_control(&input, &output, &setpoint, 20.0, 0.0, 0.0, DIRECT);

float temp_env = 0.0;
float humidity_env = 0.0;

float temp_water = 0.0;
uint8_t water_level = 0;

uint32_t color_current = 0x0;

struct preset_stages
{
    int days;
    uint32_t color;
    float temp;
};

enum presets
{
    TOMATO = 1,
    SPINACH = 2
};

uint32_t preset_start_time;
// bool preset_changed;
uint8_t selected_preset = 0;

preset_stages tomato[5] = {
    {18, 0xFF0000, 25.0},
    {32, 0xFF7233, 25.0},
    {58, 0xFFB43C, 25.0},
    {75, 0xFF00B4, 25.0},
    {90, 0xFFFFC8, 25.0}};

preset_stages spinach[4] = {
    {18, 0xFF0000, 25.0},
    {32, 0xFF7233, 25.0},
    {58, 0xFFB43C, 25.0},
    {75, 0xFF00B4, 25.0}};

void read_env_data()
{
    sensors_event_t event;
    dht_internal.temperature().getEvent(&event);

    if (isnan(event.temperature))
    {
        temp_env = (temp_env == 0.0) ? 28.0 : temp_env; // Dummy Temp
#if DEBUG
        Serial.println(F("Error reading temperature!"));
#endif
    }
    else
        temp_env = event.temperature;
    dht_internal.humidity().getEvent(&event);
    if (isnan(event.relative_humidity))
    {
        humidity_env = (humidity_env == 0.0) ? 60.0 : humidity_env; //Dummy Humidity
#if DEBUG
        Serial.println(F("Error reading humidity!"));
#endif
    }
    else
        humidity_env = event.relative_humidity;
}

String get_json()
{
    String json = "{";
    json += "\"temperature\": " + String(temp_env);
    json += ",\"humidity\": " + String(humidity_env);
    json += ",\"RGB\": " + String(color_current);
    json += ",\"w_level\": " + String(water_level);
    json += "}";
    return json;
}
void send_data_to_server()
{
    http.begin((String)HOST_NAME + "/api/v1/" + (String)AUTH_TOKEN + "/telemetry");
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(get_json());
    String payload = http.getString();
    http.end();
#if DEBUG
    Serial.println("RECVD PAYLOAD : " + payload);
#endif
}

void send_to_display()
{
    Serial.println(get_json());
}

void set_led(uint32_t color)
{
    float red_current = color_current >> 16 & 0xFF;
    float green_current = color_current >> 8 & 0xFF;
    float blue_current = color_current & 0xFF;
    uint8_t red_set = color >> 16 & 0xFF;
    uint8_t green_set = color >> 8 & 0xFF;
    uint8_t blue_set = color & 0xFF;
    // Serial.println(red_current);
    // Serial.println(green_current);
    // Serial.println(blue_current);

    // Serial.println(red_set);
    // Serial.println(green_set);
    // Serial.println(blue_set);

    float alpha = 0.02;
    while (abs(red_current - red_set) > 2.0 || abs(blue_current - blue_set) > 2.0 || abs(green_current - green_set) > 2.0)
    {
        red_current += alpha * float(red_set - red_current);
        blue_current += alpha * float(blue_set - blue_current);
        green_current += alpha * float(green_set - green_current);
        for (int i = 0; i < NUMPIXELS; i++)
            pixels.setPixelColor(i, pixels.Color((int)red_current, (int)green_current, (int)blue_current));
        pixels.show();
#if DEBUG
        Serial.println("Changing LED Color");
        Serial.println(red_current);
        Serial.println(blue_current);
        Serial.println(green_current);
#endif
        delay(20);
    }
    color_current = color;
}

void measure_water_level()
{
}

void set_peltier_output(int power)
{
}

void check_preset_change()
{
}

void run_preset_routine()
{
    static uint8_t current_preset = 0;
    float set_temp;
    int stage;
    if (current_preset != selected_preset)
    {
        // preset_stage = 0;
        current_preset = selected_preset;
    }
    if (current_preset == TOMATO)
    {
        for (stage = 0; stage < 5; stage++)
            if (map(millis() - preset_start_time, 0, 20000, 0, 18) < tomato[stage].days)
                break;
        set_temp = tomato[stage].temp;
        set_led(tomato[stage].color);
    }
    else if (current_preset == SPINACH)
    {
        for (stage = 0; stage < 4; stage++)
            if (map(millis() - preset_start_time, 0, 20000, 0, 18) < spinach[stage].days)
                break;
        set_temp = spinach[stage].temp;
        set_led(spinach[stage].color);
    }
    input = temp_env;
    temp_control.Compute();
    set_peltier_output(output);
}