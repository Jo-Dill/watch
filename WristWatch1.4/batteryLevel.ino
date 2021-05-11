byte batteryshown=0;
void batteryLevel (){
  const int maxMeasurement=1005; //experimentel ermittelt
  const int minMeasurement=900;
  if(batteryshown==0){
    batteryshown=1;
    digitalWrite(batteryreaderOutPin, HIGH);
    delay(20);
    int measurement=0;
    measurement = analogRead(batteryreaderInPin);
    //for(int i=0; i<=100; i++){measurement += analogRead(batteryreaderInPin); measurement=measurement/2; }
    if(measurement>maxMeasurement){measurement=maxMeasurement;}
    if(measurement<minMeasurement){measurement=minMeasurement;}
    byte lastLED = map(measurement,minMeasurement,maxMeasurement,0,NUMPIXELS);
    //Serial.print("analogRead(batteryreaderInPin) :");Serial.println(measurement);
    pixels.clear();
    
    byte r=0; byte g=1; byte b=0;
    if(lastLED<=2){r=1;g=0;b=0;}
    for (int i=0;i<lastLED;i++){pixels.setPixelColor((i), pixels.Color((r*70),(g*70),(b*70))); delay(100);pixels.show();}
    delay(100);
    pixels.setPixelColor(lastLED, pixels.Color((r*255),(g*255),(b*255)));
    pixels.show();
    digitalWrite(batteryreaderOutPin, LOW);
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
           runningProg=0; batteryLevelReset(); resetbuttons();
        }
      if(upButton== 1 && downButton == 0 && upButtonrelease ==0 && downButtonrelease ==0){ //just up pressed and released
           batteryshown=0; resetbuttons();
        }
    
}
void batteryLevelReset(){
  batteryshown=0;
}

void batteryLevelSetup(){
  
  analogReference(AR_INTERNAL1V0); //change the reference from default:external to 2.23V:internal
  for (int i =0; i<10; i++){analogRead (batteryreaderInPin);} // read something a couple of time so that the reference gets set up
  for (int i =0; i<10; i++){analogRead (lightsensorInPin  );}
}
