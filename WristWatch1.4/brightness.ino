/*Brightness: 0-255 als Faktor in die Helligkeit
 */
byte manualBrightness = 5; //can contain a number from 0 to to 5
byte autoBrightness = 10; // can contain a number from 0 to 50
int brightSensorVal = 300; //pre 250;
int darkSensorVal = 5; //pre: 50
byte orientationLightBorder =4;
int PreVal=0;
byte brightnessStep =0;
byte brightnessshown=0;
void Brightness(){
  standbyTime= 6000;
  //Serial.print("manualBrightness :"); Serial.print(manualBrightness); Serial.print(" brightSensorVal :"); Serial.print(brightSensorVal); Serial.print(" darkSensorVal :"); Serial.print(darkSensorVal); Serial.print(" orientationLightBorder :");Serial.println(orientationLightBorder);
  switch(brightnessStep){
    case 0:
      if(brightnessshown==0){
        brightnessshown=1;
        byte LED = map(brightness,0,255,0,NUMPIXELS);
        pixels.clear();
        
        byte r=1; byte g=1; byte b=1;
        
        for (int i=0;i< LED;i++){pixels.setPixelColor((i), pixels.Color((r*70),(g*70),(b*70))); delay(100);pixels.show();}
        delay(100);
        pixels.setPixelColor(LED, pixels.Color((r*255),(g*255),(b*255)));
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
           brightnessStep=1; brightnessshown=0;  resetbuttons();
        }
      if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
           brightnessshown=0; resetbuttons();
        }
        
      
    break;
    case 1:
    if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
        downButtonrelease = 1;
        downButton = 1;
        }
   
      if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
         upButtonrelease = 1;
         upButton = 1;
        }
   
      if(upButton== 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
           brightnessStep=2; PreVal=brightSensorVal; brightness=  manualBrightness * autoBrightness; pixels.setBrightness(brightness); resetbuttons();
        }
    
      if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
           manualBrightness++; resetbuttons();
        }

      if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
           manualBrightness--; resetbuttons();
        }
      if (manualBrightness>5){manualBrightness=1;}
      if (manualBrightness<1 ){ manualBrightness=5;}
      brightness=  manualBrightness * autoBrightness; 
      pixels.clear();
      pixels.setBrightness(brightness);
      pixels.setPixelColor(11, pixels.Color(255,255,255));  
      pixels.show(); 
    break;

    case 2:
      if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
        downButtonrelease = 1;
        downButton = 1;
        }
   
      if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
         upButtonrelease = 1;
         upButton = 1;
        }
   
      if(upButton== 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
           brightnessStep=3; PreVal=darkSensorVal;  resetbuttons();
        }
    
      if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
           brightSensorVal++; /*Serial.print(" brightSensorVal :"); Serial.print(brightSensorVal);*/ adjustAutoBrightness(); resetbuttons();
        }

      if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
           brightSensorVal--;/* Serial.print(" brightSensorVal :"); Serial.print(brightSensorVal); */adjustAutoBrightness(); resetbuttons();
        }
      pixels.clear();  
      if (digitalRead(downbuttonPin)== LOW && (brightSensorVal != PreVal)){
      pixels.setPixelColor(3, pixels.Color(255,255,255));   
      }
      if (digitalRead(upbuttonPin)== LOW && (brightSensorVal != PreVal)){
      pixels.setPixelColor(1, pixels.Color(255,255,255));   
      }
      if(brightSensorVal == PreVal){pixels.setPixelColor(2, pixels.Color(255,255,0));}
      pixels.show();
      
    break;
    case 3:
      if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
        downButtonrelease = 1;
        downButton = 1;
        }
   
      if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
         upButtonrelease = 1;
         upButton = 1;
        }
   
      if(upButton== 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
           brightnessStep=4; PreVal=orientationLightBorder;   resetbuttons();
        }
    
      if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
           darkSensorVal++;/* Serial.print(" darkSensorVal :"); Serial.print(darkSensorVal);*/ adjustAutoBrightness(); resetbuttons();
        }

      if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
           darkSensorVal--;/* Serial.print(" darkSensorVal :"); Serial.print(darkSensorVal);*/ adjustAutoBrightness(); resetbuttons();
        }
      pixels.clear();  
      if (digitalRead(downbuttonPin)== LOW && (darkSensorVal != PreVal)){
      pixels.setPixelColor(3, pixels.Color(255,255,255));   
      }
      if (digitalRead(upbuttonPin)== LOW && (darkSensorVal != PreVal)){
      pixels.setPixelColor(1, pixels.Color(255,255,255));   
      }
      if(darkSensorVal == PreVal){pixels.setPixelColor(2, pixels.Color(0,255,255));}
      
      pixels.show();
      
    break;
    case 4:
        if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
        downButtonrelease = 1;
        downButton = 1;
        }
   
      if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
         upButtonrelease = 1;
         upButton = 1;
        }
   
      if(upButton== 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
           runningProg=0; brightnessReset();  resetbuttons();
        }
    
      if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
           orientationLightBorder++;/* Serial.print(" orientationLightBorder :");Serial.println(orientationLightBorder);*/ adjustAutoBrightness(); resetbuttons();
        }

      if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
           orientationLightBorder--;/* Serial.print(" orientationLightBorder :");Serial.println(orientationLightBorder);*/ adjustAutoBrightness(); resetbuttons();
        }
      pixels.clear();  
      if (digitalRead(downbuttonPin)== LOW && (orientationLightBorder != PreVal)){
      pixels.setPixelColor(3, pixels.Color(255,255,255));   
      }
      if (digitalRead(upbuttonPin)== LOW && (orientationLightBorder != PreVal)){
      pixels.setPixelColor(1, pixels.Color(255,255,255));   
      }
      if(orientationLightBorder == PreVal){pixels.setPixelColor(2, pixels.Color(0,255,0));}
      
      orientationLights();
      pixels.show();
    break;
  }
}

