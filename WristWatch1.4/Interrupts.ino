volatile byte alarmflag =0;
volatile byte downbuttonflag =0;
volatile byte upbuttonflag =0;

void interruptSetup(){
  LowPower.attachInterruptWakeup(RTC_ALARM_WAKEUP, wokeUpbyAlarm, CHANGE);
  LowPower.attachInterruptWakeup(upbuttonPin, wokeUpbyUpbutton, FALLING);
  LowPower.attachInterruptWakeup(downbuttonPin, wokeUpbyDownbutton, FALLING);
}

void wokeUpbyAlarm (){
  alarmflag=1;
}
void wokeUpbyDownbutton (){
  downbuttonflag =1;
}

void wokeUpbyUpbutton (){
  upbuttonflag =1;
}
