
void RTCSetup (){
  const byte seconds = 0;
  const byte minutes = 0;
  const byte hours = 0;
  
  const byte day = 9;
  const byte month = 3;
  const byte year = 21;
  rtc.begin();
  rtc.setTime(hours, minutes, seconds);
  rtc.setDate(day, month, year);
}
