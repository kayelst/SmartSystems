#include <VirtualWire.h>

const int receive_pin = 8;

void setup()
{
  Serial.begin(9600);
  Serial.println("I'm alive!");
  
  vw_set_rx_pin(receive_pin); //Stel recieve pin/bitrate in en start communicatie
  vw_setup(9600);

  vw_rx_start();
}

void loop()
{
  
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  //Serial.println(buflen);
  //Serial.println(vw_have_message());
  
  if (vw_get_message(buf, &buflen)) //Ontvanging bericht
  {
    int i;
    Serial.print("Got: "); //
  	
    for (i = 0; i < buflen; i++)
    {
      Serial.print(buf[i]);
      Serial.print(' ');
    }
    Serial.println();
  }
}

