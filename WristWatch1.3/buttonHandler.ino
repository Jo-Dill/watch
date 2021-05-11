
void buttonHandler(){
  const byte minreleaseTime = 100;
  if (upButtonrelease ==1 && upButtonrealeaseTimer ==0){upButtonrealeaseTimer= millis();}
  if (upButtonrelease ==1 && digitalRead(upbuttonPin)== LOW){upButtonrealeaseTimer=0;}
  if (upButtonrelease ==1 && upButtonrealeaseTimer != 0 && (millis()-upButtonrealeaseTimer)>minreleaseTime ){upButtonrelease=0; Serial.println("buttonreset");}
  
  if (downButtonrelease ==1 && downButtonrealeaseTimer ==0){downButtonrealeaseTimer= millis();}
  if (downButtonrelease ==1 && digitalRead(downbuttonPin)== LOW){downButtonrealeaseTimer=0;}
  if (downButtonrelease ==1 && downButtonrealeaseTimer != 0 && (millis()-downButtonrealeaseTimer)>minreleaseTime ){downButtonrelease=0; Serial.println("buttonreset");}
}

void resetbuttons(){
  downButton = 0; 
  upButton = 0; 
}

void test (){
  if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
    upButtonrelease=1;
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color((25*brightness),0,0));
    pixels.show();
    Serial.println("buttonpressed");
    delay(20);
  }else{
    pixels.clear();
    pixels.show();
  }
  if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==1){
    Serial.println("failed buttonpress");
  }
}

void test2 () {
    int ledChangetime = 150;
  if (millis()-lastLedChangeTime >= ledChangetime){
    lastLedChangeTime = millis();
    if (alarmLed < (NUMPIXELS-1)){alarmLed ++;}
    else{alarmLed=0;pixels.clear();}
   // pixels.clear();
    pixels.setPixelColor(alarmLed, pixels.Color((5*brightness),(5*brightness),(5*brightness)));
    pixels.show();
  }
  
 
}
