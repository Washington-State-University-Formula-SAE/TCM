// upshift
bool can_upshift()
{
  return (UpButtonState != UpButtonReading && UpButtonReading == 1 && ShiftOccurance < 5 && ShiftOccurance !=-1);
}
void upshift()
{
  UpButtonState = UpButtonReading;
  ShiftOccurance = ShiftOccurance + 1;
  
  ShiftStall = millis();
  UpShiftStallTimer = millis() - ShiftStall;
  
  while(UpShiftSwitchState == 0 && UpShiftStallTimer < ShiftStallWait)
  {
    digitalWrite(UpShiftOutput, LOW);
    UpShiftSwitchState = digitalRead(UpShiftSwitch);
    UpShiftStallTimer = millis() - ShiftStall;
  }
  
  digitalWrite(UpShiftOutput, HIGH);
}

// downshift
bool can_downshift()
{
  bool result = false;
  // ...
  if(DownButtonState != DownButtonReading && DownButtonReading == 1 && ShiftOccurance > 0) 
  {
    // ...
  }
  else if(DownButtonState != DownButtonReading && DownButtonReading == 0) 
  {
    DownButtonState = DownButtonReading;
  }
  return result;
}
void downshift()
{
  DownButtonState = DownButtonReading;
  ShiftOccurance = ShiftOccurance - 1;

  ShiftStall = millis();
  DownShiftStallTimer = millis() - ShiftStall;
  
  while(DownShiftSwitchState == 0 && DownShiftStallTimer < ShiftStallWait)
  {
    digitalWrite(DownShiftOutput, LOW);
    DownShiftSwitchState = digitalRead(DownShiftSwitch);
    DownShiftStallTimer = millis() - ShiftStall;
  }
  
  digitalWrite(DownShiftOutput, HIGH);
}

// neutral shift
bool can neutralshift()
{
  return (UpButtonState != UpButtonReading && UpButtonReading == 1 && ShiftOccurance < 0);
}
void neutralshift()
{
  UpButtonState = UpButtonReading;
  ShiftOccurance = ShiftOccurance + 1;
  
  ShiftStall = millis();
  DownShiftStallTimer = millis() - ShiftStall;
  
  while(DownShiftSwitchState == 0 && DownShiftStallTimer < ShiftStallWait)
  {
    digitalWrite(DownShiftOutput, LOW);
    DownShiftSwitchState = digitalRead(DownShiftSwitch);
    DownShiftStallTimer = millis() - ShiftStall;
  }
  digitalWrite(DownShiftOutput, HIGH);
}