void brightnessReset(){
    brightnessStep=0;
    brightnessshown=0;
}

void adjustAutoBrightness(){
  digitalWrite(lightsensorVCCPin,HIGH);
  digitalWrite(lightsensorActivatePin,HIGH);
  pixels.clear();
  pixels.show();
  delay(200);
  int LightSensorVal =analogRead(lightsensorInPin); 
  if (LightSensorVal>brightSensorVal){LightSensorVal=brightSensorVal;}
  if (LightSensorVal<darkSensorVal){LightSensorVal=darkSensorVal;}
  
  autoBrightness =map(LightSensorVal,darkSensorVal,brightSensorVal,1,50);
  //Serial.print("LightSensorval :"); Serial.println(LightSensorVal);
  //Serial.print("autobrightness :"); Serial.println(autoBrightness);
  digitalWrite(lightsensorVCCPin,LOW);
  digitalWrite(lightsensorActivatePin,LOW);
  AutoBrightness();
  
}

void AutoBrightness(){
 brightness=  manualBrightness * autoBrightness;
    pixels.clear();
    pixels.setBrightness(brightness);
    //pixels.setPixelColor(11, pixels.Color(255,255,255));  
    pixels.show(); 
}

void orientationLights(){
  if(autoBrightness<orientationLightBorder){
  /*pixels.setPixelColor(2, pixels.Color(40,40,0));
   *pixels.setPixelColor(5, pixels.Color(40,40,0));
   *pixels.setPixelColor(8, pixels.Color(40,40,0));
   *pixels.setPixelColor(11, pixels.Color(40,40,0)); 
   */
   pixels.setPixelColor(2, pixels.Color(0,0,40));
   pixels.setPixelColor(5, pixels.Color(0,0,40));
   pixels.setPixelColor(8, pixels.Color(0,0,40));
   pixels.setPixelColor(11, pixels.Color(0,0,40));
  }
}
