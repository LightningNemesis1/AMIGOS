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
   * Temp:@@  Water:@@%.
   * Lock Stat:@@@......
   * Elapsed Time: hh:mm
   * Press to go back...
   * 
   * 
   */
  lcd.setCursor(0, 0);
  lcd.print("Temp:@@  Water:@@%.");
  lcd.setCursor(0, 1);
  lcd.print("Valve Status:@@@..");
  lcd.setCursor(0, 2);
  lcd.print("Elapsed Time: hh:mm");
  lcd.setCursor(0, 3);
  lcd.print("Press to go back...");
}

void navScr()
{
  /*
   *  .
   * Lock Stat:@@@......
   * Elapsed Time: hh:mm
   * Press to go back...
   * 
   * 
   */
  lcd.setCursor(0, 0);
  lcd.print("Temp:@@  Water:@@%.");
  lcd.setCursor(0, 1);
  lcd.print("Valve Status:@@@..");
  lcd.setCursor(0, 2);
  lcd.print("Elapsed Time: hh:mm");
  lcd.setCursor(0, 3);
  lcd.print("Press to go back...");
}
