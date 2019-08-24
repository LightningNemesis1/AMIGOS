uint32_t last_sent = 0;
void loop()
{
    temp_env = 28.67;
    humidity_env = 70.00;
    // color_current = 0x0;
    set_led(0xFF00FF);
    water_level = 43.66;
    delay(1000);
    // read_env_data();
    // measure_water_level();
    // check_preset_change();
    // Serial.println(String(temp_env) + " " + String(humidity_env));
    // if (millis() - last_sent > 1000)
    // {
    //     last_sent = millis();
    //     send_data_to_server();
    // }
    send_to_display();
}