// Define Paddle Inputs
int ClutchButton = 8;
int DownShiftButton = 5;
int UpShiftButton = 7;
int AuxButton = 9;
//int NeutralButton = A1;

// Define Shift Completion Inputs
int UpShiftSwitch = 10;
//int NeutralSwitch = 11 ;
int DownShiftSwitch = 11;

// Define Auxillary Sensor Outputs
int NeutralIndicator = A1;
int SignalLight = A0;


// Define Shift Control Outputs
int ClutchOutput = 2;
int DownShiftOutput = 4;
int UpShiftOutput = 3;
int IgnCut = 5;

// Define Waits
int ShiftDelay = 50;
int ShiftStallWait = 500;

// Define Shift Tracking Perameters
float ShiftOccurance = 0;
int CurrentGear = 0;

// Define Timers
int ShiftStall = 0;
int UpShiftStallTimer = 0;
int DownShiftStallTimer = 0;

// Define Initial Input States
int ClutchButtonState = 0;
int DownButtonState = 0;
int UpButtonState = 0;
int AuxButtonState = 0;
int NeutralButtonState = 0;

int UpShiftSwitchState = 0;
int NeutralShiftSwitchState = 0;
int DownShiftSwitchState = 0;

int ClutchButtonReading = 0;
int DownButtonReading = 0;
int UpButtonReading = 0;
int AuxButtonReading = 0;
int NeutralButtonReading = 0;

// Define Counting Variables
  int startupcounter = 1;


// Initialize Program
void setup() {

  pinMode(ClutchButton, INPUT);
  pinMode(DownShiftButton, INPUT);
  pinMode(UpShiftButton, INPUT);
  pinMode(AuxButton, INPUT);
//  pinMode(NeutralButton, INPUT);

  pinMode(UpShiftSwitch, INPUT);
  pinMode(DownShiftSwitch, INPUT);

  digitalWrite(ClutchOutput, HIGH);
  digitalWrite(DownShiftOutput, HIGH);
  digitalWrite(UpShiftOutput, HIGH);

  pinMode(ClutchOutput, OUTPUT);
  pinMode(DownShiftOutput, OUTPUT);
  pinMode(UpShiftOutput, OUTPUT);

  Serial.begin(9600);
}


