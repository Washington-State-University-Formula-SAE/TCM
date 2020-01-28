bool upshift_button_engaged()
{
  return digitalRead(UpShiftButton);;
}
bool downshift_button_engaged()
{
  return digitalRead(DownShiftButton);
}
bool clutch_paddle_engaged()
{
  return digitalRead(ClutchButton);
}
bool neutral_button_engaged()
{
  return digitalRead(AuxButton);
}

int mode_selection_switch()
{
  // get value
  int mode_value = 0;
 
  // parse value and translate to 0, 1, 2, etc.
  // ...

  // if we can't read the switch, then default to mode 0
  // ...
  
  // return value
  return mode_value;
}
