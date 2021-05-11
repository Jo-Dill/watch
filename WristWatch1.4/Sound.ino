unsigned long soundTime =0;
byte playingSound = 0;


void playsound(byte selectedsound){
  if(selectedsound!=0 && SoundState==0){SoundState=1; playingSound = selectedsound;}
}

byte soundstep=0;

void SoundPlayer(){

  
  switch (playingSound){
    case 0:
     
    break;
    case 1:
      
        const byte melody_lenghth = 4;
        const int melody_frequency []={0,3500,0,4500,0};
        const int melody_duration []={10,50,50,50,10};
       // const int melody1_frequency []={0,2000,0,3000,0,4000,0,5000};
        // const int melody1_duration []={2000,30,100,30,100,30,100,30};
        if (millis()- soundTime > melody_duration[soundstep]){
          soundTime= millis();
          soundstep++; //Serial.println("soundstep ++");
          if(soundstep< melody_lenghth){
            
            tone(buzzerPin, melody_frequency [soundstep], melody_duration [soundstep]);
            if(melody_frequency [soundstep]==0){/*noTone(buzzerPin);*/digitalWrite(buzzerPin, LOW);}
          }else{
            ResetSound();
          } 
        } 
    break;
  }
}

void ResetSound(){
  //Serial.println("reset sound");
  soundstep=0;
  playingSound = 0;
  SoundState=0;

}
