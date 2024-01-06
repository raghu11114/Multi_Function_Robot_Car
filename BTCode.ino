#include<NewPing.h>
#include<Servo.h>
#include<AFMotor.h>
#define RIGHT A3
#define LEFT A2
#define TRIGGER_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 100
#define MAX_SPEED 100  

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


AF_DCMotor Motor1(1,MOTOR12_1KHZ);
AF_DCMotor Motor2(2,MOTOR12_1KHZ);
AF_DCMotor Motor3(3,MOTOR34_1KHZ);
AF_DCMotor Motor4(4,MOTOR34_1KHZ);

Servo myservo;
boolean goesForward=false;
int pos =0;
int distance2=100;
int speedSet=0;
char command; 
int buzzer=A4;
void setup() 
{       
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
  myservo.attach(10);
  myservo.attach(10);  
  myservo.write(100); 
  delay(2000);
  distance2 = readPing();
  delay(100);
  distance2 = readPing();
  delay(100);
  distance2 = readPing();
  delay(100);
  distance2 = readPing();
  delay(100);
{
for(pos = 90; pos <= 180; pos += 1){
  myservo.write(pos);
  delay(15);
} for(pos = 180; pos >= 0; pos-= 1) {
  myservo.write(pos);
  delay(15);
}for(pos = 0; pos<=90; pos += 1) {
  myservo.write(pos);
  delay(15);
}
}
pinMode(RIGHT, INPUT);
pinMode(LEFT, INPUT);

}

void loop(){
  if(Serial.available() > 0){ 
    command = Serial.read(); 
    Stop(); //initialize with motors stoped
    //Change pin mode only if new command is different from previous.   
    //Serial.println(command);
    switch(command){
    case 'F':  
      forward();
      break;
    case 'B':  
       back();
      break;
    case 'L':  
      left();
      break;
    case 'R':
      right();
      break;
    case 'S':
      Stop();
      break;
    case 'H':
     human();  
      break;
    case 'O':
      obstacle();
      break;
    }
  } 
}

void forward()
{
  Motor1.setSpeed(100); //Define maximum velocity
  Motor1.run(FORWARD); //rotate the motor clockwise
  Motor2.setSpeed(100); //Define maximum velocity
  Motor2.run(FORWARD); //rotate the motor clockwise
  Motor3.setSpeed(100);//Define maximum velocity
  Motor3.run(FORWARD); //rotate the motor clockwise
  Motor4.setSpeed(100);//Define maximum velocity
  Motor4.run(FORWARD); //rotate the motor clockwise
  Serial.println("BT Forward");
}

void back()
{
  Motor1.setSpeed(100); //Define maximum velocity
  Motor1.run(BACKWARD); //rotate the motor anti-clockwise
  Motor2.setSpeed(100); //Define maximum velocity
  Motor2.run(BACKWARD); //rotate the motor anti-clockwise
  Motor3.setSpeed(100); //Define maximum velocity
  Motor3.run(BACKWARD); //rotate the motor anti-clockwise
  Motor4.setSpeed(100); //Define maximum velocity
  Motor4.run(BACKWARD); //rotate the motor anti-clockwise
  Serial.println("BT Backward");
}

void left()
{
  Motor1.setSpeed(100); //Define maximum velocity
  Motor1.run(BACKWARD); //rotate the motor anti-clockwise
  Motor2.setSpeed(100); //Define maximum velocity
  Motor2.run(BACKWARD); //rotate the motor anti-clockwise
  Motor3.setSpeed(100); //Define maximum velocity
  Motor3.run(FORWARD);  //rotate the motor clockwise
  Motor4.setSpeed(100); //Define maximum velocity
  Motor4.run(FORWARD);  //rotate the motor clockwise
  Serial.println("BT Left");
}

void right()
{
  Motor1.setSpeed(100); //Define maximum velocity
  Motor1.run(FORWARD); //rotate the motor clockwise
  Motor2.setSpeed(100); //Define maximum velocity
  Motor2.run(FORWARD); //rotate the motor clockwise
  Motor3.setSpeed(100); //Define maximum velocity
  Motor3.run(BACKWARD); //rotate the motor anti-clockwise
  Motor4.setSpeed(100); //Define maximum velocity
  Motor4.run(BACKWARD); //rotate the motor anti-clockwise
  Serial.println("BT Right");
} 