// Control Loop
void loop() {

  ClutchButtonReading = digitalRead(ClutchButton);
  DownButtonReading = digitalRead(DownShiftButton);
  UpButtonReading = digitalRead(UpShiftButton);
  AuxButtonReading = digitalRead(AuxButton);
  // NeutralButtonReading = digitalRead(NeutralButton);

  UpShiftSwitchState = digitalRead(UpShiftSwitch);
  DownShiftSwitchState = digitalRead(DownShiftSwitch);

//Startup Sequence
  while(startupcounter == 1){

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
  }

// Pneumatic Clutch Control
    if(ClutchButtonState != ClutchButtonReading && ClutchButtonReading == 1) {
      ClutchButtonState = ClutchButtonReading;
      digitalWrite(ClutchOutput, LOW);
    }

    else if (ClutchButtonState != ClutchButtonReading && ClutchButtonReading == 0) {
      ClutchButtonState = ClutchButtonReading;
      digitalWrite(ClutchOutput, HIGH);
    }

// Aux Button Functionality
//    if(AuxButtonState != AuxButtonReading && AuxButtonReading == 1) {
//      AuxButtonState = AuxButtonReading;
//    }
//
//    else if (AuxButtonState != AuxButtonReading && AuxButtonReading == 0) {
//      AuxButtonState = AuxButtonReading;
//    }

// Complete a Downshift
    if(DownButtonState != DownButtonReading && DownButtonReading == 1 && ShiftOccurance > 0) {
      DownButtonState = DownButtonReading;
      ShiftOccurance = ShiftOccurance - 1;

      ShiftStall = millis();
      DownShiftStallTimer = millis() - ShiftStall;
      
      while(DownShiftSwitchState == 0 && DownShiftStallTimer < ShiftStallWait){
      digitalWrite(DownShiftOutput, LOW);
      DownShiftSwitchState = digitalRead(DownShiftSwitch);
      DownShiftStallTimer = millis() - ShiftStall;
      }
      digitalWrite(DownShiftOutput, HIGH);
    }
    else if(DownButtonState != DownButtonReading && DownButtonReading == 0) {
      DownButtonState = DownButtonReading;
    }

// Complete an Upshift
    if(UpButtonState != UpButtonReading && UpButtonReading == 1 && ShiftOccurance < 5 && ShiftOccurance !=-1) {
      UpButtonState = UpButtonReading;
      ShiftOccurance = ShiftOccurance + 1;
      
      ShiftStall = millis();
      UpShiftStallTimer = millis() - ShiftStall;
      
      while(UpShiftSwitchState == 0 && UpShiftStallTimer < ShiftStallWait){
      digitalWrite(UpShiftOutput, LOW);
      UpShiftSwitchState = digitalRead(UpShiftSwitch);
      UpShiftStallTimer = millis() - ShiftStall;
      }
      digitalWrite(UpShiftOutput, HIGH);
    }

// Shift Out of Neutral
    else if(UpButtonState != UpButtonReading && UpButtonReading == 1 && ShiftOccurance < 0) {
      UpButtonState = UpButtonReading;
      ShiftOccurance = ShiftOccurance + 1;
      
      ShiftStall = millis();
      DownShiftStallTimer = millis() - ShiftStall;
      
      while(DownShiftSwitchState == 0 && DownShiftStallTimer < ShiftStallWait){
      digitalWrite(DownShiftOutput, LOW);
      DownShiftSwitchState = digitalRead(DownShiftSwitch);
      DownShiftStallTimer = millis() - ShiftStall;
      }
      digitalWrite(DownShiftOutput, HIGH);
    }
    
    else if(UpButtonState != UpButtonReading && UpButtonReading == 0) {
      UpButtonState = UpButtonReading;
    }

// Maintain Solenoids in Off, Piston-Neutral State
    else {
      digitalWrite(DownShiftOutput, HIGH);
      digitalWrite(UpShiftOutput, HIGH);
    }

// Neutral Shift Sequence
    if(AuxButtonState != AuxButtonReading && AuxButtonReading == 1 && ClutchButtonReading == 1) {
      AuxButtonState = AuxButtonReading;

      if(ShiftOccurance == 0){
        digitalWrite(UpShiftOutput, LOW);
        delay(100);
        digitalWrite(UpShiftOutput, HIGH);
        ShiftOccurance = -1;
      }
      
      if(ShiftOccurance == 1){
        digitalWrite(DownShiftOutput, LOW);
        delay(100);
        digitalWrite(DownShiftOutput, HIGH);
        ShiftOccurance = -1;
      }
    }
    else if (AuxButtonState != AuxButtonReading && AuxButtonReading == 0) {
      AuxButtonState = AuxButtonReading;
    }

//Neutral Indicator
  if(ShiftOccurance == -1){
    digitalWrite(NeutralIndicator, HIGH);
  }
  else {
    digitalWrite(NeutralIndicator, LOW);
  }
  
// Calibrate Gear Tracking
    CurrentGear = ShiftOccurance;

// Output Gear and Button Status to Serial
    Serial.print("Current Gear:");
    Serial.print(CurrentGear+1);
    Serial.print(",");
    Serial.print("Clutch Button State:");
    Serial.print(ClutchButtonState);
    Serial.print(",");
    Serial.print("Upshift Button State:");
    Serial.print(UpButtonState);
    Serial.print(",");
    Serial.print("Downshift Button State:");
    Serial.print(DownButtonState);
    Serial.print(",");
    Serial.print("Aux Button State:");
    Serial.print(AuxButtonState);
    Serial.print(",");
    Serial.print("Up Shift Sensor State:");
    Serial.println(UpShiftSwitchState);
    Serial.print(",");
    Serial.print("Down Shift Sensor State:");
    Serial.print(DownShiftSwitchState);
}