byte shown = 0; //says if time is already diplayed,  0: no , 1 yes
void showSimpleTime(){
  byte overlapping = 0;
  
  byte hours = rtc.getHours();
  if(hours > 12){hours=hours-12;}
  if(hours == 0){hours=12;}
  byte minutes = rtc.getMinutes();
  if(minutes<5){
    if (12 != hours){  overlapping=0;}else{overlapping=255;}
    pixels.clear();
    orientationLights();
    pixels.setPixelColor(11, pixels.Color(255,overlapping,0));
    if (12 != hours){ pixels.setPixelColor((hours-1), pixels.Color(0,255,0));}
  }else{
    minutes= minutes / 5;
    if (minutes != hours){  overlapping=0;}else{overlapping=255;}
    pixels.clear();
    orientationLights();
    pixels.setPixelColor((minutes-1), pixels.Color(255,overlapping,0));
    if (minutes != hours){ pixels.setPixelColor((hours-1), pixels.Color(0,255,0));}
  }
  pixels.show();
  if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
        upButtonrelease=1;
        runningProg =3;
        shown =0;
       // adjustAutoBrightness();
  }
}

int repetitions = 7;
byte minuteLed = 13;
unsigned long minutesLedTime = 0;
void showCompleteTime(){
  pixels.clear();
  orientationLights();
  byte hours = rtc.getHours();
  if(hours > 12){hours=hours-12;}
  if(hours == 0){hours=12;}
  byte minutes = rtc.getMinutes();
  if(minuteLed==13){
    if(minutes<5){
      minuteLed=12;
    }else{
      minuteLed = minutes / 5;
    }
  }
  if(repetitions==7){
    if(minutes<5){
      repetitions = minutes +1; minutesLedTime= millis(); 
    }else{
      repetitions = minutes -(minuteLed * 5 )+1; minutesLedTime= millis(); 
    }
    
  }
  byte overlapping = 0;
  if (minuteLed != hours){ pixels.setPixelColor((hours-1), pixels.Color(0,255,0)); overlapping=0;}else{overlapping=255;}
  
  pixels.setPixelColor((minuteLed-1), pixels.Color(255,overlapping,0));
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
