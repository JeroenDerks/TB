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

int r1, r2, r3;
int inputPin = 11;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

int c;

void setup() {
  Serial.begin(9600);
  pinMode(inputPin, INPUT);     // declare sensor as input
  strip1.begin();
  strip1.show();
  strip2.begin();
  strip2.show();
  strip3.begin();
  strip3.show();
  r1  = random(6000);
  r2 = random(5000);
  r3 = random(7000);
  c = 1;
}

void loop() {
  val = digitalRead(inputPin);  // read input value
  if (val != pirState) {
    if (val == HIGH) {
      // Serial.println("Motion detected!");
      c *= -1;
      //      for (int i = 0; i < NUMPIX_1; i++) {
      //        strip1.setPixelColor(i, strip1.Color(0, 45, 280)); // bright green color.
      //        strip1.show(); // This sends the updated pixel color to the hardware.
      //        delay(2);
      //      }
      //      for (int i = 0; i < NUMPIX_2; i++) {
      //        strip2.setPixelColor(i, strip2.Color(0, 45, 280)); // bright green color.
      //        strip2.show(); // This sends the updated pixel color to the hardware.
      //        delay(2);
      //      }
      //      for (int i = 0; i < NUMPIX_3; i++) {
      //        strip3.setPixelColor(i, strip3.Color(0, 45, 280)); // bright green color.
      //        strip3.show(); // This sends the updated pixel color to the hardware.
      //        delay(2);
      //      }
    }
    pirState = val;
  }
  float green1 = sin(millis() / 5000.0);
  green1 *= 0.1;

  float sin1 = sin((millis() + r1) / 2500.0);
  float absSin1 = 1.0 + sin1;
  float sinToLed1 = absSin1 * (NUMPIX_1 / 2);
  int pix1 = (int)sinToLed1;
  for (int i = 1; i < 10; i++) {
    float cMinus = sinToLed1 - pix1 + i;
    cMinus *= cMinus;
    float cPlus = sinToLed1 - pix1 - i;
    cPlus *= cPlus;
    strip1.setPixelColor(pix1 - 1 - i, strip1.Color(0, (1.25 + green1 - c) * cMinus, (1.5 + c) * cMinus));
    strip1.setPixelColor(pix1 + 1 + i, strip1.Color(0, (1.25 + green1 - c) * cPlus, (1.5 + c) * cPlus));
  }
  strip1.show();

  float sin2 = sin((millis() + r2) / 2200.0);
  float absSin2 = 1.0 + sin2;
  float sinToLed2 = absSin1 * (NUMPIX_2 / 2);
  int pix2 = (int)sinToLed2;
  for (int i = 1; i < 10; i++) {
    float cMinus = sinToLed2 - pix2 + i;
    cMinus *= cMinus;
    float cPlus = sinToLed2 - pix2 - i;
    cPlus *= cPlus;
    strip2.setPixelColor(pix2 - 1  -i, strip2.Color (0, (1.25 - c) * cMinus, (1.5 + c) * cMinus));
    strip2.setPixelColor(pix2 + 1 + i, strip2.Color(0, (1.25 - c) * cPlus, (1.5 + c) * cPlus));
  }
  strip2.show();

  float sin3 = sin((millis() + r3) / 5500.0);
  float absSin3 = 1.0 + sin3;
  float sinToLed3 = absSin3 * (NUMPIX_3 / 2);
  int pix3 = (int)sinToLed3;
  for (int i = 1; i < 15; i++) {
    float cMinus = sinToLed3 - pix3 + i;
    cMinus *= cMinus;
    float cPlus = sinToLed3 - pix3 - i;
    cPlus *= cPlus;
    if (c > 0) {
      strip3.setPixelColor(pix3 - 2 - i, strip3.Color(0, 0.25 * cMinus, 1.25 * cMinus));
      strip3.setPixelColor(pix3 + 2 + i, strip3.Color(0, 0.25 * cPlus, 1.25 * cPlus));
    }
    else {
      strip3.setPixelColor(pix3 - i, strip3.Color(0, 1.25 * cMinus, 0.25 * cMinus));
      strip3.setPixelColor(pix3 + i, strip3.Color(0, 1.25 * cPlus, 0.25 * cPlus));
    }
  }
  strip3.show();
}
