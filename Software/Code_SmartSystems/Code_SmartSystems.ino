//Libraries Aanspreken
#include <VirtualWire.h>

//INTS aanmaken
int LinksVooruit =11;
int LinksAchteruit = 12;
int RechtsVooruit = 5;
int RechtsAchteruit = 6;
int EnableRechts = 4;
int EnableLinks = 13;
int Work = false;
bool FirstDelay = true;

void setup() {
  // put your setup code here, to run once:
  //Zet alle pins als Output
  pinMode(LinksVooruit, OUTPUT);
  pinMode(LinksAchteruit, OUTPUT); 
  pinMode(RechtsVooruit, OUTPUT);
  pinMode(RechtsAchteruit, OUTPUT);
  pinMode(EnableLinks, OUTPUT);
  pinMode(EnableRechts, OUTPUT);
  //zorg ervoor dat seriële communicatie enabled is voor de input.
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   //FIRST TEST
   if(FirstDelay = true){
    Stop(5000);
    FirstDelay = false;
   }
  Vooruit(3000);
  DraaiRechts(3000);
  DraaiLinks(3000);
  Achteruit(3000);
  Stop(10000);
}

void Drive(int LeftWheel, int RightWheel)
{
 switch(LeftWheel)
 {
  //links wiel vooruit
  case 1:
    digitalWrite(EnableLinks, HIGH);
    digitalWrite(LinksVooruit, HIGH);
    digitalWrite(LinksAchteruit, LOW);
    break;
    //links wiel remt
  case 0:
    digitalWrite(EnableLinks, LOW);
    digitalWrite(LinksVooruit, LOW);
    digitalWrite(LinksAchteruit, LOW);
   break;
   case -1:
    digitalWrite(EnableLinks, HIGH);
    digitalWrite(LinksVooruit, LOW);
    digitalWrite(LinksAchteruit, HIGH);
    break;
 }
 switch(RightWheel)
 {
    case 1:
    digitalWrite(EnableRechts, HIGH);
    digitalWrite(RechtsVooruit, HIGH);
    digitalWrite(RechtsAchteruit, LOW);
    break;
    //links wiel remt
  case 0:
    digitalWrite(EnableRechts, LOW);
    digitalWrite(RechtsVooruit, LOW);
    digitalWrite(RechtsAchteruit, LOW);
   break;
   case -1:
    digitalWrite(EnableRechts, HIGH);
    digitalWrite(RechtsVooruit, LOW);
    digitalWrite(RechtsAchteruit, HIGH);
    break;
 }
}

/*void CheckSchakelaar()
{
}*/

void Vooruit(int delayVal)
{
  Drive(1,1);
  delay(delayVal);
  Stop(2000);
}

void DraaiRechts(int delayVal)
{
  Drive(-1, 1);
  delay(delayVal);
  Stop(2000);
}

void DraaiLinks(int delayVal)
{
  Drive(1, -1);
  delay(delayVal);
  Stop(2000);
}

void Achteruit(int delayVal)
{
  Drive(-1,-1);
  delay(delayVal);
  Stop(2000);
}

void Stop(int delayVal)
{
  Drive(0,0);
  delay(delayVal); 
}


