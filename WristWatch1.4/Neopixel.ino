#define NUMPIXELS 12
Adafruit_NeoPixel pixels(NUMPIXELS, leddataPin, NEO_GRB + NEO_KHZ800);
void neopixelSetup (){
  pixels.begin();
}
