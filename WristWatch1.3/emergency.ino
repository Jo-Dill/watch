int FlashlightBrightness =250;

void Flashlight(){ 
  standbystate = 0 ;
  if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
        downButtonrelease = 1;
        downButton = 1;
  }
   
 if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
         upButtonrelease = 1;
         upButton = 1;
  }
  
  if(upButton== 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
      runningProg=0; standbystate = 1; resetbuttons();
  }
    
  if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
      FlashlightBrightness+=10; resetbuttons();
  }

  if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
      FlashlightBrightness-=10; resetbuttons();
  }
  
  if (FlashlightBrightness > 255){FlashlightBrightness= (-165);}
  if (FlashlightBrightness < (-165)){FlashlightBrightness= 255;}
  
  if (FlashlightBrightness>0){
   pixels.clear(); 
   pixels.setBrightness(255);
    for(int i=0;i<=11;i++){ pixels.setPixelColor(i, pixels.Color(FlashlightBrightness,FlashlightBrightness,FlashlightBrightness));}
   pixels.show();
  }
  
  if (FlashlightBrightness<0){
    pixels.clear(); 
    for(int i=0;i<=11;i++){pixels.setPixelColor(i, pixels.Color((FlashlightBrightness * (-1)),0,0));}
    pixels.show();
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
      for(int i=2;i<=11;i+=3){pixels.setPixelColor(i, pixels.Color(FlashlightBrightness,0,0));}
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
      runningProg=0; standbystate = 1; resetbuttons();
  }
    
  if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
      FlashlightBrightness+=10; resetbuttons();
  }

  if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
      FlashlightBrightness-=10; resetbuttons();
  }
  
  if (FlashlightBrightness > 165){FlashlightBrightness= 5;}
  if (FlashlightBrightness < 0){FlashlightBrightness= 165;}

  delay(50);
}
