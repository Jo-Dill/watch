
void buttonHandler(){
  const byte minreleaseTime = 100;
  if (upButtonrelease ==1 && upButtonrealeaseTimer ==0){upButtonrealeaseTimer= millis();}
  if (upButtonrelease ==1 && digitalRead(upbuttonPin)== LOW){upButtonrealeaseTimer=0;}
  if (upButtonrelease ==1 && upButtonrealeaseTimer != 0 && (millis()-upButtonrealeaseTimer)>minreleaseTime ){upButtonrelease=0;/*Serial.println("buttonreset");*/}
  
  if (downButtonrelease ==1 && downButtonrealeaseTimer ==0){downButtonrealeaseTimer= millis();}
  if (downButtonrelease ==1 && digitalRead(downbuttonPin)== LOW){downButtonrealeaseTimer=0;}
  if (downButtonrelease ==1 && downButtonrealeaseTimer != 0 && (millis()-downButtonrealeaseTimer)>minreleaseTime ){downButtonrelease=0;/* Serial.println("buttonreset");*/}
}

void resetbuttons(){
  downButton = 0; 
  upButton = 0; 
}
/*
void test3 (){
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
*/
unsigned long lastChangeTime =0;
byte Led=0;
void test () {
    int ledChangetime = 150;
    
  if (millis()-lastChangeTime >= ledChangetime){
    lastChangeTime = millis();
    pixels.clear();
    if (Led < (NUMPIXELS-1)){Led ++;}
    else{Led=0;pixels.clear();}
   // pixels.clear();
    pixels.setPixelColor(Led, pixels.Color(255,255,255));
    pixels.show();
  }
}
