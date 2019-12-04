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

void setup() 
{
  pinMode(ClutchButton, INPUT);
  pinMode(DownShiftButton, INPUT);
  pinMode(UpShiftButton, INPUT);
  pinMode(AuxButton, INPUT);

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

void loop() 
{

}

void upshift()
{

}
void downshift()
{

}

bool can_upshift()
{

}
bool can_downshift()
{

}

int get_rpm()
{

}
int get_gear()
{

}