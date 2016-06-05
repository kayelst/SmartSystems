//Libraries Aanspreken
#include <NewPing.h>
#include <Servo.h>
#include "Timer.h"

Servo Servo1;

int ProgramCount = 1;

int DriveCount = 1;
long FrontSensor;
long RightSensor;
long LeftSensor;
int ServoStatus = 20;

Timer t;

//RijINTs aanmaken
int LinksVooruit = 1;
int LinksAchteruit = 2;
int RechtsVooruit = 5;
int RechtsAchteruit = 4;
int EnableRechts = 3;
int EnableLinks = 0;
 
#define TRIGGER_PIN  12
#define TRIGGER_PIN2 13
#define TRIGGER_PIN3 7
#define ECHO_PIN2    10
#define ECHO_PIN     11
#define ECHO_PIN3    6
#define MAX_DISTANCE 200
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE);


void setup() {
  // put your setup code here, to run once:

  pinMode(LinksVooruit, OUTPUT);
  pinMode(LinksAchteruit, OUTPUT); 
  pinMode(RechtsVooruit, OUTPUT);
  pinMode(RechtsAchteruit, OUTPUT);
  pinMode(EnableLinks, OUTPUT);
  pinMode(EnableRechts, OUTPUT);

  Servo1.attach(19);

  int tickEvent = t.every(500,ChangeServo);
}

void loop() {
  // put your main code here, to run repeatedly:
  MeasureDistance(1);
  DistanceCheck(1);
  Execute();
}

void ChangeServo()
{
    if(ServoStatus == 20){
    Servo1.write(80);
    ServoStatus = 80;
  }
  else if(ServoStatus == 80){
    Servo1.write(20);
    ServoStatus = 20;
  }
}

void Execute(){
 switch(ProgramCount){
  case 1:
    Servo1.write(20);
    Vooruit();
    break;
  case 2:
    Vooruit();
    t.update();
    break;
  case 3:
    Servo1.write(20);
    DriveZigzag();
    break;
  case 4:
    DriveCount = 0;
    DriveZigzag();
    break;    
 }
}

void DriveZigzag(){
    if (DriveCount == 0){
  do { 
  Drive (-1,1);
  delay(250);
  MeasureDistance(1);
  DistanceCheck(1);
  Vooruit();
  if(ProgramCount == 4){
      t.update(); 
  }
  delay(300);
  MeasureDistance(1);
  DistanceCheck(1);
  Drive (1,-1);
  if(ProgramCount == 4){
      t.update(); 
  }
  delay(750);
  Vooruit();
  if(ProgramCount == 4){
      t.update(); 
  }
  MeasureDistance(1);
  DistanceCheck(1);
  delay(300);
  DriveCount++;
  MeasureDistance(1);
  DistanceCheck(1);
  } while(ProgramCount == 3 || ProgramCount == 4);
  }
  else {
    do{ 
    Drive (-1,1);
    delay(750);
   MeasureDistance(1);
   DistanceCheck(1);
    Vooruit();
    if(ProgramCount == 4){
      t.update(); 
    }
    delay(300);
    MeasureDistance(1);
    DistanceCheck(1);  
    Drive (1,-1);
    if(ProgramCount == 4){
      t.update(); 
    }
    delay(750);
    MeasureDistance(1);
    DistanceCheck(1);
    Vooruit();
    if(ProgramCount == 4){
      t.update(); 
    }
    delay(300);
    DriveCount++;
    MeasureDistance(1);
    DistanceCheck(1);
    if(ProgramCount == 4){
      t.update(); 
    }
    } while(ProgramCount == 3 ||ProgramCount == 4);
  }  
  
}

void MeasureDistance(int DelayVal){
  delay(50);
  int uS = sonar.ping();
  FrontSensor = uS / US_ROUNDTRIP_CM;
  int ping2 = sonar2.ping();
  RightSensor = ping2 / US_ROUNDTRIP_CM;
  int ping3 = sonar3.ping();
  LeftSensor = ping3 / US_ROUNDTRIP_CM;
}
void DistanceCheck(int DelayVal){
  if(FrontSensor <= 10 && FrontSensor != 0 || RightSensor <= 12 && RightSensor != 0 || LeftSensor <= 12 && LeftSensor != 0){
    DraaiRechts(1500);
    if (ProgramCount < 4){
     ProgramCount++;
    }
    else
    ProgramCount = 1;
  }
  else
  Vooruit();
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
 }
}

void Vooruit()
{
  Drive(1,1);
}

void DraaiRechts(int delayVal)
{
  Servo1.write(80);
  Drive(-1, 1);
  delay(delayVal);
}


