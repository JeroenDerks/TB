#include <Adafruit_NeoPixel.h>
#include <math.h>

const byte dim_curve[] = {
  0,   1,   1,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,   3,   3,
  3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   4,   4,   4,   4,
  4,   4,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   6,   6,
  6,   6,   6,   6,   6,   7,   7,   7,   7,   7,   7,   7,   8,   8,   8,   8,
  8,   8,   9,   9,   9,   9,   9,   9,   10,  10,  10,  10,  10,  11,  11,  11,
  11,  11,  12,  12,  12,  12,  12,  13,  13,  13,  13,  14,  14,  14,  14,  15,
  15,  15,  16,  16,  16,  16,  17,  17,  17,  18,  18,  18,  19,  19,  19,  20,
  20,  20,  21,  21,  22,  22,  22,  23,  23,  24,  24,  25,  25,  25,  26,  26,
  27,  27,  28,  28,  29,  29,  30,  30,  31,  32,  32,  33,  33,  34,  35,  35,
  36,  36,  37,  38,  38,  39,  40,  40,  41,  42,  43,  43,  44,  45,  46,  47,
  48,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,
  63,  64,  65,  66,  68,  69,  70,  71,  73,  74,  75,  76,  78,  79,  81,  82,
  83,  85,  86,  88,  90,  91,  93,  94,  96,  98,  99,  101, 103, 105, 107, 109,
  110, 112, 114, 116, 118, 121, 123, 125, 127, 129, 132, 134, 136, 139, 141, 144,
  146, 149, 151, 154, 157, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 190,
  193, 196, 200, 203, 207, 211, 214, 218, 222, 226, 230, 234, 238, 242, 248, 255,
};

int rgb_colors1[3];
int rgb_colors2[3];

#define NUMPIX_1 90
#define PIN_1 2
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIX_1, PIN_1, NEO_GRB + NEO_KHZ800);
#define NUMPIX_2 120
#define PIN_2 4
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUMPIX_2, PIN_2, NEO_GRB + NEO_KHZ800);
#define NUMPIX_3 150
#define PIN_3 6
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUMPIX_3, PIN_3, NEO_GRB + NEO_KHZ800);
#define NUMPIX_4 90
#define PIN_4 8
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(NUMPIX_4, PIN_4, NEO_GRB + NEO_KHZ800);

int inputPin1 = 12;              
int pirState1 = LOW;            
int val1 = 0;         

int inputPin2 = 11;
int pirState2 = LOW;
int val2 = 0;

void setup() {
  Serial.begin(9600);
  strip1.begin();
  strip1.show();
  strip2.begin();
  strip2.show();
  strip3.begin();
  strip3.show();
  strip4.begin();
  strip4.show();

}

