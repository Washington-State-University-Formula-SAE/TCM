// Define Paddle Inputs
int ClutchButton = 8;
int DownShiftButton = 5;
int UpShiftButton = 7;
int NeutralButton = 9;

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
int IgnCut = A2;

// Define Waits
int ShiftDelay = 50;
int ShiftStallWait = 600;

// Define Shift Tracking Perameters
int CurrentGear = 0;

// Define Timers
int ShiftStall = 0;
int UpShiftStallTimer = 0;
int DownShiftStallTimer = 0;

// Define Initial Input States
int ClutchButtonState = 0;
int DownButtonState = 0;
int UpButtonState = 0;
int NeutralButtonState = 0;
int NeutralButtonState = 0;

int UpShiftSwitchState = 0;
int NeutralShiftSwitchState = 0;
int DownShiftSwitchState = 0;

int ClutchButtonReading = 0;
int DownButtonReading = 0;
int UpButtonReading = 0;
int NeutralButtonReading = 0;
int NeutralButtonReading = 0;

void setup()
{
  pinMode(ClutchButton, INPUT);
  pinMode(DownShiftButton, INPUT);
  pinMode(UpShiftButton, INPUT);
  pinMode(NeutralButton, INPUT);
  // pinMode(NeutralButton, INPUT);

  pinMode(UpShiftSwitch, INPUT);
  pinMode(DownShiftSwitch, INPUT);

  digitalWrite(ClutchOutput, HIGH);
  digitalWrite(DownShiftOutput, HIGH);
  digitalWrite(UpShiftOutput, HIGH);

  pinMode(ClutchOutput, OUTPUT);
  pinMode(DownShiftOutput, OUTPUT);
  pinMode(UpShiftOutput, OUTPUT);

  Serial.begin(9600);

  // startup sequence
  if (mode_selection_switch() != 0)
  {
    int start_result = 1;
    while(start_result == 1 && mode_selection_switch() != 0)
    {
      start_result = start();
    }
  }
}

void loop() 
{
  // update sensor info
  int drivemode = mode_selection_switch();

  // do stuff
  switch (drivemode)
  {
    case 0:
    mode_zero(); // no babysitting mode
    break;

    case 1:
    mode_one(); // a little bit of babysitting mode
    break;

    case 2:
    mode_two(); // a lot of babysitting mode
    break;

    default: // driving mode is not recognized (not 0, 1, or 2)
    mode_one(); // default to mode 1
    break;
  }
  print_stuff();
}

void print_stuff()
{
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
  Serial.print(NeutralButtonState);
  Serial.print(",");
  Serial.print("Up Shift Sensor State:");
  Serial.println(UpShiftSwitchState);
  Serial.print(",");
  Serial.print("Down Shift Sensor State:");
  Serial.print(DownShiftSwitchState);
}

void other_random_stuff_i_dont_know_what_to_do_with()
{
  // Maintain Solenoids in Off, Piston-Neutral State
  else 
  {
    digitalWrite(DownShiftOutput, HIGH);
    digitalWrite(UpShiftOutput, HIGH);
  }

  // Neutral Shift Sequence
  if(NeutralButtonState != NeutralButtonReading && NeutralButtonReading == 1 && ClutchButtonReading == 1) 
  {
    NeutralButtonState = NeutralButtonReading;

    if(CurrentGear == 0) 
    {
      digitalWrite(UpShiftOutput, LOW);
      delay(40);
      digitalWrite(UpShiftOutput, HIGH);
      CurrentGear = -1;
    }
    
    if(CurrentGear == 1)
    {
      digitalWrite(DownShiftOutput, LOW);
      delay(40);
      digitalWrite(DownShiftOutput, HIGH);
      CurrentGear = -1;
    }
  }
  else if (NeutralButtonState != NeutralButtonReading && NeutralButtonReading == 0) {
    NeutralButtonState = NeutralButtonReading;
  }

  // neutral indicator
  if(CurrentGear == -1)
  {
    digitalWrite(NeutralIndicator, HIGH);
  }
  else 
  {
    digitalWrite(NeutralIndicator, LOW);
  }
}
