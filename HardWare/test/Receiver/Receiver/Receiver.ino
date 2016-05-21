#include <VirtualWire.h>

int pin_left_E1 = 2;
int pin_left_I1 = 3;
int pin_left_I2 = 4; //Gebruikte poorten

int pin_right_E1 = 5;
int pin_right_I1 = 6;
int pin_right_I2 = 7;

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
  vw_setup(9600);

  vw_rx_start();
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) //Ontvanging bericht
  {
    int i;
    Serial.print("Got: "); //
  	
    for (i = 0; i < buflen; i++)
    {
      switch(buf[i]) //
      {
        case 'f': Forward(); break; 
        case 'b': Backward(); break;
        case 'l': TurnLeft(); break;
        case 'r': TurnRight(); break; 
        case 's': Stop(); break;
      }
      Serial.print(buf[i]);
      Serial.print(' ');
    }
    Serial.println();
  }
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

void TurnRight()
{
  updateMotors(1,-1);
}

void TurnLeft()
{
  updateMotors(-1,1);
}

void Forward()
{
  updateMotors(1,1);
}

void Backward()
{
  updateMotors(-1,-1);
}

void Stop()
{
  updateMotors(0,0);
}
