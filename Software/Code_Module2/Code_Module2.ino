//Libraries Aanspreken
#include <NewPing.h>
#include <Servo.h>
 
#define SONAR_NUM  3 // Number or sensors.
#define MAX_DISTANCE 500 // Max distance in cm.
#define PING_INTERVAL 500 // Milliseconds between pings.

Servo servoMain;

//RijINTs aanmaken
int LinksVooruit =11;
int LinksAchteruit = 12;
int RechtsVooruit = 5;
int RechtsAchteruit = 6;
int EnableRechts = 4;
int EnableLinks = 13;

int ProgramCount = 1;
int DriveCount = 0;
int Status = 1;

//Sonarints aanmaken
unsigned long pingTimer[SONAR_NUM]; // When each pings.
unsigned int cm[SONAR_NUM]; // Store ping distances.
uint8_t currentSensor = 0; // Which sensor is active.
long RightSensor;
long LeftSensor;
long FrontSensor;
long duration;
long Distance;
const int trigPin3 = 3;
const int echoPin2 = 4;
const int echoPin1 = 2;
const int echoPin3 = 6;

 
NewPing sonar[SONAR_NUM] = { // Sensor object array.
  NewPing(3, 2, MAX_DISTANCE),
  NewPing(3, 6, MAX_DISTANCE),
  NewPing(3, 4, MAX_DISTANCE)
};

void setup() {
  // put your setup code here, to run once:
  
  //setup motors
  pinMode(LinksVooruit, OUTPUT);
  pinMode(LinksAchteruit, OUTPUT); 
  pinMode(RechtsVooruit, OUTPUT);
  pinMode(RechtsAchteruit, OUTPUT);
  pinMode(EnableLinks, OUTPUT);
  pinMode(EnableRechts, OUTPUT);
  
  //setup Sensors 
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  
  //zorg ervoor dat seriële communicatie enabled is voor de input.
  Serial.begin(9600);
  servoMain.attach(8);

  pingTimer[0] = millis() + 75; // First ping start in ms.
  for (uint8_t i = 1; i < SONAR_NUM; i++)
  pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
}

void loop() {
  // put your main code here, to run repeatedly:
  
  /*MeasureDistance(500);
  Serial.print("LeftSensor is ");
  Serial.println(LeftSensor);
  Serial.print("FrontSensor is ");
  Serial.println(FrontSensor);
  Serial.print("RightSensor is ");
  Serial.println(RightSensor);
  Serial.println(" ");
  
  DistanceCheck(500);*/
  Execute();
}

void MeasureDistance(int DelayVal){

      for (uint8_t i = 0; i < SONAR_NUM; i++) {
        if (millis() >= pingTimer[i]) {
          pingTimer[i] += PING_INTERVAL * SONAR_NUM;
          if (i == 0 && currentSensor == SONAR_NUM - 1){
            oneSensorCycle(); // Do something with results.
          }
          sonar[currentSensor].timer_stop();
          currentSensor = i;
          cm[currentSensor] = 0;
          sonar[currentSensor].ping_timer(echoCheck);
      } 
    }
}

void DistanceCheck(int DelayVal){
  if(FrontSensor <= 15 || LeftSensor <= 19 || RightSensor <= 19){
    if (ProgramCount < 4){
      ProgramCount++;
    }
    else{
      ProgramCount = 1;
    }
    DraaiRechts(1500);
    Serial.println("Running Next Program");
    Serial.println("Turn!");
  }
  else
  Vooruit();
}

void echoCheck() { // If ping echo, set distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}
 
void oneSensorCycle() { // Do something with the results.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    Serial.print(i);
    Serial.print("=");
    Serial.print(cm[i]);
    Serial.print("cm ");

    switch (i){
      case 0:
      FrontSensor = cm[i];
      Serial.print("FrontSensor is ");
      Serial.println(FrontSensor);
      break;
      case 1:
      LeftSensor = cm[i];
      Serial.print("LeftSensor is ");
      Serial.println(LeftSensor);
      break;
      case 2:
      RightSensor = cm[i];
      Serial.print("RightSensor is ");
      Serial.println(RightSensor);
      break;
    }
    /*cm[0]= FrontSensor;
    cm[1] = LeftSensor;
    cm[2] = RightSensor;*/
  }
  Serial.println();
}

void Execute(){
  switch(ProgramCount){
    case 1:
      Serial.println("Volle Lijn");
      DriveCount = 0;
      //servoStatus(1);
      Vooruit();
      MeasureDistance(500);
      DistanceCheck(500);
      break;
    case 2:
      Serial.println("Stippellijn");
      //servoStatus(2);
      Vooruit();
      MeasureDistance(500);
      DistanceCheck(500);
      break;
    case 3:
      Serial.println("Zigzaglijn");
      DriveZigzag();
      //servoStatus(1);
      break;
    case 4:
      Serial.println("Gestipte ZigZagLijn");
      DriveCount = 0;
      DriveZigzag();
      //servoStatus(2);
      break;
  }
}

/* Not Needed for first Test
 * void servoStatus(int Status){
  switch(Status){
    case 1:
      servoMain.write(180);
      break;
    case 2:
      //while(Status == 2){
      servoMain.write(90);
      Serial.println("servo UP");
      //delay(5000);
      servoMain.write(180);
      Serial.println("servo down");
      //delay(5000);
      //}   
  }
}*/

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

/*void CheckSchakelaar()
{
}*/

void Vooruit()
{
  Drive(1,1);
}

void DraaiRechts(int delayVal)
{
  Drive(-1, 1);
  delay(delayVal);
  Stop(1000);
}

void DraaiLinks(int delayVal)
{
  Drive(1, -1);
  delay(delayVal);
  Stop(1000);
}

void DriveZigzag(){
  if (DriveCount < 1){
  do { 
  Drive (1,-1);
  delay(250);
  Vooruit();
  delay(1000);
  Drive (-1,1);
  delay(750);
  Vooruit();
  delay(1000);
  DriveCount++;
  MeasureDistance(500);
  DistanceCheck(500);
  } while(ProgramCount == 3 || ProgramCount == 4);
  }
  else {
    do{ 
    Drive (1,-1);
    delay(750);
    Vooruit();
    delay(2000);
    Drive (-1,1);
    delay(750);
    Vooruit();
    delay(2000);
    DriveCount++;
    MeasureDistance(500);
    DistanceCheck(500);
    } while( ProgramCount == 3 || ProgramCount == 4);
  }
}
void Stop(int delayVal)
{
  Drive(0,0);
  delay(delayVal); 
}


