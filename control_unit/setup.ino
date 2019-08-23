void setup()
{
    Serial.begin(115200);
    dht_internal.begin();
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {

        delay(500);
        Serial.println("Waiting for connection");
    }
    pixels.begin();
    pixels.clear();
}