    unsigned long lastLedChangeTime =0 ;
    byte alarmLed = 0;

  byte melodystep = 0;
  unsigned long lastmelodyChangeTime =0 ;
void alarm (){
  standbyTime = 180000;  
  pixels.setBrightness(200);
  const int ledChangetime = 100;
  if (millis()-lastLedChangeTime >= ledChangetime){
    lastLedChangeTime = millis();
    if (alarmLed < (NUMPIXELS-1)){alarmLed ++;}
    else{alarmLed=0;}
    pixels.clear();
    pixels.setPixelColor(alarmLed, pixels.Color(255, 0, 0));
    pixels.show();
  }

  const byte melody1_lenghth = 8;
  //const int melody1_frequency []={0,4000,0,4000,0,4000,0,4000};
  const int melody1_frequency []={0,3000,0,3000,0,4000,0,5000};
  const int melody1_duration []={2000,100,50,100,50,100,50,100};
  if (millis()- lastmelodyChangeTime > melody1_duration[melodystep]){
    lastmelodyChangeTime= millis();
    if(melodystep< melody1_lenghth){melodystep++;}else{melodystep=0;}
    tone(buzzerPin, melody1_frequency [melodystep], melody1_duration [melodystep]);
    if(melody1_frequency [melodystep]==0){noTone(buzzerPin);digitalWrite(buzzerPin, LOW);}
  } 
  //if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){runningProg=0; upButtonrelease =1; AutoBrightness(); standbyTime = 2000;}
  //if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){runningProg=0; downButtonrelease =1; AutoBrightness(); standbyTime = 2000;}
  
    if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
        downButtonrelease = 1;
        downButton = 1;
        }
   
    if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
         upButtonrelease = 1;
         upButton = 1;
        }
   
    if(upButton== 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
          runningProg=0; AutoBrightness(); noTone(buzzerPin); deleteAlarm(); standbyTime = 2000; resetbuttons();
        }
    
    if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
           timerSetReset();
           timerStep=3;
           timerMinutes = 5;
           runningProg=5;
           resetbuttons();
        }

    if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
           timerSetReset();
           timerStep=3;
           timerMinutes = 1;
           runningProg=5;
           resetbuttons();
        }
            
}
