byte settingCursor =1;
byte settingsShown =0;
void settings(){
  if(settingsShown ==0){
      settingsShown =1;
      pixels.clear();
      //orientationLights();
      for (byte i = 0; i<= 4; i++){ pixels.setPixelColor(i,pixels.Color(70,70,70));} 
      pixels.setPixelColor(11,pixels.Color(70,70,70));
      byte settingCursorLED =0;
      settingCursorLED= settingCursor -2;
      if(settingCursor ==1){settingCursorLED=11;}
      pixels.setPixelColor(settingCursorLED,pixels.Color(255,0,0));
      pixels.show();
      //Serial.println("led");
  }
  
  if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
    downButtonrelease = 1;
    downButton = 1;
        }
  //Serial.print("setting Cursor");  Serial.println(settingCursor); 
  if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
    upButtonrelease = 1;
    upButton = 1;
        }

  if(upButton== 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
    gotoProgramm (); resetbuttons();
        }
    
  if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
    settingCursor--;settingsShown =0; resetbuttons(); //adjustAutoBrightness();
        }

  if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
    settingCursor++;settingsShown =0; resetbuttons();
        }
  if (settingCursor >=7){settingCursor = 1;}
  if (settingCursor ==0){settingCursor = 6;}
 
}

void settingsReset (){
  settingCursor =1;
  settingsShown =0;
}

void gotoProgramm (){
  if (settingCursor==1){runningProg= 7;}
  if (settingCursor==2){runningProg= 8;}
  if (settingCursor==3){runningProg= 9;}
  if (settingCursor==4){runningProg= 10;}
  if (settingCursor==5){runningProg= 11;}
  if (settingCursor==6){runningProg= 12;}
  settingsReset ();
}
