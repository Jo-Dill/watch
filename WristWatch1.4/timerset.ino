
byte timerRepetitions = 0;
unsigned long timerMinutesLedTime =0;

void timerSet (){
 byte overlapping =0;
 //Serial.print("timerStep");Serial.print(timerStep);Serial.print(" timerHours");Serial.print(timerHours);Serial.print(" timerMinutes");Serial.println(timerMinutes);
 switch(timerStep){
  case 0: //set hours
    if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
        downButtonrelease = 1;
        downButton = 1;
        }
   
      if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
         upButtonrelease = 1;
         upButton = 1;
        }
   
      if(upButton== 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
           timerStep=1; resetbuttons();
        }
    
      if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
           timerHours++; resetbuttons();
        }

      if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
           timerHours--; resetbuttons();
        }
            
      if(timerHours > 11 && timerHours <250){timerHours=timerHours-12;}
      if(timerHours >250){timerHours =11;}
      pixels.clear();
      orientationLights();
      if(timerHours==0){pixels.setPixelColor(11, pixels.Color(0,255,0));}
      else{ pixels.setPixelColor((timerHours-1), pixels.Color(0,255,0));}
      pixels.show();
     
  break;
  case 1: //set minutes in 5er Blocks
      if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
        downButtonrelease = 1;
        downButton = 1;
        }
   
      if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
         upButtonrelease = 1;
         upButton = 1;
        }
   
      if(upButton== 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
           timerStep=2; resetbuttons();
        }
    
      if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
           timerMinutes += 5; resetbuttons();
        }

      if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
           timerMinutes -= 5; resetbuttons();
        }
      if(timerMinutes>250){timerMinutes=55;}
      if(timerMinutes>55 && timerMinutes<250){timerMinutes=0;}
            
      pixels.clear();
      orientationLights();
      overlapping = 0;
      if(timerMinutes<5){
        if (0!=timerHours){ pixels.setPixelColor((timerHours-1), pixels.Color(0,255,0)); overlapping=0;}else{overlapping=255;} 
        pixels.setPixelColor(11, pixels.Color(255,overlapping,0));
      }else{
        if ((timerMinutes/5) !=timerHours){ 
         pixels.setPixelColor((timerHours-1), pixels.Color(0,255,0)); overlapping=0; 
         if(timerHours==0){pixels.setPixelColor(11, pixels.Color(0,255,0));}
        }else{overlapping=255;}
        pixels.setPixelColor(((timerMinutes/5)-1), pixels.Color(255,overlapping,0));
      }
      pixels.show();
    

  break;
  case 2: //set minutes precise
     if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
        downButtonrelease = 1;
        downButton = 1;
        }
   
      if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
         upButtonrelease = 1;
         upButton = 1;
        }
   
      if(upButton== 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
           timerStep=3; resetbuttons();
        }
    
      if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
           timerMinutes ++; resetbuttons();
        }

      if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
           timerMinutes --; resetbuttons();
        }

      if(timerMinutes>250){timerMinutes=59;}
      if(timerMinutes>59 && timerMinutes<250){timerMinutes=0;}

       pixels.clear();
       orientationLights();
       byte timerMinuteLED;
       byte timerHoursLED;
       if(timerHours !=0){timerHoursLED=timerHours;}else{timerHoursLED=12;}
       if(timerMinutes<5){
          timerMinuteLED=12; 
          if(timerRepetitions==7){timerRepetitions = timerMinutes +1; timerMinutesLedTime= millis(); }
       }else{
          timerMinuteLED = timerMinutes / 5;
          if(timerRepetitions==7){timerRepetitions = timerMinutes -(timerMinuteLED * 5 )+1; timerMinutesLedTime= millis(); }
       }
       overlapping = 0;
        if (timerMinuteLED != timerHoursLED){ pixels.setPixelColor((timerHoursLED-1), pixels.Color(0,255,0)); overlapping=0;}else{overlapping=255;}
        
        pixels.setPixelColor((timerMinuteLED-1), pixels.Color(255,overlapping,0));
        if ((millis() -timerMinutesLedTime)>200){pixels.setPixelColor((timerMinuteLED-1), pixels.Color(0,overlapping,0));}
        if (((millis() -timerMinutesLedTime)>400) && timerRepetitions > 0){timerMinutesLedTime= millis(); timerRepetitions = timerRepetitions-1;}
        if (timerRepetitions <= 0){
            pixels.setPixelColor((timerMinuteLED-1), pixels.Color(0,overlapping,0));
            //pixels.setPixelColor((timerHours-1), pixels.Color(0,0,0));
            if((millis() -timerMinutesLedTime)>1000){
              timerRepetitions=7;  
            }
        }
        pixels.show();
      
  break;
  case 3: //save
      pixels.clear();
      pixels.show();
      playsound(1); 
      byte hoursnow= rtc.getHours();
      byte minutesnow= rtc.getMinutes();
      byte wakeUpHours=0;
      byte wakeUpMinutes=0;
      if ((timerMinutes + minutesnow)>=60){timerHours++; wakeUpMinutes= (timerMinutes+minutesnow)-60;}else{wakeUpMinutes=minutesnow+timerMinutes;}
      if ((timerHours+hoursnow)>=24){wakeUpHours=(timerHours+hoursnow)-24;}else{wakeUpHours=timerHours+hoursnow;}
      rtc.setAlarmTime(wakeUpHours, wakeUpMinutes, rtc.getSeconds());
      rtc.enableAlarm(rtc.MATCH_HHMMSS);
      standbyTime = 400;
      standbystate = 1 ;
      timerStep=3;
  break;
 }
}


void timerSetReset(){
  timerStep=0;
  timerHours = 0;
  timerMinutes = 0;
  timerRepetitions = 0;
}
