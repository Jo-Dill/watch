void batteryLevel (){
  digitalWrite(batteryreaderOutPin, HIGH);
  byte lastLED = map(analogRead(batteryreaderInPin),409,475,1,NUMPIXELS);
  pixels.clear();
  for (int i=0; i<=(NUMPIXELS-1);i++){pixels.setPixelColor((alarmHours-1), pixels.Color(0,(5*brightness),0));}
  for (int i=(NUMPIXELS-1);i>=lastLED;i--){pixels.setPixelColor((alarmHours-1), pixels.Color(0,0,0));}
  pixels.show();
  
}

void batteryLevelSetup(){
  analogReference(AR_INTERNAL2V23); //change the reference from default:external to 2.23V:internal
  for (int i =0; i<10; i++){analogRead (batteryreaderInPin);} // read something a couple of time so that the reference gets set up
  
}
