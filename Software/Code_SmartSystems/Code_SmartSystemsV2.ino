//Libraries Aanspreken
#include <VirtualWire.h>

//INTS aanmaken
int LinksVooruit = 10;
int LinksAchteruit = 9;
int RechtsVooruit = 12;
int RechtsAchteruit = 13;

void setup() {
  // put your setup code here, to run once:
  //Zet alle pins als Output
  pinMode(LinksVooruit, OUTPUT);
  pinMode(LinksAchteruit, OUTPUT); 
  pinMode(RechtsVooruit, OUTPUT);
  pinMode(RechtsAchteruit, OUTPUT);
  //zorg ervoor dat seriële communicatie enabled is voor de input.
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) 
  {
    char KeyboardInput = Serial.read();
    if(KeyboardInput == '8')
    {
      Serial.println("Auto rijd Vooruit");
      Vooruit();
    }
    else if (KeyboardInput == '4')
    {
      Serial.println("Auto rijd links");
      DraaiLinks();
    }
    else if (KeyboardInput == '2')
    {
      Serial.println("Auto rijd achteruit");
      Achteruit();
    }
    else if (KeyboardInput = '6')
    {
      Serial.println("Auto draait naar rechts");
      DraaiRechts();
    }
    else
    {
      Serial.println("Auto stopt");
      Stop();
    }
  }

  /* FIRST TEST
  Vooruit();
  DraaiRechts();
  DraaiLinks();
  Achteruit();
  Stop();
  */
}

void Vooruit()
{
  //Zowel links en rechts gaan rijden => Auto rijd vooruit
 digitalWrite(RechtsVooruit, HIGH);
 digitalWrite(LinksVooruit, HIGH);
 delay(3000); //Gedurende 3 seconen

 /* FIRST TEST
 //Links en Rechts gaan stilstaan zodat de auto stilstaat
 digitalWrite(RechtsVooruit, LOW);
 digitalWrite(LinksVooruit, LOW);
 delay(3000); //Gedurende 3 seconden*/
}

void DraaiRechts()
{
 //Links gaat rijden en Rechts gaat stilstaan waardoor de auto naar rechts draait
 digitalWrite(RechtsVooruit, LOW);
 digitalWrite(LinksVooruit, HIGH);
 delay(5000); //gedurende 5 seconden 

/* FIRST TEST
 //Links en Rechts gaan stilstaan zodat de auto stilstaat
 digitalWrite(RechtsVooruit, LOW);
 digitalWrite(LinksVooruit, LOW);
 delay(3000); //gedurende 3 seconden*/
}

void DraaiLinks()
{
  //Links gaat stilstaan en de rechtse motor gaat draaien waardoor de auto naar links afdraait
  digitalWrite(RechtsVooruit, HIGH);
  digitalWrite(LinksVooruit, LOW);
  delay(5000); //Gedurende 5 seconden

/* FIRST TEST
  //Links en Rechts gaan stilstaan zodat de auto stilstaat
 digitalWrite(RechtsVooruit, LOW);
 digitalWrite(LinksVooruit, LOW);
 delay(3000); //gedurende 3 seconden*/
}

void Achteruit()
{
  //links en rechts gaan beiden naar achter draaien zodat de auto naar achter rijd.
  digitalWrite(RechtsAchteruit, HIGH);
  digitalWrite(LinksAchteruit, HIGH);
  delay(3000); //gedurende 3 sec

  /*FIRST TEST
  //Links en Rechts gaan stilstaan zodat de auto stilstaat
  digitalWrite(RechtsVooruit, LOW);
  digitalWrite(LinksVooruit, LOW);
  delay(3000); //gedurende 3 seconden*/
}

void Stop()
{
  //Links en Rechts gaan stilstaan zodat de auto stilstaat
  digitalWrite(RechtsVooruit, LOW);
  digitalWrite(LinksVooruit, LOW);
  delay(3000); //gedurende 3 seconden

   //Links en Rechts gaan stilstaan zodat de auto stilstaat
  digitalWrite(RechtsAchteruit, LOW);
  digitalWrite(LinksAchteruit, LOW);
  delay(3000); //gedurende 3 seconden
}


