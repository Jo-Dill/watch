#include "ArduinoLowPower.h"
#include <Adafruit_NeoPixel.h>
#include <RTCZero.h>
//--------------------------------------------------------Pins in Proto
#define  upbuttonPin           2   //buttons
#define  downbuttonPin     3
#define  batteryreaderOutPin       10     //batteryvoltage
#define  batteryreaderInPin     4
#define  lightsensorVCCPin         6     //lightsensor
#define  lightsensorActivatePin     5
#define  lightsensorInPin     7
#define  ledactivatePin      1           //led
#define  leddataPin     0
#define  buzzerPin      8               //buzzer



RTCZero rtc;

byte startup = 0; //0: no startup yet , 1: startup was done
byte runningProg= 0; //says what the watch should do
byte brightness = 0; //regulates the brightness can be from 0 to 255
byte standbystate = 0;//if autostandby is on: 1 , off: 0
byte upButtonrelease = 0; //if 1 button was already recognized
byte downButtonrelease = 0; //if 1 button was already recognized
unsigned long upButtonrealeaseTimer = 0;
unsigned long downButtonrealeaseTimer = 0;
int standbyTime = 3000; //defines the time between last valid button press and auto standby
byte downButton= 0;  // 1 if button pressed
byte upButton = 0;
byte SoundState=0; //is a sound playing or not
byte timerStep=0;  //timerset variables (here because c__alram needs access too)
byte timerHours = 0;
byte timerMinutes = 0;


void  pinSetup();
void  interruptSetup();
void  neopixelSetup();
void  showSimpleTime();
void  showCompleteTime();
void  alarm();
void  alarmSet();
void  timerSet();
void  settings();
void  menue();
void  buttonHandler();
void  standbyloop ();
void  standbyreset();
void  showCompleteTimeReset();
void  resetmenue();
void  timerSet();
void  Flashlight();
void  SOS ();

void setup() {
  Serial.begin(9600);
  batteryLevelSetup();
  pinSetup();
  interruptSetup(); //after PinSetup
  neopixelSetup();
  RTCSetup ();
  Serial.println("setupdone");
}

void loop() {
  //Serial.print("Time is :"); Serial.print(rtc.getHours()); Serial.println(rtc.getMinutes());
 // Serial.print("runningProg");Serial.println(runningProg);
//Serial.print("brightness :"); Serial.println(brightness);
if (startup == 0){start();}else{

switch (runningProg){
  case 0:
    showSimpleTime();
   break;
  case 1:
    showCompleteTime();
   break;
  case 2: 
    alarm();
   break;
  case 3:
    menue();
  break;
  case 4:
    alarmSet();
  break;
  case 5:
    timerSet(); 
  break;
  case 6:
    settings();
  break;
  case 7:
    deleteAlarm(); 
  break;
  case 8:
    batteryLevel(); //noch nicht fertig
  break;
  case 9:
    Flashlight(); 
  break;
  case 10:
    SOS (); 
  break;
  case 11:
    TimeSet();
  break;
  case 12:
    Brightness();
  break;
  case 13:
    AutoBrightness();//noch nicht fertig
  break;
  case 14:
    test();
  break;
  default:
  runningProg= 0;
  break;

}

if(SoundState!=0){SoundPlayer();}
buttonHandler ();
standbyloop ();
}
}
