#include <Adafruit_NeoPixel.h>
#define NUMPIX 54
#define PIN_1 8 
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIX, PIN_1, NEO_RGBW + NEO_KHZ800);

int inputPin = 11;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

void setup() {
  pinMode(inputPin, INPUT);     // declare sensor as input
  Serial.begin(9600);
  strip1.begin();
  strip1.show(); // Initialize all pixels to 'off'

}

void loop() {
  val = digitalRead(inputPin);  // read input value
  Serial.println(val);
  if (val != pirState) {
    if (val == HIGH) {
      Serial.println("Motion detected!");
      for (int i = 0; i < NUMPIX; i++) {
        strip1.setPixelColor(i, strip1.Color(255, 0, 0)); // bright green color.
        strip1.show(); // This sends the updated pixel color to the hardware.
      }
    } else {
      Serial.println("Motion ended!");
      for (int i = 0; i < NUMPIX; i++) {
        strip1.setPixelColor(i, strip1.Color(0, 255, 0)); // bright green color.
        strip1.show(); // This sends the updated pixel color to the hardware.
      }
    }
    pirState = val;
  }
}
