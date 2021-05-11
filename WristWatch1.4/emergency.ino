int FlashlightBrightness =100;
int PreFlashlightBrightness =100;
void Flashlight(){ 
  standbystate = 0 ;
  //Serial.println(FlashlightBrightness);
    if (FlashlightBrightness > 130){FlashlightBrightness= (-255);}
  if (FlashlightBrightness < (-255)){FlashlightBrightness= 130;}

  if(PreFlashlightBrightness !=FlashlightBrightness){PreFlashlightBrightness =FlashlightBrightness; digitalWrite(ledactivatePin ,LOW); delay (10); digitalWrite(ledactivatePin ,HIGH);}
  if (FlashlightBrightness>0){
   pixels.clear(); 
   pixels.setBrightness(FlashlightBrightness);
    //for(int i=0;i<=3;i++){ pixels.setPixelColor(i, pixels.Color(255,255,255));}
   pixels.setPixelColor(11, pixels.Color(255,255,255));
   pixels.setPixelColor(2, pixels.Color(255,255,255));
   pixels.setPixelColor(5, pixels.Color(255,255,255));
   pixels.setPixelColor(8, pixels.Color(255,255,255));
   pixels.show();
  }
  
  if (FlashlightBrightness<0){
    pixels.clear(); 
    pixels.setBrightness((FlashlightBrightness*(-1)));
    for(int i=0;i<=11;i++){pixels.setPixelColor(i, pixels.Color(255,0,0));}
    pixels.show();
  }
  
  if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
        downButtonrelease = 1;
        downButton = 1;
  }
   
 if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
         upButtonrelease = 1;
         upButton = 1;
  }
  
  if(upButton== 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
      runningProg=0; AutoBrightness(); standbystate = 1; resetbuttons();
  }
    
  if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
      FlashlightBrightness+=30; resetbuttons();
  }

  if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
      FlashlightBrightness-=30; resetbuttons();
  }
  

  
}

unsigned long SOSTime =0;
byte selector =0;
void SOS(){
  standbystate = 0 ;
 # define kurz 400
 # define lang 1400
 # define Pause 200
 # define mittlerePause 440
 # define langePause 5000

 const int blinktimes [] ={kurz,Pause,kurz,Pause,kurz,mittlerePause,lang,Pause,lang,Pause,lang,mittlerePause,kurz,Pause,kurz,Pause,kurz,langePause};
 if((millis()-SOSTime)>blinktimes [selector]){
    SOSTime=millis();
    selector++;
    if(selector >= 18){selector=0;}
    if(blinktimes [selector]!=Pause && blinktimes [selector]!=langePause && blinktimes [selector]!=mittlerePause){
      for(int i=2;i<=11;i+=3){pixels.setPixelColor(i, pixels.Color(255,0,0));}
      pixels.show();
    }else{
      pixels.clear();
      pixels.show();
    }
 }

  if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
        downButtonrelease = 1;
        downButton = 1;
  }
   
 if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
         upButtonrelease = 1;
         upButton = 1;
  }
  
  if(upButton== 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
      runningProg=0; AutoBrightness(); standbystate = 1; resetbuttons();
  }
    
  if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
      FlashlightBrightness+=10;   pixels.setBrightness(FlashlightBrightness); resetbuttons();
  }

  if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
      FlashlightBrightness-=10;  pixels.setBrightness(FlashlightBrightness); resetbuttons();
  }
  
  if (FlashlightBrightness > 165){FlashlightBrightness= 5;}
  if (FlashlightBrightness < 1){FlashlightBrightness= 165;}
  
  
  delay(50);
}
