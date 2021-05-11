unsigned long resetTime =0;

void standbyreset(){
  resetTime = millis();
}

void standbyloop () {
  if(standbystate ==1){
    if (millis()-resetTime > standbyTime){
     shutDown();
    }
  }else{
    //standbyreset();
  }
  if (digitalRead(upbuttonPin)== LOW ){standbyreset();}
  if (digitalRead(downbuttonPin)== LOW ){standbyreset();}
}

void shutDown (){
  digitalWrite(ledactivatePin ,LOW);
  //Serial.println("going to sleep");
  runningProg=3;
  upbuttonflag=0;
  downbuttonflag=0;
  startup=0;
  LowPower.deepSleep();
}
