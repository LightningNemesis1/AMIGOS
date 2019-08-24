void homeScr()
{
  lcd.setCursor(4, 1);
  lcd.print("DEMETER 1.1");
  lcd.setCursor(0, 3);
  lcd.print("____Team AMIGOS_____");
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
  lcd.print(amb_temp);
  lcd.printByte(1);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Water Level:");
  lcd.print(w_level);
  lcd.print("%");
  lcd.setCursor(0, 2);
  lcd.print("Humidity: ");
  lcd.print(amb_humid);
  lcd.print(" mm");
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
   *   *Presets

  */
  lcd.setCursor(3, 0);
  lcd.print("Sensor Data");
  lcd.setCursor(3, 1);
  lcd.print("Preset Modes");
  
  lcd.setCursor(0, 3);
  lcd.print("Slide ");
  lcd.printByte(7);
  lcd.print(" to return ");
}

void preScr()
{
  tomato();
}


void tomato()
{
  current = millis();
  if(flag==0)
  {
    lcd.setCursor(4,1);
    lcd.print("Tomato Mode");
    lcd.setCursor(4,2);
    lcd.print("___________");
    delay(3000);
    flag++;
    lcd.clear();
  }
  lcd.setCursor(0, 0);
  lcd.print("Targt Temp|Curr Temp");
  lcd.setCursor(2, 1);
  lcd.print(24);
  lcd.printByte(1);
  lcd.print("C    | ");
  lcd.print(amb_temp);
  lcd.printByte(1);
  lcd.print("C");

  while (millis() - current < 2000)
  {
    lcd.setCursor(4, 2);
    lcd.print("R     G     B");
    lcd.setCursor(3, 3);
    lcd.print(rgb1[0]);
    lcd.print("%  ");
    lcd.print(rgb1[1]);
    lcd.print("%  ");
    lcd.print(rgb1[2]);
    lcd.print("%");
  }
  
  lcd.setCursor(0,3); //Eraser
  for(j=0;j<4;j++)
  {
    lcd.print(" ");
  }
  rgb1[0] = 100, rgb1[1] = 20, rgb1[2] = 0;
  current = millis();

  
  
  while (millis() - current < 1600)
  {
    lcd.setCursor(5, 2);
    lcd.print("R     G     B");
    lcd.setCursor(3, 3);
    lcd.print(rgb1[0]);
    lcd.print("%  ");
    lcd.print(rgb1[1]);
    lcd.print("%  ");
    lcd.print(rgb1[2]);
    lcd.print("%");
  }
  lcd.setCursor(0,3); //Eraser
  for(j=0;j<4;j++)
  {
    lcd.print(" ");
  }
  rgb1[0] = 100, rgb1[1] = 0, rgb1[2] = 50;
  current = millis();
  while (millis() - current < 2400)
  {
    lcd.setCursor(5, 2);
    lcd.print("R     G     B");
    lcd.setCursor(3, 3);
    lcd.print(rgb1[0]);
    lcd.print("%  ");
    lcd.print(rgb1[1]);
    lcd.print("%  ");
    lcd.print(rgb1[2]);
    lcd.print("%");
  }
  lcd.setCursor(0,3); //Eraser
  for(j=0;j<4;j++)
  {
    lcd.print(" ");
  }
  rgb1[0] = 20, rgb1[1] = 0, rgb1[2] = 100;
  current = millis();
  while (millis() - current < 2500)
  {
    lcd.setCursor(5, 2);
    lcd.print("R     G     B");
    lcd.setCursor(3, 3);
    lcd.print(rgb1[0]);
    lcd.print("%  ");
    lcd.print(rgb1[1]);
    lcd.print("%  ");
    lcd.print(rgb1[2]);
    lcd.print("%");
  }
}

//void spinach()
//{
//  current = millis();
//  /*
//    targt temp|curr temp
//    ---@@*C---|--@@*C---
//    ----R-----G-----B---
//    --100%--100%--100%--
//  */
//
//  lcd.setCursor(0, 0);
//  lcd.print("Targt Temp|Curr Temp");
//  lcd.setCursor(4, 1);
//  lcd.print(21);
//  lcd.printByte(1);
//  lcd.print("C   |  ");
//  lcd.print(w_temp);
//  lcd.printByte(1);
//  lcd.print("C");
//
//  while (millis() - current < 11000)
//  {
//    lcd.setCursor(5, 2);
//    lcd.print("R     G     B");
//    lcd.setCursor(3, 3);
//    lcd.print(rgb1[0]);
//    lcd.print("%  ");
//    lcd.print(rgb1[1]);
//    lcd.print("%  ");
//    lcd.print(rgb1[2]);
//    lcd.print("%");
//  }
//  rgb1[0] = 100, rgb1[1] = 10, rgb1[2] = 10;
//  current = millis();
//  while (millis() - current < 12000)
//  {
//    lcd.setCursor(5, 2);
//    lcd.print("R     G     B");
//    lcd.setCursor(3, 3);
//    lcd.print(rgb1[0]);
//    lcd.print("%  ");
//    lcd.print(rgb1[1]);
//    lcd.print("%  ");
//    lcd.print(rgb1[2]);
//    lcd.print("%");
//  }
//  rgb1[0] = 100, rgb1[1] = 25, rgb1[2] = 26;
//  current = millis();
//  while (millis() - current < 24000)
//  {
//    lcd.setCursor(5, 2);
//    lcd.print("R     G     B");
//    lcd.setCursor(3, 3);
//    lcd.print(rgb1[0]);
//    lcd.print("%  ");
//    lcd.print(rgb1[1]);
//    lcd.print("%  ");
//    lcd.print(rgb1[2]);
//    lcd.print("%");
//  }
//}

void comm()
{
  
}
