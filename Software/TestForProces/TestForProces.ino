char incomingByte;
 int ledPin = 8; // Set the pin to digital I/O 13

 void setup() {
   pinMode(ledPin, OUTPUT); // Set pin as OUTPUT
   Serial.begin(9600); // Start serial communication at 9600 bps
 }


 void loop() {
   if (Serial.available()) 
   { // If data is available to read,
     incomingByte = Serial.read(); // read it and store it in val
   if (incomingByte == 'L') 
   { // If 1 was received
     digitalWrite(ledPin, HIGH); // turn the LED on
     Serial.print("Links");
   }
   else if (incomingByte == 'R') {
     digitalWrite(ledPin, HIGH); // otherwise turn it off
     Serial.print("Rechts");
   }
   else if (incomingByte =='U'){
    digitalWrite(ledPin, HIGH);
    Serial.print("Vooruit");
   }
   else if(incomingByte == 'D') {
    digitalWrite(ledPin, HIGH);
    Serial.print("Achteruit");
   }
   else {
      digitalWrite(ledPin, LOW);
    }
   delay(10); // Wait 10 milliseconds for next reading
 }
}

