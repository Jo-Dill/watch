byte TimeStep =0;
byte AmPM =0; // 1:am , 2:pm
byte TimeHours = 0;
byte TimeMinutes = 0;
byte TimeRepetitions = 0;
byte TimeMinuteLed =0;
unsigned long TimeMinutesLedTime =0;


void TimeSet(){
  
 byte overlapping = 0;
  
  switch (TimeStep){
    case 0: //set am / pm
      pixels.clear();
      pixels.setPixelColor(1, pixels.Color((5*brightness),(5*brightness),0));
      pixels.setPixelColor(2, pixels.Color(0,0,(5*brightness)));
      pixels.show();
   
      if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
         downButtonrelease = 1;
         downButton = 1;
       }
       
       if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
         upButtonrelease = 1;
         upButton = 1;
       }
       
        
       if(upButton == 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
         AmPM =1; TimeStep=1;  resetbuttons();
       }
    
       if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
         AmPM =2;  TimeStep=1; resetbuttons();
       }

    
    break;
    case 1://set hours
      if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
        downButtonrelease = 1;
        downButton = 1;
        }
   
      if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
         upButtonrelease = 1;
         upButton = 1;
        }
   
      if(upButton== 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
           TimeStep=2; resetbuttons();
        }
    
      if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
           TimeHours++; resetbuttons();
        }

      if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
           TimeHours--; resetbuttons();
        }
            
      if(TimeHours > 12){TimeHours=TimeHours-12;}
      if(TimeHours <= 0){TimeHours =12;}
      pixels.clear();
      pixels.setPixelColor((TimeHours-1), pixels.Color(0,(5*brightness),0));
      pixels.show();

    break;

    case 2: // set minutes in 5er Blocks
      if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
        downButtonrelease = 1;
        downButton = 1;
        }
   
      if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
         upButtonrelease = 1;
         upButton = 1;
        }
   
      if(upButton== 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
           TimeStep=3; resetbuttons();
        }
    
      if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
           TimeMinutes += 5; resetbuttons();
        }

      if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
           TimeMinutes -= 5; resetbuttons();
        }
            
      pixels.clear();
      overlapping = 0;
      if ((TimeMinutes/5) !=TimeHours){ pixels.setPixelColor((TimeHours-1), pixels.Color(0,(5*brightness),0)); overlapping=0;}else{overlapping=(5*brightness);}
      pixels.setPixelColor(((TimeMinutes/5)-1), pixels.Color((5*brightness),overlapping,0));
      pixels.show();


    break;

    case 3:  //set minutes precise
      if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
        downButtonrelease = 1;
        downButton = 1;
        }
   
      if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
         upButtonrelease = 1;
         upButton = 1;
        }
   
      if(upButton== 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
           TimeStep=4; resetbuttons();
        }
    
      if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
           TimeMinutes ++; resetbuttons();
        }

      if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
           TimeMinutes --; resetbuttons();
        }

       pixels.clear();
       byte TimeMinuteLED;
       TimeMinuteLed = TimeMinutes / 5;
       if(TimeRepetitions==7){TimeRepetitions = TimeMinutes -(TimeMinuteLed * 5 )+1; TimeMinutesLedTime= millis(); }
       overlapping = 0;
        if (TimeMinuteLed != TimeHours){ pixels.setPixelColor((TimeHours-1), pixels.Color(0,(5*brightness),0)); overlapping=0;}else{overlapping=(5*brightness);}
  
        pixels.setPixelColor((TimeMinuteLed-1), pixels.Color((5*brightness),overlapping,0));
        if ((millis() -TimeMinutesLedTime)>200){pixels.setPixelColor((TimeMinuteLed-1), pixels.Color(0,overlapping,0));}
        if (((millis() -TimeMinutesLedTime)>400) && TimeRepetitions > 0){TimeMinutesLedTime= millis(); TimeRepetitions = TimeRepetitions-1;}
        if (TimeRepetitions <= 0){
            pixels.setPixelColor((TimeMinuteLed-1), pixels.Color(0,overlapping,0));
            //pixels.setPixelColor((TimeHours-1), pixels.Color(0,0,0));
            if((millis() -TimeMinutesLedTime)>1000){
              TimeRepetitions=7;  
            }
        }
        pixels.show();
    break;

    case 4: //save settings
        pixels.clear();
        pixels.show();
        tone(buzzerPin, 4000, 30);
        delay(50);
        tone(buzzerPin, 5000, 30);
        delay(50);
        tone(buzzerPin, 6000, 30);
        if (TimeHours== 12){TimeHours= 0;}
        if (AmPM == 2){TimeHours += 12;}
        rtc.setTime(TimeHours, TimeMinutes,0);
        Serial.print("set Time to :"); Serial.print(TimeHours); Serial.println(TimeMinutes);
        delay(10);
        runningProg=0;
        TimeSetReset();
    break;
  }
}

void TimeSetReset(){
  
  TimeStep =0;
  AmPM =0; // 1:am , 2:pm
  TimeHours = 0;
  TimeMinutes = 0;
  TimeRepetitions = 0;
  TimeMinuteLed =0;
  TimeMinutesLedTime =0;

}
