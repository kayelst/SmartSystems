//Libraries Aanspreken
#include <VirtualWire.h>

//180 draaien = DraaiRechts(1500);

//INTS aanmaken
int LinksVooruit =1;
int LinksAchteruit = 2;
int RechtsVooruit = 4;
int RechtsAchteruit = 5;
int EnableRechts = 3;
int EnableLinks = 0;
int Work = false;

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
  Vooruit(3000);
  DraaiRechts(3000);
  DraaiLinks(3000);
  Achteruit(3000);
  Stop(3000);
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
   //links wiel achteruit
   case -1:
    digitalWrite(EnableLinks, HIGH);
    digitalWrite(LinksVooruit, LOW);
    digitalWrite(LinksAchteruit, HIGH);
    break;
   /*default:
    digitalWrite(EnableLinks, LOW);
    digitalWrite(LinksVooruit, LOW);
    digitalWrite(LinksAchteruit, LOW);
    break;*/ 
 }
 switch(RightWheel)
 {
    //Rechts wiel vooruit
    case 1:
    digitalWrite(EnableRechts, HIGH);
    digitalWrite(RechtsVooruit, HIGH);
    digitalWrite(RechtsAchteruit, LOW);
    break;
    //Rechts wiel remt
  case 0:
    digitalWrite(EnableRechts, LOW);
    digitalWrite(RechtsVooruit, LOW);
    digitalWrite(RechtsAchteruit, LOW);
   break;
   //Rechts wiel gaat achteruit
   case -1:
    digitalWrite(EnableRechts, HIGH);
    digitalWrite(RechtsVooruit, LOW);
    digitalWrite(RechtsAchteruit, HIGH);
    break;
  /* default:
    digitalWrite(EnableRechts, LOW);
    digitalWrite(RechtsVooruit, LOW);
    digitalWrite(RechtsAchteruit, LOW);
    break;*/ 
 }
}

/*void CheckSchakelaar()
{
}*/

void Vooruit(int delayVal)
{
   Serial.println("Vooruit");
  Drive(1,1);
  delay(delayVal);
  Stop(0);
}

void DraaiRechts(int delayVal)
{
    Serial.println("Rechts");
  Drive(-1, 1);
  delay(delayVal);
  Stop(1000);
}

void DraaiLinks(int delayVal)
{
    Serial.println("Links");
  Drive(1, -1);
  delay(delayVal);
  Stop(1000);
}

void Achteruit(int delayVal)
{
    Serial.println("Achteruit");
  Drive(-1, -1);
  delay(delayVal);
  Stop(1000);
}

void Stop(int delayVal)
{
  Drive(0,0);
  delay(delayVal); 
}


