#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

#define Vrx A0
#define Vry A1
#define Sw 9

int sw, vx,vy;

uint8_t bell[8]  = {0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4};
uint8_t note[8]  = {0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0};
uint8_t clock[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
uint8_t duck[8]  = {0x0, 0xc, 0x1d, 0xf, 0xf, 0x6, 0x0};
uint8_t check[8] = {0x0, 0x1, 0x3, 0x16, 0x1c, 0x8, 0x0};
uint8_t cross[8] = {0x0, 0x1b, 0xe, 0x4, 0xe, 0x1b, 0x0};
uint8_t retarrow[8] = {  0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4};
uint8_t arrow[8] = {  0x8, 0x4, 0x2, 0xff, 0x2, 0x4, 0x8};


LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Serial.begin(9600);
  
  pinMode(Vrx, INPUT);
  pinMode(Vry, INPUT);
  pinMode(Sw, INPUT);
  
  lcd.init();                      
  lcd.backlight();

  lcd.createChar(0, arrow);
  lcd.createChar(1, note);
  lcd.createChar(2, clock);
  lcd.createChar(3, heart);
  lcd.createChar(4, duck);
  lcd.createChar(5, check);
  lcd.createChar(6, cross);
  lcd.createChar(7, arrow);
  
  //homeScr();
  //infoScr();
  
}


void loop()
{
  vx = analogRead(Vrx);
  vy = analogRead(Vry);
  sw = digitalRead(Sw);
  map(vx,0,1023,-50,50);
  if((vx>=300)&&(vx<=600))
  {
    vx = 0;
  }
  else if(vx>=650)
  {
    vx=1;
  }
  else if(vx<=250)
  {
    vx = -1;
  }
  Serial.println(vx);
  //Serial.println(analogRead(Vry));
  //Serial.println(digitalRead(Sw));
}
