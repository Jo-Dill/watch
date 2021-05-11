unsigned long menueTimer = 0;
 
void menue(){
  standbyTime= 5000;
   pixels.clear();
   pixels.setPixelColor(1, pixels.Color((5*brightness),0,0));
   pixels.setPixelColor(2, pixels.Color(0,0,(5*brightness)));
   pixels.show();
   
   if (digitalRead(downbuttonPin)== LOW && downButtonrelease ==0){
     downButtonrelease = 1;
     downButton = 1;
   }
   
   if (digitalRead(upbuttonPin)== LOW && upButtonrelease ==0){
     upButtonrelease = 1;
     upButton = 1;
   }
   
   if(upButton == 1 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //both pressed an released
     runningProg=6; resetbuttons();
   }
    
   if(upButton == 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
     runningProg=4; resetbuttons();
   }

   if(upButton == 0 && downButton == 1 && upButtonrelease ==0 && downButtonrelease ==0){ //just down pressed and released
     runningProg=5; resetbuttons();
   }

    
/*const int menueChangeTime =300;  
if((millis()-menueTimer)> menueChangeTime){
  pixels.clear();
  pixels.setPixelColor(1, pixels.Color((5*brightness),0,0));
  pixels.setPixelColor(2, pixels.Color(0,0,(5*brightness)));
  pixels.show();
}

if((millis()-menueTimer)> (2*menueChangeTime)){
  menueTimer= millis();
  pixels.clear();
  pixels.show();
}
*/
}
