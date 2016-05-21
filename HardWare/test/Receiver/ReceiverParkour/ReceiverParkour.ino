#include <VirtualWire.h>

int pin_left_E1 = 2;
int pin_left_I1 = 3;
int pin_left_I2 = 4; //Gebruikte poorten

int pin_right_E1 = 7;
int pin_right_I1 = 6;
int pin_right_I2 = 5;

int receive_pin = 8;

void setup()
{
  Serial.begin(9600);
  Serial.println("I'm alive!");
  
  pinMode(pin_left_E1, OUTPUT);
  pinMode(pin_left_I1, OUTPUT);
  pinMode(pin_left_I2, OUTPUT); //Zet de poorten als output
  
  pinMode(pin_right_E1, OUTPUT);
  pinMode(pin_right_I1, OUTPUT);
  pinMode(pin_right_I2, OUTPUT);
  
  vw_set_rx_pin(receive_pin); //Stel recieve pin/bitrate in en start communicatie
  vw_setup(1200);

  vw_rx_start();
}

void loop()
{
  Forward(750);
  Stop(500);
  TurnRight(1000);
  Stop(500);
  TurnLeft(1000);
  Stop(500);
  Backward(750);
  Stop(3000);
}

void updateMotors(int Mleft, int Mright) //Methode om de motoren aan te zetten adhv. de parameters (1 = vooruit, 0 = stop, -1 = achteruit)
{
  switch(Mleft)
  {
    case 1: digitalWrite(pin_left_E1, HIGH); digitalWrite(pin_left_I1, HIGH); digitalWrite(pin_left_I2, LOW); break;
    case 0: digitalWrite(pin_left_E1, LOW); digitalWrite(pin_left_I1, LOW); digitalWrite(pin_left_I2, LOW); break;
    case -1: digitalWrite(pin_left_E1, HIGH); digitalWrite(pin_left_I1, LOW); digitalWrite(pin_left_I2, HIGH); break;
  }
  
  switch(Mright)
  {
    case 1: digitalWrite(pin_right_E1, HIGH); digitalWrite(pin_right_I1, HIGH); digitalWrite(pin_right_I2, LOW); break;
    case 0: digitalWrite(pin_right_E1, LOW); digitalWrite(pin_right_I1, LOW); digitalWrite(pin_right_I2, LOW); break;
    case -1: digitalWrite(pin_right_E1, HIGH); digitalWrite(pin_right_I1, LOW); digitalWrite(pin_right_I2, HIGH); break;
  } 
}

void TurnRight(int d)
{
  updateMotors(1,-1);
  delay(d);
}

void TurnLeft(int d)
{
  updateMotors(-1,1);
  delay(d);
}

void Forward(int d)
{
  updateMotors(1,1);
  delay(d);
}

void Backward(int d)
{
  updateMotors(-1,-1);
  delay(d);
}

void Stop(int d)
{
  updateMotors(0,0);
  delay(d);
}
