#include <Adafruit_NeoPixel.h>

#define PIN 8
#define NUMPIXELS 8

typedef unsigned int uint;
const uint MAX_BRIGHTNESS = 30;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
}

void rgb(uint r, uint g, uint b, uint mask) {
  pixels.clear();
  for (uint i = 0; i < NUMPIXELS; i++)
    if (mask & (1 << i))
      pixels.setPixelColor(i, r, g, b);
  pixels.show();
}

void rgb_loop(uint mask) {
  for (uint br = 0; br < MAX_BRIGHTNESS; br++) {
    uint r = (mask & 1) ? br : 0;
    uint g = (mask & 2) ? br : 0;
    uint b = (mask & 4) ? br : 0;
    rgb(r, g, b, 0x7F);
    delay(1500);
  }
}

uint num2dig(uint num) {
  uint digs[10] = { 0x7D, 0x60, 0x3E, 0x7A, 0x63, 0x5B, 0x5F, 0x70, 0x7F, 0x7B };
  if (num > 9)
    return 2;
  return digs[num];
}

void blink_rgb() {
  for (uint i = 0; i < MAX_BRIGHTNESS + 1; i++) {
    rgb(0, i, MAX_BRIGHTNESS - i, 0x7F);
    delay(1500);
  }

  for (uint i = 0; i < MAX_BRIGHTNESS + 1; i++) {
    rgb(i, MAX_BRIGHTNESS - i, 0, 0x7F);
    delay(1500);
  }
  
  for (uint i = 0; i < MAX_BRIGHTNESS + 1; i++) {
    rgb(MAX_BRIGHTNESS - i, 0, i, 0x7F);
    delay(1500);
  }
}

void rainbow() {
  uint m = MAX_BRIGHTNESS;
  pixels.clear();
  pixels.setPixelColor(0, m, 0, 0);
  pixels.setPixelColor(1, 0, m, 0);
  pixels.setPixelColor(2, 0, 0, m);
  pixels.setPixelColor(3, m, m, 0);
  pixels.setPixelColor(4, 0, m, m);
  pixels.setPixelColor(5, m, 0, m);
  pixels.setPixelColor(6, m, m, m);
  pixels.show();
  delay(3000);
}

void loop() {
  for (uint i = 0; i < 11; i++) {
    rgb(MAX_BRIGHTNESS, 0, 0, num2dig(i));
    delay(1000);
  }

  for (uint i = 1; i < 8; i++)
    rgb_loop(i);

  for (uint i = 1; i < 4; i++)
    blink_rgb();

  rainbow();
}
