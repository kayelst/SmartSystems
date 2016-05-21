#define rfReceivePin A0
#define ledPin 13

unsigned int data = 0;
const unsigned int upper = 70;
const unsigned int lower = 50;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  data=analogRead(rfReceivePin);    
   
    if(data>upper){
     digitalWrite(ledPin, LOW);
     Serial.println(data);
    }

    if(data<lower){
     digitalWrite(ledPin, HIGH);
     Serial.println(data);
   }
}

  
