byte alarmHours = 0;
byte alarmMinutes = 0;
byte alarmStep =0;
byte alarmRepetitions = 0;
byte alarmMinuteLed =0;
unsigned long alarmMinutesLedTime =0;

void alarmSet (){
  byte overlapping = 0;
  
  //Serial.print("alarmStep");Serial.print(alarmStep);Serial.print(" alarmHours");Serial.print(alarmHours);Serial.print(" alarmMinutes");Serial.println(alarmMinutes);
  switch (alarmStep){
    case 0://set hours
     if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
        downButtonrelease = 1;
        downButton = 1;
        }
   
      if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
         upButtonrelease = 1;
         upButton = 1;
        }
   
      if(upButton== 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
           alarmStep=1; resetbuttons();
        }
    
      if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
           alarmHours++; resetbuttons();
        }

      if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
           alarmHours--; resetbuttons();
        }
            
      if(alarmHours > 12){alarmHours=alarmHours-12;}
      if(alarmHours <= 0){alarmHours =12;}
      pixels.clear();
      orientationLights();
      pixels.setPixelColor((alarmHours-1), pixels.Color(0,255,0));
      pixels.show();
     
    break;

    case 1: // set minutes in 5er Blocks
      //Serial.println(alarmMinutes);
      if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
        downButtonrelease = 1;
        downButton = 1;
      
        }
   
      if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
         upButtonrelease = 1;
         upButton = 1;
         
        }
   
      if(upButton== 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
           alarmStep=2; resetbuttons();
        }
    
      if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
           alarmMinutes += 5; resetbuttons();
        }

      if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
           alarmMinutes -= 5; resetbuttons();
        }
      if(alarmMinutes>250){alarmMinutes=55;}
      if(alarmMinutes>55 && alarmMinutes<250){alarmMinutes=0;}

          
      pixels.clear();
      orientationLights();
      overlapping = 0;
      if(alarmMinutes<5){if (12!=alarmHours){
        pixels.setPixelColor((alarmHours-1), pixels.Color(0,255,0)); overlapping=0;}else{overlapping=255;} 
        pixels.setPixelColor(11, pixels.Color(255,overlapping,0));
        pixels.show();
      }else{
        if ((alarmMinutes/5) !=alarmHours){ pixels.setPixelColor((alarmHours-1), pixels.Color(0,255,0)); overlapping=0;}else{overlapping=255;}
         pixels.setPixelColor(((alarmMinutes/5)-1), pixels.Color(255,overlapping,0));
      
      pixels.show();
    }


    break;

    case 2:  //set minutes precise
      if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
        downButtonrelease = 1;
        downButton = 1;
        }
   
      if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
         upButtonrelease = 1;
         upButton = 1;
        }
   
      if(upButton== 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
           alarmStep=3; resetbuttons();
        }
    
      if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
           alarmMinutes ++; resetbuttons();
        }

      if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
           alarmMinutes --; resetbuttons();
        }

      if(alarmMinutes>250){alarmMinutes=59;}
      if(alarmMinutes>59 && alarmMinutes<250){alarmMinutes=0;}

       pixels.clear();
       orientationLights();
       if(alarmMinutes<5){
          alarmMinuteLed=12; 
          if(alarmRepetitions==7){alarmRepetitions = alarmMinutes +1; alarmMinutesLedTime= millis(); }
       }else{
          alarmMinuteLed = alarmMinutes / 5;
          if(alarmRepetitions==7){alarmRepetitions = alarmMinutes -(alarmMinuteLed * 5 )+1; alarmMinutesLedTime= millis(); }
       }
       overlapping = 0;
        if (alarmMinuteLed != alarmHours){ pixels.setPixelColor((alarmHours-1), pixels.Color(0,255,0)); overlapping=0;}else{overlapping=255;}
        
        pixels.setPixelColor((alarmMinuteLed-1), pixels.Color(255,overlapping,0));
        if ((millis() -alarmMinutesLedTime)>200){pixels.setPixelColor((alarmMinuteLed-1), pixels.Color(0,overlapping,0));}
        if (((millis() -alarmMinutesLedTime)>400) && alarmRepetitions > 0){alarmMinutesLedTime= millis(); alarmRepetitions = alarmRepetitions-1;}
        if (alarmRepetitions <= 0){
            pixels.setPixelColor((alarmMinuteLed-1), pixels.Color(0,overlapping,0));
            //pixels.setPixelColor((alarmHours-1), pixels.Color(0,0,0));
            if((millis() -alarmMinutesLedTime)>1000){
              alarmRepetitions=7;  
            }
        }
        pixels.show();
      
    break;

    case 3: //save settings
        pixels.clear();
        pixels.show();
        playsound(1);
        byte hoursnow= rtc.getHours();
        byte minutesnow= rtc.getMinutes();
        if (alarmHours== 12){alarmHours= 0;}
        if (hoursnow > alarmHours){alarmHours +=12;}
        if (hoursnow == alarmHours && minutesnow > alarmMinutes){alarmHours +=12;}
        rtc.setAlarmTime(alarmHours, alarmMinutes, 0);
        rtc.enableAlarm(rtc.MATCH_HHMMSS);
        standbyTime = 400;
        standbystate = 1 ;
        alarmStep=4;
    break;
    
 
  }
}

void deleteAlarm(){
  rtc.disableAlarm();
  alarmReset();
  pixels.clear();
  pixels.show();
  runningProg=0;
  delay(100);
  tone(buzzerPin, 4000, 30);
  delay(150);
  tone(buzzerPin, 3000, 30);
}

void alarmReset(){
  alarmStep =0;
  alarmMinutes =0;
  alarmHours = 0;
  alarmRepetitions = 0;
  alarmMinutesLedTime =0;
  alarmMinuteLed =0;
}
