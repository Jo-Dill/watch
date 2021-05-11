    unsigned long lastLedChangeTime =0 ;
    byte alarmLed = 0;

  byte melodystep = 0;
  unsigned long lastmelodyChangeTime =0 ;
void alarm (){
  standbyTime = 120000;  
  const int ledChangetime = 500;
  if (millis()-lastLedChangeTime >= ledChangetime){
    lastLedChangeTime = millis();
    if (alarmLed < NUMPIXELS){alarmLed ++;}
    else{alarmLed=0;}
    pixels.clear();
    pixels.setPixelColor(alarmLed, pixels.Color((5*brightness), 0, 0));
    pixels.show();
  }

  const byte melody1_lenghth = 8;
  const int melody1_frequency []={0,4000,0,4000,0,4000,0,4000};
  const int melody1_duration []={2000,30,100,30,100,30,100,30};
  if (millis()- lastmelodyChangeTime > melody1_duration[melodystep]){
    lastmelodyChangeTime= millis();
    if(melodystep< melody1_lenghth){melodystep++;}else{melodystep=0;}
    tone(buzzerPin, melody1_frequency [melodystep], melody1_duration [melodystep]);
    if(melody1_frequency [melodystep]==0){noTone(buzzerPin);digitalWrite(buzzerPin, LOW);}
  } 
  if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){runningProg=0; upButtonrelease =1; standbyTime = 2000;}
  if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){runningProg=0; downButtonrelease =1; standbyTime = 2000;}
}
