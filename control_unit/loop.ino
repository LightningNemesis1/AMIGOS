void loop()
{
    delay(100);
    // read_env_data();
    // Serial.println(String(temp_env) + " " + String(humidity_env));
    send_data_to_server();
}