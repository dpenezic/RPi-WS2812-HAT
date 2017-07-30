/*
  RPi-WS2812-HAT Text Example
 */

#include <WS2812.h>
//#include <avr/pgmspace.h>

#define DATAPIN     1 //digital output pin (data input of LEDs)
#define LEDCOUNT   64 //number of LEDs to drive
#define INTENSITY 100 //light intensity

WS2812 LED(LEDCOUNT);

byte intensity=0;
byte sign=1;

const byte font_data[] PROGMEM =
{
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 0x20
  0x30,0x78,0x78,0x30,0x30,0x00,0x30,0x00, // 0x21
  0x6C,0x6C,0x6C,0x00,0x00,0x00,0x00,0x00, // 0x22
  0x6C,0x6C,0xFE,0x6C,0xFE,0x6C,0x6C,0x00, // 0x23
  0x30,0x7C,0xC0,0x78,0x0C,0xF8,0x30,0x00, // 0x24
  0x00,0xC6,0xCC,0x18,0x30,0x66,0xC6,0x00, // 0x25
  0x38,0x6C,0x38,0x76,0xDC,0xCC,0x76,0x00, // 0x26
  0x60,0x60,0xC0,0x00,0x00,0x00,0x00,0x00, // 0x27
  0x18,0x30,0x60,0x60,0x60,0x30,0x18,0x00, // 0x28
  0x60,0x30,0x18,0x18,0x18,0x30,0x60,0x00, // 0x29
  0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00, // 0x2A
  0x00,0x30,0x30,0xFC,0x30,0x30,0x00,0x00, // 0x2B
  0x00,0x00,0x00,0x00,0x00,0x70,0x30,0x60, // 0x2C
  0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x00, // 0x2D
  0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00, // 0x2E
  0x06,0x0C,0x18,0x30,0x60,0xC0,0x80,0x00, // 0x2F
  0x78,0xCC,0xDC,0xFC,0xEC,0xCC,0x78,0x00, // 0x30
  0x30,0xF0,0x30,0x30,0x30,0x30,0xFC,0x00, // 0x31
  0x78,0xCC,0x0C,0x38,0x60,0xCC,0xFC,0x00, // 0x32
  0x78,0xCC,0x0C,0x38,0x0C,0xCC,0x78,0x00, // 0x33
  0x1C,0x3C,0x6C,0xCC,0xFE,0x0C,0x0C,0x00, // 0x34
  0xFC,0xC0,0xF8,0x0C,0x0C,0xCC,0x78,0x00, // 0x35
  0x38,0x60,0xC0,0xF8,0xCC,0xCC,0x78,0x00, // 0x36
  0xFC,0xCC,0x0C,0x18,0x30,0x60,0x60,0x00, // 0x37
  0x78,0xCC,0xCC,0x78,0xCC,0xCC,0x78,0x00, // 0x38
  0x78,0xCC,0xCC,0x7C,0x0C,0x18,0x70,0x00, // 0x39
  0x00,0x00,0x30,0x30,0x00,0x30,0x30,0x00, // 0x3A
  0x00,0x00,0x30,0x30,0x00,0x70,0x30,0x60, // 0x3B
  0x18,0x30,0x60,0xC0,0x60,0x30,0x18,0x00, // 0x3C
  0x00,0x00,0xFC,0x00,0xFC,0x00,0x00,0x00, // 0x3D
  0x60,0x30,0x18,0x0C,0x18,0x30,0x60,0x00, // 0x3E
  0x78,0xCC,0x0C,0x18,0x30,0x00,0x30,0x00, // 0x3F
  0x7C,0xC6,0xDE,0xDE,0xDE,0xC0,0x78,0x00, // 0x40
  0x30,0x78,0xCC,0xCC,0xFC,0xCC,0xCC,0x00, // 0x41
  0xFC,0x66,0x66,0x7C,0x66,0x66,0xFC,0x00, // 0x42
  0x3C,0x66,0xC0,0xC0,0xC0,0x66,0x3C,0x00, // 0x43
  0xFC,0x6C,0x66,0x66,0x66,0x6C,0xFC,0x00, // 0x44
  0xFE,0x62,0x68,0x78,0x68,0x62,0xFE,0x00, // 0x45
  0xFE,0x62,0x68,0x78,0x68,0x60,0xF0,0x00, // 0x46
  0x3C,0x66,0xC0,0xC0,0xCE,0x66,0x3E,0x00, // 0x47
  0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0x00, // 0x48
  0x78,0x30,0x30,0x30,0x30,0x30,0x78,0x00, // 0x49
  0x1E,0x0C,0x0C,0x0C,0xCC,0xCC,0x78,0x00, // 0x4A
  0xE6,0x66,0x6C,0x78,0x6C,0x66,0xE6,0x00, // 0x4B
  0xF0,0x60,0x60,0x60,0x62,0x66,0xFE,0x00, // 0x4C
  0xC6,0xEE,0xFE,0xD6,0xC6,0xC6,0xC6,0x00, // 0x4D
  0xC6,0xE6,0xF6,0xDE,0xCE,0xC6,0xC6,0x00, // 0x4E
  0x38,0x6C,0xC6,0xC6,0xC6,0x6C,0x38,0x00, // 0x4F
  0xFC,0x66,0x66,0x7C,0x60,0x60,0xF0,0x00, // 0x50
  0x78,0xCC,0xCC,0xCC,0xDC,0x78,0x1C,0x00, // 0x51
  0xFC,0x66,0x66,0x7C,0x78,0x6C,0xE6,0x00, // 0x52
  0x78,0xCC,0xE0,0x38,0x1C,0xCC,0x78,0x00, // 0x53
  0xFC,0xB4,0x30,0x30,0x30,0x30,0x78,0x00, // 0x54
  0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xFC,0x00, // 0x55
  0xCC,0xCC,0xCC,0xCC,0xCC,0x78,0x30,0x00, // 0x56
  0xC6,0xC6,0xC6,0xD6,0xFE,0xEE,0xC6,0x00, // 0x57
  0xC6,0xC6,0x6C,0x38,0x6C,0xC6,0xC6,0x00, // 0x58
  0xCC,0xCC,0xCC,0x78,0x30,0x30,0x78,0x00, // 0x59
  0xFE,0xCC,0x98,0x30,0x62,0xC6,0xFE,0x00, // 0x5A
  0x78,0x60,0x60,0x60,0x60,0x60,0x78,0x00, // 0x5B
  0xC0,0x60,0x30,0x18,0x0C,0x06,0x02,0x00, // 0x5C
  0x78,0x18,0x18,0x18,0x18,0x18,0x78,0x00, // 0x5D
  0x10,0x38,0x6C,0xC6,0x00,0x00,0x00,0x00, // 0x5E
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF, // 0x5F
  0x30,0x30,0x18,0x00,0x00,0x00,0x00,0x00, // 0x60
  0x00,0x00,0x78,0x0C,0x7C,0xCC,0x76,0x00, // 0x61
  0xE0,0x60,0x7C,0x66,0x66,0x66,0xBC,0x00, // 0x62
  0x00,0x00,0x78,0xCC,0xC0,0xCC,0x78,0x00, // 0x63
  0x1C,0x0C,0x0C,0x7C,0xCC,0xCC,0x76,0x00, // 0x64
  0x00,0x00,0x78,0xCC,0xFC,0xC0,0x78,0x00, // 0x65
  0x38,0x6C,0x60,0xF0,0x60,0x60,0xF0,0x00, // 0x66
  0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0xF8, // 0x67
  0xE0,0x60,0x6C,0x76,0x66,0x66,0xE6,0x00, // 0x68
  0x30,0x00,0x70,0x30,0x30,0x30,0x78,0x00, // 0x69
  0x18,0x00,0x78,0x18,0x18,0x18,0xD8,0x70, // 0x6A
  0xE0,0x60,0x66,0x6C,0x78,0x6C,0xE6,0x00, // 0x6B
  0x70,0x30,0x30,0x30,0x30,0x30,0x78,0x00, // 0x6C
  0x00,0x00,0xEC,0xFE,0xD6,0xC6,0xC6,0x00, // 0x6D
  0x00,0x00,0xF8,0xCC,0xCC,0xCC,0xCC,0x00, // 0x6E
  0x00,0x00,0x78,0xCC,0xCC,0xCC,0x78,0x00, // 0x6F
  0x00,0x00,0xDC,0x66,0x66,0x7C,0x60,0xF0, // 0x70
  0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0x1E, // 0x71
  0x00,0x00,0xD8,0x6C,0x6C,0x60,0xF0,0x00, // 0x72
  0x00,0x00,0x7C,0xC0,0x78,0x0C,0xF8,0x00, // 0x73
  0x10,0x30,0x7C,0x30,0x30,0x34,0x18,0x00, // 0x74
  0x00,0x00,0xCC,0xCC,0xCC,0xCC,0x76,0x00, // 0x75
  0x00,0x00,0xCC,0xCC,0xCC,0x78,0x30,0x00, // 0x76
  0x00,0x00,0xC6,0xC6,0xD6,0xFE,0x6C,0x00, // 0x77
  0x00,0x00,0xC6,0x6C,0x38,0x6C,0xC6,0x00, // 0x78
  0x00,0x00,0xCC,0xCC,0xCC,0x7C,0x0C,0xF8, // 0x79
  0x00,0x00,0xFC,0x98,0x30,0x64,0xFC,0x00, // 0x7A
  0x1C,0x30,0x30,0xE0,0x30,0x30,0x1C,0x00, // 0x7B
  0x18,0x18,0x18,0x00,0x18,0x18,0x18,0x00, // 0x7C
  0xE0,0x30,0x30,0x1C,0x30,0x30,0xE0,0x00, // 0x7D
  0x76,0xDC,0x00,0x00,0x00,0x00,0x00,0x00, // 0x7E
  0x10,0x38,0x6C,0xC6,0xC6,0xC6,0xFE,0x00  // 0x7F
};

