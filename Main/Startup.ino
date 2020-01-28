bool can_start()
{
  
}

int start()
{
  // pull the clutch in
  // verify that the car is in neutral 
  // let the clutch out
  int startupcounter = 0;
  
  digitalWrite(SignalLight, HIGH);
  
  while(UpButtonReading == 0){
    UpButtonReading = digitalRead(UpShiftButton);
    //wait Until the Upshift button is pressed to continue.
    Serial.println("Entering startup sequence, please press the right paddle to continue.");
  }
  
  delay(500);
  UpButtonReading = 0;
  digitalWrite(ClutchOutput, LOW);
  delay(10);
  while(UpButtonReading == 0){
    UpButtonReading = digitalRead(UpShiftButton);
    //wait Until the Upshift button is pressed to continue.
    Serial.println("Please Confirm in Neutral: Press the right paddle to continue.");
  }
  digitalWrite(ClutchOutput, HIGH);
  delay(10);
  
  Serial.println("Startup Sequence Complete");
  digitalWrite(SignalLight,LOW);
  startupcounter = startupcounter + 1;
  
  delay(1000);
  UpButtonReading = 0;
  ShiftOccurance = -1;
  
  return startupcounter;
}
