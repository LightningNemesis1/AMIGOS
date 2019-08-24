void setup()
{
    Serial.begin(9600);
    dht_internal.begin();
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {

        delay(500);
#if DEBUG
        Serial.println("Waiting for connection");
#endif
    }
    pixels.begin();
    pixels.clear();
    temp_control.SetOutputLimits(-100.0, 100.0);
    temp_control.SetMode(AUTOMATIC);
    pinMode(WATER_LEV_IND_PIN, INPUT);
    pinMode(PRESET_PIN1, INPUT);
    pinMode(PRESET_PIN2, INPUT);
}