void Stop()
{
  Motor1.setSpeed(0); //Define minimum velocity
  Motor1.run(RELEASE); //stop the motor when release the button
  Motor2.setSpeed(0); //Define minimum velocity
  Motor2.run(RELEASE); //rotate the motor clockwise
  Motor3.setSpeed(0); //Define minimum velocity
  Motor3.run(RELEASE); //stop the motor when release the button
  Motor4.setSpeed(0); //Define minimum velocity
  Motor4.run(RELEASE); //stop the motor when release the button
  Serial.println("Stopped");
}
void human(){
  //int i=1;
  while(1){
  delay(1);
 unsigned int distance = sonar.ping_cm();
Serial.println("Human Follower Mode");
Serial.print("distance");
Serial.println(distance);


int Right_Value = digitalRead(RIGHT);
int Left_Value = digitalRead(LEFT);

Serial.print("RIGHT");
Serial.println(Right_Value);
Serial.print("LEFT");
Serial.println(Left_Value);
Serial.print("before if");
if((Right_Value==1) && distance>=10 && distance<=30 &&(Left_Value==1)){
  Serial.print("in if block");
  Motor1.setSpeed(100);
  Motor1.run(FORWARD);
  Motor2.setSpeed(100);
  Motor2.run(FORWARD);
  Motor3.setSpeed(100);
  Motor3.run(FORWARD);
  Motor4.setSpeed(100);
  Motor4.run(FORWARD);
}
else if((Right_Value==0) && (Left_Value==1)) {
  Serial.print("right block");
  Motor1.setSpeed(100);
  Motor1.run(FORWARD);
  Motor2.setSpeed(100);
  Motor2.run(FORWARD);
  Motor3.setSpeed(100);
  Motor3.run(BACKWARD);
  Motor4.setSpeed(100);
  Motor4.run(BACKWARD);
}
else if((Right_Value==1)&&(Left_Value==0)) {
  Serial.print("left block");
  Motor1.setSpeed(100);
  Motor1.run(BACKWARD);
  Motor2.setSpeed(100);
  Motor2.run(BACKWARD);
  Motor3.setSpeed(100);
  Motor3.run(FORWARD);
  Motor4.setSpeed(100);
  Motor4.run(FORWARD);
}
else if((Right_Value==1)&&(Left_Value==1)) {
  Serial.print("stop block");
  Motor1.setSpeed(0);
  Motor1.run(RELEASE);
  Motor2.setSpeed(0);
  Motor2.run(RELEASE);
  Motor3.setSpeed(0);
  Motor3.run(RELEASE);
  Motor4.setSpeed(0);
  Motor4.run(RELEASE);
}
else if(distance > 1 && distance < 10) {
  Serial.print("less distance block");
  Motor1.setSpeed(0);
  Motor1.run(RELEASE);
  Motor2.setSpeed(0);
  Motor2.run(RELEASE);
  Motor3.setSpeed(0);
  Motor3.run(RELEASE);
  Motor4.setSpeed(0);
  Motor4.run(RELEASE);
  }
  else {
    Serial.print("in else block");
  }

  command = Serial.read(); 
  if(command=='S'){
    break;
  }
  }
 }
 void obstacle(){
   int distanceR = 0;
 int distanceL =  0;
 delay(40);
 Serial.println("Obstacle Mode");
 while(1){
 if(distance2<=35)
 {
  moveStop();
  delay(100);
  {
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
  }
        
  moveBackward();
  delay(300);
        
       
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }else
  {
    turnLeft();
    moveStop();
  }
 }else
 {
  moveForward();
 }
 distance2 = readPing();
 command = Serial.read(); 
  if(command=='S'){
    break;
  }
 }
 }

int lookRight()
{
    myservo.write(30); 
    delay(1000);
    int distance = readPing();
    delay(100);
    myservo.write(100); 
    return distance;
}

int lookLeft()
{
    myservo.write(180); 
    delay(1000);
    int distance = readPing();
    delay(100);
    myservo.write(100); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  Motor1.run(RELEASE); 
  Motor2.run(RELEASE);
  Motor3.run(RELEASE);
  Motor4.run(RELEASE);
  
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    Motor1.run(FORWARD);      
    Motor2.run(FORWARD);
    Motor3.run(FORWARD); 
    Motor4.run(FORWARD);     
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    Motor1.setSpeed(speedSet);
    Motor2.setSpeed(speedSet);
    Motor3.setSpeed(speedSet);
    Motor4.setSpeed(speedSet);
    delay(5);
   }
  }
}


void moveBackward() {
    goesForward=false;
    Motor1.run(BACKWARD);      
    Motor2.run(BACKWARD);
    Motor3.run(BACKWARD);
    Motor4.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    Motor1.setSpeed(speedSet);
    Motor2.setSpeed(speedSet);
    Motor3.setSpeed(speedSet);
    Motor4.setSpeed(speedSet);
    delay(5);
  }
}  


void turnRight() {
  Motor1.run(FORWARD);
  Motor2.run(FORWARD);
  Motor3.run(BACKWARD);
  Motor4.run(BACKWARD);     
  delay(500);
  Motor1.run(FORWARD);      
  Motor2.run(FORWARD);
  Motor3.run(FORWARD);
  Motor4.run(FORWARD);      
} 
 
void turnLeft() {
  Motor1.run(BACKWARD);     
  Motor2.run(BACKWARD);  
  Motor3.run(FORWARD);
  Motor4.run(FORWARD);   
  delay(500);
  Motor1.run(FORWARD);     
  Motor2.run(FORWARD);
  Motor3.run(FORWARD);
  Motor4.run(FORWARD);
}