void setup()
{
  //init LEDs
  LED.setOutput(DATAPIN);
  //LED.setColorOrderRGB(); //uncomment for RGB color order
  //LED.setColorOrderBRG(); //uncomment for BRG color order
  LED.setColorOrderGRB(); //ucomment for GRB color order (default)
}

void write_ch(char c, cRGB fg, cRGB bg)
{
  uint_least16_t pos;
  uint_least8_t data, mask;
  uint_least8_t i, j, width, height;
  const uint_least8_t *ptr PROGMEM;

  if((c < 0x20) || (c > 0x7F))
  {
    return;
  }

  pos = (c-0x20)*(8*8/8); //8x8 font
  ptr = &font_data[pos];

  for(byte y=0; y < 8; y++)
  {
    data = pgm_read_byte(ptr++);
    data >>=1; //offset 1 pixel to left
    for(byte x=0, mask=(1<<(8-1)); mask!=0; mask>>=1, x++)
    {
      if(data & mask)
      {
        LED.set_crgb_at((x*8)+y, fg); //set character on pixel
      }
      else
      {
        LED.set_crgb_at((x*8)+y, bg); //set character off pixel
      }
    }
  }
  LED.sync(); //send the values to the LEDs
}

void write_s(char *s, cRGB fg, cRGB bg, int ms)
{
  while(*s)
  {
    write_ch(' ', fg, bg); //clear before letter
    delay(50);
    write_ch(*s++, fg, bg);
    delay(ms); //wait
  }
  write_ch(' ', fg, bg); //clear after last letter
}

void loop()
{
  cRGB fg, bg;

  if(sign)
  {
    intensity+=5;
    if(intensity >= INTENSITY)
    {
      sign = 0;
    }
  }
  else
  {
    intensity-=5;
    if(intensity <= 10)
    {
      sign = 1;
    }
  }

  fg.r = intensity;
  fg.g = 0;
  fg.b = 0;

  bg.r = 0;
  bg.g = 0;
  bg.b = 0;

  write_s("Hello World!", fg, bg, 500);
  delay(1000);
}
