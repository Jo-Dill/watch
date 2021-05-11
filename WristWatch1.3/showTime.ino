byte shown = 0; //says if time is already diplayed,  0: no , 1 yes
void showSimpleTime(){

  
  byte hours = rtc.getHours();
  if(hours > 12){hours=hours-12;}
  if(hours == 0){hours=12;}
  byte minutes = rtc.getMinutes();
  minutes= minutes / 5;
  byte overlapping = 0;
  if (minutes != hours){  overlapping=0;}else{overlapping=(5*brightness);}
  pixels.clear();
  pixels.setPixelColor((minutes-1), pixels.Color((5*brightness),overlapping,0));
  
  if (minutes != hours){ pixels.setPixelColor((hours-1), pixels.Color(0,(5*brightness),0));}
  pixels.show();
  if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
        upButtonrelease=1;
        runningProg =3;
        shown =0;
  }
}

int repetitions = 7;
byte minuteLed = 13;
unsigned long minutesLedTime = 0;
void showCompleteTime(){
  pixels.clear();
  byte hours = rtc.getHours();
  if(hours > 12){hours=hours-12;}
  if(hours == 0){hours=12;}
  byte minutes = rtc.getMinutes();
  if(minuteLed==13){ minuteLed = minutes / 5;}
  if(repetitions==7){repetitions = minutes -(minuteLed * 5 )+1; minutesLedTime= millis(); }
  byte overlapping = 0;
  if (minuteLed != hours){ pixels.setPixelColor((hours-1), pixels.Color(0,(5*brightness),0)); overlapping=0;}else{overlapping=(5*brightness);}
  
  pixels.setPixelColor((minuteLed-1), pixels.Color((5*brightness),overlapping,0));
  if ((millis() -minutesLedTime)>200){pixels.setPixelColor((minuteLed-1), pixels.Color(0,overlapping,0));}
  if (((millis() -minutesLedTime)>400) && repetitions > 0){minutesLedTime= millis(); repetitions = repetitions-1;}
  if (repetitions <= 0){
    pixels.setPixelColor((minuteLed-1), pixels.Color(0,overlapping,0));
    pixels.setPixelColor((hours-1), pixels.Color(0,0,0));
    if((millis() -minutesLedTime)>500){
      if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
        downButtonrelease=1;
        repetitions=7;  
        minuteLed=13;
      }
    }
    //if((millis() -minutesLedTime)>1500){shutDown();}
  }
  
  pixels.show();

  if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
        upButtonrelease=1;
        runningProg =3;
  }
/*
  if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){

    pixels.clear(); // not debugged power off part
    pixels.show();
    standbyTime= 100;

    
  }
  */
}
void showCompleteTimeReset(){
  repetitions = 7;
  minuteLed=13;
  minutesLedTime = 0;

  shown=0;
}
