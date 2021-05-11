
void pinSetup(){
   pinMode(upbuttonPin , INPUT_PULLUP);
   pinMode(downbuttonPin , INPUT_PULLUP);
   pinMode(batteryreaderOutPin , OUTPUT);
   pinMode(lightsensorVCCPin , OUTPUT);
   pinMode(lightsensorActivatePin , OUTPUT);
   pinMode(ledactivatePin , OUTPUT);         
   pinMode(buzzerPin , OUTPUT);
   Serial.println("pinSetup");
}
