//Libraries Aanspreken
#include <NewPing.h>
#include <Servo.h>
#include "Timer.h"

Servo servoMain;

int ProgramCount = 1;

int DriveCount = 1;
long FrontSensor;
long duration;
long Distance;
int ServoStatus = 20;

Timer t;

//RijINTs aanmaken
int LinksVooruit = 5;
int LinksAchteruit = 4;
int RechtsVooruit = 1;
int RechtsAchteruit = 2;
int EnableRechts = 0;
int EnableLinks = 3;

#include <NewPing.h>
 
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);



void setup() {
  // put your setup code here, to run once:

  pinMode(LinksVooruit, OUTPUT);
  pinMode(LinksAchteruit, OUTPUT); 
  pinMode(RechtsVooruit, OUTPUT);
  pinMode(RechtsAchteruit, OUTPUT);
  pinMode(EnableLinks, OUTPUT);
  pinMode(EnableRechts, OUTPUT);
  //zorg ervoor dat seriële communicatie enabled is voor de input.
  Serial.begin(115200);

  servoMain.attach(9);

  int tickEvent = t.every(2000,ChangeServo);
}

void loop() {
  // put your main code here, to run repeatedly:
  MeasureDistance(1);
  Serial.print("FrontSensor is ");
  Serial.println(FrontSensor);
  DistanceCheck(1);
  Execute();
}

void ChangeServo()
{
    if(ServoStatus == 20){
    servoMain.write(80);
    ServoStatus = 80;
    Serial.print("ServoStatus is ");
    Serial.print(ServoStatus);
  }
  else if(ServoStatus == 80){
    servoMain.write(20);
    ServoStatus = 20;
    Serial.print("ServoStatus is ");
    Serial.print(ServoStatus);
  }
  Serial.print("2 second tick: millis()=");
  Serial.println(millis());
}

void Execute(){
 switch(ProgramCount){
  case 1:
    servoMain.write(20);
    Serial.println(ProgramCount);
    Vooruit();
    break;
  case 2:
  Serial.println(ProgramCount);
    Vooruit();
    t.update();
    Serial.println("Updated Timer");
    Serial.print("millis()");
    Serial.println(millis());
    break;
  case 3:
    servoMain.write(20);
    Serial.println(ProgramCount);
    Serial.println("Zigzaglijn");
    DriveZigzag();
    break;
  case 4:
    Serial.println("Gestipte ZigZagLijn");
    DriveCount = 0;
    DriveZigzag();
    Serial.println(ProgramCount);
    Serial.println("Updated Timer");
    Serial.print("millis()");
    Serial.println(millis());
    break;    
 }
}

void DriveZigzag(){
    if (DriveCount < 1){
  do { 
  Drive (1,0);
  delay(250);
  MeasureDistance(1);
  DistanceCheck(1);
  Serial.print("FrontSensor is ");
  Serial.println(FrontSensor);
  Vooruit();
  if(ProgramCount == 4){
      t.update(); 
  }
  delay(1000);
  MeasureDistance(1);
  DistanceCheck(1);
  Serial.print("FrontSensor is ");
  Serial.println(FrontSensor);
  Drive (0,1);
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
  Serial.print("FrontSensor is ");
  Serial.println(FrontSensor);
  delay(1000);
  DriveCount++;
  MeasureDistance(1);
  DistanceCheck(1);
  Serial.print("FrontSensor is ");
  Serial.println(FrontSensor);
  } while(ProgramCount == 3 || ProgramCount == 4);
  }
  else {
    do{ 
    Drive (1,0);
    delay(750);
   MeasureDistance(1);
   DistanceCheck(1);
   Serial.print("FrontSensor is ");
   Serial.println(FrontSensor);
    Vooruit();
    if(ProgramCount == 4){
      t.update(); 
    }
    delay(1000);
    MeasureDistance(1);
    DistanceCheck(1);
    Serial.print("FrontSensor is ");
    Serial.println(FrontSensor);  
    Drive (0,1);
    if(ProgramCount == 4){
      t.update(); 
    }
    delay(750);
      MeasureDistance(1);
    DistanceCheck(1);
    Serial.print("FrontSensor is ");
    Serial.println(FrontSensor);
    Vooruit();
    servoMain.write(80);
    if(ProgramCount == 4){
      t.update(); 
    }
    delay(1000);
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
}

void DistanceCheck(int DelayVal){
  if(FrontSensor <= 15 && FrontSensor != 0){
    DraaiRechts(1500);
    Serial.println("Turn!");
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
  Drive(-1, 1);
  delay(delayVal);
}