void loop() {

  ///////////////// SENSOR 1 /////////////////

  val1 = digitalRead(inputPin1);
  if (val1 != pirState1) {
    if (val1 == HIGH) {
      int h =  (int)(millis() / 500.0) % 360;
      if (h > 180) h = 360 - h;
      int hue = (240 + h) % 360;
      getRGB(hue, 255, 255, rgb_colors1);
      // LEDstrip 4.1
      for (int i = 0; i <= NUMPIX_2; i++) {
        strip1.setPixelColor(24 + i, strip1.Color(rgb_colors1[0], rgb_colors1[1], rgb_colors1[2]));
        strip1.setPixelColor(24 - i, strip1.Color(rgb_colors1[0], rgb_colors1[1], rgb_colors1[2]));
        strip1.show();
        // LEDstrip 4.2
        strip2.setPixelColor(i, strip2.Color(rgb_colors1[0], rgb_colors1[1], rgb_colors1[2]));
        strip2.show();
        delay(4);
      }
    }
    pirState1 = val1;
  }

  ///////////////// LEDstrip 3.1 = NUMPIX_1 /////////////////

  float sin1 = sin(millis() / 2350.0);
  float absSin1 = 1.0 + sin1;
  float sinToLed1 = - (NUMPIX_1 * 0.5) + (absSin1 * NUMPIX_1);
  int pix1 = (int)sinToLed1;

  for (int i = 0; i < 11; i++) {
    float cMinus = sinToLed1 - pix1 + i;
    cMinus *= cMinus * 0.01;
    if (cMinus > 1.0) cMinus = 1.0;
    float cPlus = sinToLed1 - pix1 - i;
    cPlus *= cPlus * 0.01;
    if (cPlus > 1.0) cPlus = 1.0;
    strip1.setPixelColor(pix1 - 1  - i, strip1.Color (rgb_colors1[0] * cMinus, rgb_colors1[1] * cMinus, rgb_colors1[2] * cMinus));
    strip1.setPixelColor(pix1, strip1.Color (0, 0, 0));
    strip1.setPixelColor(pix1 + 1 + i, strip1.Color(rgb_colors1[0] * cPlus, rgb_colors1[1] * cPlus, rgb_colors1[2] * cPlus));
  }
  strip1.show();

  ///////////////// LEDstrip 3.2 = NUMPIX_2 /////////////////

  sin1 = sin(millis() / 2890.0);
  absSin1 = 1.0 + sin1;
  sinToLed1 = - (NUMPIX_2 * 0.5) + (absSin1 * NUMPIX_2);
  pix1 = (int)sinToLed1;

  for (int i = 0; i < 11; i++) {
    float cMinus = sinToLed1 - pix1 + i;
    cMinus *= cMinus * 0.01;
    if (cMinus > 1.0) cMinus = 1.0;
    float cPlus = sinToLed1 - pix1 - i;
    cPlus *= cPlus * 0.01;
    if (cPlus > 1.0) cPlus = 1.0;
    strip2.setPixelColor(pix1 - 1  - i, strip2.Color (rgb_colors1[0] * cMinus, rgb_colors1[1] * cMinus, rgb_colors1[2] * cMinus));
    strip2.setPixelColor(pix1, strip2.Color (0, 0, 0));
    strip2.setPixelColor(pix1 + 1 + i, strip2.Color(rgb_colors1[0] * cPlus, rgb_colors1[1] * cPlus, rgb_colors1[2] * cPlus));
  }
  strip2.show();


  ///////////////// SENSOR 2 /////////////////

  val2 = digitalRead(inputPin2);
  if (val2 != pirState2) {
    if (val2 == HIGH) {
      int h = (int)(millis() / 500.0) % 360;
      if (h > 180) h = 360 - h;
      int hue = (240 + h) % 360;
      getRGB(hue, 255, 255, rgb_colors2);
      for (int i = 0; i <= NUMPIX_3; i++) {
        // LEDstrip 3.3
        strip3.setPixelColor(i, strip3.Color(rgb_colors2[0], rgb_colors2[1], rgb_colors2[2]));
        strip3.show();
        // LEDstrip 3.4
        strip4.setPixelColor(60 - i, strip4.Color(rgb_colors2[0], rgb_colors2[1], rgb_colors2[2]));
        strip4.setPixelColor(60 + i, strip4.Color(rgb_colors2[0], rgb_colors2[1], rgb_colors2[2]));
        strip4.show();
        delay(4);
      }
    }
    pirState1 = val1;
  }

  ///////////////// LEDstrip 3.3 = NUMPIX_3 /////////////////

  sin1 = sin(millis() / 4290.0);
  absSin1 = 1.0 + sin1;
  sinToLed1 = - (NUMPIX_3 * 0.5) + (absSin1 * NUMPIX_3);
  pix1 = (int)sinToLed1;

  for (int i = 0; i < 11; i++) {
    float cMinus = sinToLed1 - pix1 + i;
    cMinus *= cMinus * 0.01;
    if (cMinus > 1.0) cMinus = 1.0;
    float cPlus = sinToLed1 - pix1 - i;
    cPlus *= cPlus * 0.01;
    if (cPlus > 1.0) cPlus = 1.0;
    strip3.setPixelColor(pix1 - 1  - i, strip3.Color (rgb_colors2[0] * cMinus, rgb_colors2[1] * cMinus, rgb_colors2[2] * cMinus));
    strip3.setPixelColor(pix1, strip3.Color (0, 0, 0));
    strip3.setPixelColor(pix1 + 1 + i, strip3.Color(rgb_colors2[0] * cPlus, rgb_colors2[1] * cPlus, rgb_colors2[2] * cPlus));
  }
  strip3.show();


  ///////////////// LEDstrip 3.4 = NUMPIX_4 /////////////////

  sin1 = sin(millis() / 2610.0);
  absSin1 = 1.0 + sin1;
  sinToLed1 = - (NUMPIX_4 * 0.5) + (absSin1 * NUMPIX_4);
  pix1 = (int)sinToLed1;

  for (int i = 0; i < 11; i++) {
    float cMinus = sinToLed1 - pix1 + i;
    cMinus *= cMinus * 0.01;
    if (cMinus > 1.0) cMinus = 1.0;
    float cPlus = sinToLed1 - pix1 - i;
    cPlus *= cPlus * 0.01;
    if (cPlus > 1.0) cPlus = 1.0;
    strip4.setPixelColor(pix1 - 1  - i, strip4.Color (rgb_colors2[0] * cMinus, rgb_colors2[1] * cMinus, rgb_colors2[2] * cMinus));
    strip4.setPixelColor(pix1, strip4.Color (0, 0, 0));
    strip4.setPixelColor(pix1 + 1 + i, strip4.Color(rgb_colors2[0] * cPlus, rgb_colors2[1] * cPlus, rgb_colors2[2] * cPlus));
  }
  strip4.show();
}

void getRGB(int hue, int sat, int val, int colors[3]) {
  val = dim_curve[val];
  sat = 255 - dim_curve[255 - sat];

  int r;
  int g;
  int b;
  int base;

  base = ((255 - sat) * val) >> 8;

  switch (hue / 60) {
    case 0:
      r = val;
      g = (((val - base) * hue) / 60) + base;
      b = base;
      break;

    case 1:
      r = (((val - base) * (60 - (hue % 60))) / 60) + base;
      g = val;
      b = base;
      break;

    case 2:
      r = base;
      g = val;
      b = (((val - base) * (hue % 60)) / 60) + base;
      break;

    case 3:
      r = base;
      g = (((val - base) * (60 - (hue % 60))) / 60) + base;
      b = val;
      break;

    case 4:
      r = (((val - base) * (hue % 60)) / 60) + base;
      g = base;
      b = val;
      break;

    case 5:
      r = val;
      g = base;
      b = (((val - base) * (60 - (hue % 60))) / 60) + base;
      break;
  }

  colors[0] = r;
  colors[1] = g;
  colors[2] = b;
}
