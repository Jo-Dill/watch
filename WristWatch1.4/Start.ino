

void start (){
  pixels.clear();
  pixels.show();
  //delay(10000);
  runningProg =0;
  if (alarmflag==1){alarmflag=0; runningProg = 2;}
  if (upbuttonflag==1){upbuttonflag=0; runningProg = 0;}
  if (downbuttonflag==1){downbuttonflag=0; runningProg = 1;}
  standbyreset();
  digitalWrite(ledactivatePin ,HIGH);
  startup = 1;

  upButtonrelease=1;   //because button was pressed on wakeup
  downButtonrelease=1;

  
  downButtonrealeaseTimer = 0; //reseting some stuff
  upButtonrealeaseTimer = 0;
  showCompleteTimeReset();
  resetbuttons();
  alarmReset();
  settingsReset ();
  TimeSetReset();
  timerSetReset();
  ResetSound();
  brightnessReset();
  batteryLevelReset();
  standbyTime= 3000;
  adjustAutoBrightness();
  
  delay(20);
}
