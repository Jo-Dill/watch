void timerSet (){
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(0,0,(5*brightness)));
  pixels.show();
}
