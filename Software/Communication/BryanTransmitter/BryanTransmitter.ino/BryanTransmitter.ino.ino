  #include <VirtualWire.h>
 
  void setup() {
    Serial.begin(9600);
    vw_set_ptt_inverted(true);
    vw_setup(2000);
    vw_set_tx_pin(4);
  }
 
  void loop() {
     sendMessage("1", "5");
     delay(10000);
  }
 
  void sendMessage(char* pinCode, char *data) {
     if (strlen(data) > 0) {
      //double startTime = millis(); 
      //Serial.println("Sending...");
      int msgSize = (strlen(data) + strlen(pinCode) + 1);
      char packetData[msgSize];
      strcat(packetData, pinCode);
      strcat(packetData, ".");
      strcat(packetData, data);
 
      //Serial.println("Debugging ");
      //Serial.print("Sending Command: ");
      //Serial.print(data);
      //Serial.print(" with Pin Code: ");
      //Serial.print(pinCode);
      //Serial.print("\n");
 
      vw_send((uint8_t *)packetData, msgSize);
      vw_wait_tx();
 
      //double endTime = millis();
      //double timeTaken = (endTime - startTime); 
      //Serial.print("Time Taken: ");
      //Serial.print(timeTaken);
      //Serial.print(" ms\n");
    }  
  }
