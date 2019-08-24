#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

#include <ArduinoJson.h>
StaticJsonDocument<100> doc;

#define Vrx A0
#define Vry A1
#define Sw 9
#define wls A15
#define wts A13
#define amb A14
#define pump 7
#define led 8
#define digPin1 10
#define digPin2 11

void map_x();
void map_y();
void homeScr();
void navScr();
void infoScr();
void preScr();
void conn();



int counter = 0;
int scr_count = 0;
int current = 0;

int cur = 0;
int i, flag = 0,j;

int sw, vx, vy;

int w_level = 0;
double amb_temp = 0.0, amb_humid = 0.0;
long rgb = 0;
char r, g, b;

String json;

char rgb1[3];

uint8_t deg_hole[8]  = {0x4, 0xa, 0xa, 0x4, 0x0, 0x0, 0x0};
uint8_t deg[8]  = {0x4, 0xe, 0xe, 0x4, 0x0, 0x0, 0x0};
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
  Serial3.begin(9600);

  pinMode(digPin1, INPUT);
  pinMode(digPin2, INPUT);

  lcd.init();
  lcd.backlight();

  lcd.createChar(0, arrow);
  lcd.createChar(1, deg_hole);
  lcd.createChar(2, clock);
  lcd.createChar(3, deg);
  lcd.createChar(4, duck);
  lcd.createChar(5, check);
  lcd.createChar(6, cross);
  lcd.createChar(7, retarrow);


}

String str = "";
bool newString = false;
bool newStringAvailable = false;
void loop()
{

  if (Serial3.available())
  {
    while (!newString && Serial3.available()) {
      char ch = Serial3.read();

      if (ch == '{') {
        newStringAvailable = true;
        str = "{";
      }
      else if (ch == '}' && newStringAvailable)
      {
        str += "}\n";
        newStringAvailable = false;
        newString = true;
      }
      else if (newStringAvailable)
        str += ch;

    }
    if (newString) {
      newString = false;
      //Serial.print(str);

      DeserializationError error = deserializeJson(doc, str);

      // Test if parsing succeeds.
      if (error)
      {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return;
      }
      else
      {
        amb_humid = doc["humidity"];
        w_level = doc["w_level"];
        rgb = doc["RGB"];
        amb_temp = doc["temperature"];
        rgb1[0] = rgb >> 16;
        rgb1[1] = rgb >> 8;
        rgb1[2] = rgb ;
        
        //        Serial.print("Humid");
        //        Serial.println(amb_humid);
        //        Serial.print("\nTemp");
        //        Serial.println(amb_temp);
        //        Serial.print("water level");
        //        Serial.println(w_level);
        //        Serial.print("rgb");
        //        Serial.println(rgb);

      }
    }
  }


  map_x();
  //  map_y();
  //Serial.println(scr_count);
  if (scr_count < 0)
  {
    scr_count = 0;
  }
  while (scr_count == 0)
  {
    counter = 0;
    map_x();
    map_y();
    if (vx == 1)
    {
      scr_count++;
      lcd.clear();
      delay(500);
      break;
    }
    else if (vx == -1)
    {
      scr_count--;
      lcd.clear();
      delay(500);
      break;
    }
    homeScr();
  }

  while (scr_count == 1)
  {
    //Serial.println(scr_count);
    if (vx == -1)
    {
      scr_count--;
      lcd.clear();
      delay(400);
      break;
    }
    map_x();
    map_y();
    navScr();
    if (cur > 1)
    {
      cur = 0;
    }
    if (vy == -1)
    {
      cur++;
      delay(150);
    }

    switch (cur)
    {
      case 0:
        lcd.setCursor(0, 1);
        lcd.print(" ");
        lcd.setCursor(0, 2);
        lcd.print(" ");
        lcd.setCursor(0, cur);
        lcd.printByte(0);
        if (vx == 1)
        {
          scr_count = 2;
          lcd.clear();
          delay(500);
        }
        break;

      case 1:
        lcd.setCursor(0, 0);
        lcd.print(" ");
        lcd.setCursor(0, 2);
        lcd.print(" ");
        lcd.setCursor(0, cur);
        lcd.printByte(0);
        if (vx == 1)
        {
          scr_count = 3;
          lcd.clear();
          delay(500);
        }
        break;
    }
  }

  switch (scr_count)
  {
    case 2:
      while (counter != 1)
      {
        map_x();
        if (vx == -1)
        {
          counter++;
          scr_count = 0;
        }
        infoScr();
        Serial.println(vx);
      }
      break;

    case 3:
      while (counter != 1)
      {
        map_x();
        if (vx == -1)
        {
          counter++;
          scr_count = 0;
        }
        preScr();
      }
      break;


  }
}
