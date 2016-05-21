#include <VirtualWire.h>

const int transmit_pin = 4;

void setup()
{
  Serial.begin(9600);
  Serial.println("I'm alive!");
  
  vw_set_tx_pin(transmit_pin); //Transmit pin instellen en versturen
  vw_setup(2000);

  vw_rx_start();
}

char *message = "s"; //Default message = stop

void loop()
{
  
  if (Serial.available() > 0) //Als er een bericht is ontvangen via de seriele poort, dat bericht versturen naar de auto
  {
    Serial.print("Sent: ");
    *message = Serial.read();
    Serial.println(message);
    
    vw_send((uint8_t *)message, 1);
    vw_wait_tx(); // Wachten tot versturing compleet is
  }
}

