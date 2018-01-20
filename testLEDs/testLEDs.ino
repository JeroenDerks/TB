#include <Adafruit_NeoPixel.h>
#include <math.h>
#define NUMPIX_1 60
#define PIN_1 3
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIX_1, PIN_1, NEO_GRB + NEO_KHZ800);
#define NUMPIX_2 60
#define PIN_2 6
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUMPIX_2, PIN_2, NEO_GRB + NEO_KHZ800);
#define NUMPIX_3 120
#define PIN_3 9
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUMPIX_3, PIN_3, NEO_GRB + NEO_KHZ800);

int r1, r2, r3;;

void setup() {
  Serial.begin(9600);
  strip1.begin();
  strip1.show();
  strip2.begin();
  strip2.show();
  strip3.begin();
  strip3.show();
  r1  = random(6000);
  r2 = random(5000);
  r3 = random(7000);
}

void loop() {
  float sin1 = sin((millis() + r1) / 2500.0);
  float absSin1 = 1.0 + sin1;
  float sinToLed1 = absSin1 * (NUMPIX_1 / 2);
  int pix1 = (int)sinToLed1;
  for (int i = 1; i < 10; i++) {
    float cMinus = sinToLed1 - pix1 + i;
    cMinus *= cMinus;
    float cPlus = sinToLed1 - pix1 - i;
    cPlus *= cPlus;
    strip1.setPixelColor(pix1 - i, strip1.Color(0, 0.5 * cMinus, 2.5 * cMinus)); // bright green color.
    strip1.setPixelColor(pix1 + i, strip1.Color(0, 0.5 * cPlus, 2.5 * cPlus)); // bright green color.
  }
  strip1.show(); // This sends the updated pixel color to the hardware.

  float sin2 = sin((millis() + r2) / 2200.0);
  float absSin2 = 1.0 + sin2;
  float sinToLed2 = absSin1 * (NUMPIX_2 / 2);
  int pix2 = (int)sinToLed2;
  for (int i = 1; i < 10; i++) {
    float cMinus = sinToLed2 - pix2 + i;
    cMinus *= cMinus;
    float cPlus = sinToLed2 - pix2 - i;
    cPlus *= cPlus;
    strip2.setPixelColor(pix2 - i, strip1.Color(0, 0.5 * cMinus, 2.5 * cMinus)); // bright green color.
    strip2.setPixelColor(pix2 + i, strip1.Color(0, 0.5 * cPlus, 2.5 * cPlus)); // bright green color.
  }
  strip2.show(); // This sends the updated pixel color to the hardware.

  float sin3 = sin((millis() + r3) / 5500.0);
  float absSin3 = 1.0 + sin3;
  float sinToLed3 = absSin3 * (NUMPIX_3 / 2);
  int pix3 = (int)sinToLed3;
  for (int i = 1; i < 15; i++) {
    float cMinus = sinToLed3 - pix3 + i;
    cMinus *= cMinus;
    float cPlus = sinToLed3 - pix3 - i;
    cPlus *= cPlus;
    strip3.setPixelColor(pix3 - i, strip1.Color(0, 0.25 * cMinus, 1.25 * cMinus)); // bright green color.
    strip3.setPixelColor(pix3 + i, strip1.Color(0, 0.25 * cPlus, 1.25 * cPlus)); // bright green color.
  }
  strip3.show(); // This sends the updated pixel color to the hardware.
}
