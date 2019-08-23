void homeScr()
{
  lcd.setCursor(4, 1);
  lcd.print("DEMETER 1.1");
  lcd.setCursor(1, 3);
  lcd.print("***Team AMIGOS***");
}

void infoScr()
{
  /*
     Temp:@@@ Water:@@%..
     Lock Stat:@@@.......
     Elapsed Time: hh:mm.
     Press to go back....


  */
  map_x();
  Serial.println(vx);
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(w_temp);
  lcd.printByte(1);
  lcd.print("C");
  lcd.setCursor(10, 0);
  lcd.print("H20 L:");
  lcd.print(w_level);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Run time: ");
  lcd.print(millis() / 1000);
  lcd.print(" secs");
  lcd.setCursor(0, 3);
  lcd.print("Slide ");
  lcd.printByte(7);
  lcd.print(" to return ");

  delay(500);
}

void navScr()
{
  /*
      .
     ->*Sensor Data
   *   *Preset 1
   *   *Connectivity ops


  */
  lcd.setCursor(3, 0);
  lcd.print("Sensor Data");
  lcd.setCursor(3, 1);
  lcd.print("Preset 1");
  lcd.setCursor(3, 2);
  lcd.print("Connectivity");
  lcd.setCursor(0, 3);
  lcd.print("Slide ");
  lcd.printByte(7);
  lcd.print(" to return ");
}


void tomato()
{
  current = millis();
  /*
    targt temp|curr temp
    ---@@*C---|--@@*C---
    ----R-----G-----B---
    --100%--100%--100%--
  */

  lcd.setCursor(0, 0);
  lcd.print("Targt Temp|Curr Temp");
  lcd.setCursor(4, 1);
  lcd.print(75);
  lcd.printByte(1);
  lcd.print("C   |  ");
  lcd.print(w_temp);
  lcd.printByte(1);
  lcd.print("C");

  while (millis() - current < 20000)
  {
    lcd.setCursor(5, 2);
    lcd.print("R     G     B");
    lcd.setCursor(3, 3);
    lcd.print(rP);
    lcd.print("%  ");
    lcd.print(gP);
    lcd.print("%  ");
    lcd.print(bP);
    lcd.print("%");
  }
  rP = 100, gP = 20, bP = 0;
  current = millis();
  while (millis() - current < 16000)
  {
    lcd.setCursor(5, 2);
    lcd.print("R     G     B");
    lcd.setCursor(3, 3);
    lcd.print(rP);
    lcd.print("%  ");
    lcd.print(gP);
    lcd.print("%  ");
    lcd.print(bP);
    lcd.print("%");
  }
  rP = 100, gP = 0, bP = 50;
  current = millis();
  while (millis() - current < 24000)
  {
    lcd.setCursor(5, 2);
    lcd.print("R     G     B");
    lcd.setCursor(3, 3);
    lcd.print(rP);
    lcd.print("%  ");
    lcd.print(gP);
    lcd.print("%  ");
    lcd.print(bP);
    lcd.print("%");
  }
  rP = 20, gP = 0, bP = 100;
  current = millis();
  while (millis() - current < 25000)
  {
    lcd.setCursor(5, 2);
    lcd.print("R     G     B");
    lcd.setCursor(3, 3);
    lcd.print(rP);
    lcd.print("%  ");
    lcd.print(gP);
    lcd.print("%  ");
    lcd.print(bP);
    lcd.print("%");
  }
}

void spinach()
{
  current = millis();
  /*
    targt temp|curr temp
    ---@@*C---|--@@*C---
    ----R-----G-----B---
    --100%--100%--100%--
  */

  lcd.setCursor(0, 0);
  lcd.print("Targt Temp|Curr Temp");
  lcd.setCursor(4, 1);
  lcd.print(21);
  lcd.printByte(1);
  lcd.print("C   |  ");
  lcd.print(w_temp);
  lcd.printByte(1);
  lcd.print("C");

  while (millis() - current < 11000)
  {
    lcd.setCursor(5, 2);
    lcd.print("R     G     B");
    lcd.setCursor(3, 3);
    lcd.print(rP);
    lcd.print("%  ");
    lcd.print(gP);
    lcd.print("%  ");
    lcd.print(bP);
    lcd.print("%");
  }
  rP = 100, gP = 10, bP = 10;
  current = millis();
  while (millis() - current < 12000)
  {
    lcd.setCursor(5, 2);
    lcd.print("R     G     B");
    lcd.setCursor(3, 3);
    lcd.print(rP);
    lcd.print("%  ");
    lcd.print(gP);
    lcd.print("%  ");
    lcd.print(bP);
    lcd.print("%");
  }
  rP = 100, gP = 25, bP = 26;
  current = millis();
  while (millis() - current < 24000)
  {
    lcd.setCursor(5, 2);
    lcd.print("R     G     B");
    lcd.setCursor(3, 3);
    lcd.print(rP);
    lcd.print("%  ");
    lcd.print(gP);
    lcd.print("%  ");
    lcd.print(bP);
    lcd.print("%");
  }
}

void conn()
{

}
