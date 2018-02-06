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


#define NUMPIX_1 180
#define PIN_1 6
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIX_1, PIN_1, NEO_GRB + NEO_KHZ800);
#define NUMPIX_2 110
#define PIN_2 11
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUMPIX_2, PIN_2, NEO_GRB + NEO_KHZ800);
#define NUMPIX_3 90
#define PIN_3 9
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUMPIX_3, PIN_3, NEO_GRB + NEO_KHZ800);
#define NUMPIX_4 90
#define PIN_4 3
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(NUMPIX_4, PIN_4, NEO_GRB + NEO_KHZ800);

int r1, r2, r3, r4;
float c1, c2, c3, c4;

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
  r1  = random(4852);
  r2 = random(5832);
  r3 = random(8019);
  r4 = random(7000);
  c1 = 1;
  c2 = 1;
  c3 = 1;
  c4 = 1;

}

void loop() {
  // Color oscialtion
  // YELLOW TO BLUE
  float c1 = sin(millis() / 18000.0);
  // Position oscilation
  float sin1 = sin((millis() + r1) / 2700.0);
  float absSin1 = 1.0 + sin1;
  float sinToLed1 = - (NUMPIX_1 / 2) + (absSin1 * NUMPIX_1);
  int pix1 = (int)sinToLed1;

  for (int i = 1; i < 10; i++) {
    float cMinus = sinToLed1 - pix1 + i;
    cMinus *= cMinus;
    float cPlus = sinToLed1 - pix1 - i;
    cPlus *= cPlus;
    strip1.setPixelColor(pix1 - 1  - i, strip1.Color ((1.5 + c1) * cMinus, (1.0 + c1) * cMinus, (1.0 - c1) * cMinus));
    strip1.setPixelColor(pix1 + 1 + i, strip1.Color((1.5 + c1) * cPlus, (1.25 + c1) * cPlus, (1.0 - c1) * cPlus));
  }
  strip1.show();

  // Color oscialtion
  // YELLOW TO ORANGE
  float c2 = sin(millis() / 17000.0);
  c2 = (1.0 + c2) / 2.0;

  // Position oscilation
  float sin2 = sin((millis() + r2) / 2580.0);
  float absSin2 = 1.0 + sin2;
  float sinToLed2 = - (NUMPIX_2 / 2) + (absSin2 * NUMPIX_2);
  int pix2 = (int)sinToLed2;
  Serial.println(pix2);
  for (int i = 1; i < 10; i++) {
    float cMinus = sinToLed2 - pix2 + i;
    cMinus *= cMinus;
    float cPlus = sinToLed2 - pix2 - i;
    cPlus *= cPlus;
    strip2.setPixelColor(pix2 - 1  - i, strip2.Color (1.25 * cMinus, (0.25 + c2) * cMinus, 0));
    strip2.setPixelColor(pix2 + 1 + i, strip2.Color(1.25 * cPlus, (0.25 + c2) * cPlus, 0));
  }
  strip2.show();
  // Color oscialtion
  // PURPLE TO ORANGE
  float c3 = sin(millis() / 17000.0);
  c3 = (1.0 + c3) / 2.0;
  // Position oscialition
  float sin3 = sin((millis() + r3) / 4320.0);
  float absSin3 = 1.0 + sin3;
  float sinToLed3 = -(NUMPIX_3 / 3) + (absSin3 * NUMPIX_3);
  int pix3 = (int)sinToLed3;
  for (int i = 1; i < 10; i++) {
    float cMinus = sinToLed3 - pix3 + i;
    cMinus *= cMinus;
    float cPlus = sinToLed3 - pix3 - i;
    cPlus *= cPlus;
    strip3.setPixelColor(pix3 - 1 - i, strip3.Color(0.75 * cMinus, (c3 * 0.5) * cMinus, (1.01 - c3) * cMinus));
    strip3.setPixelColor(pix3 + 1 + i, strip3.Color(0.75 * cPlus, (c3 * 0.5) * cPlus, (1.01 - c3) * cPlus));
  }
  strip3.show();

  // Color oscialtion
  // BLUE TO PURPLE
  float c4 = sin(millis() / 21300.0);
  c4 = (1.0 + c4) / 2.0;
  // Position oscilation
  float sin4 = sin((millis() + r4) / 3800.0);
  float absSin4 = 1.0 + sin4;
  float sinToLed4 = -(NUMPIX_4 / 2) + (absSin4 * NUMPIX_1);
  int pix4 = (int)sinToLed4;
  for (int i = 1; i < 10; i++) {
    float cMinus = sinToLed4 - pix4 + i;
    cMinus *= cMinus;
    float cPlus = sinToLed4 - pix4 - i;
    cPlus *= cPlus;
    strip4.setPixelColor(pix4 - 3  - i, strip4.Color (c4 * cMinus, 0, 1.25 * cMinus));
    strip4.setPixelColor(pix4 + 3 + i, strip4.Color(c4 * cPlus, 0, 1.25 * cPlus));
  }
  strip4.show();
}
