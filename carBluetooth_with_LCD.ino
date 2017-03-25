//This program is used to control a robot car using a app that communicates with Arduino trough a bluetooth module
//The hardware includes an Arduino Uno, a Motor Shield v1, a Bluetooth module, an I2C LCD 1602 screen and an LED on PIN A3
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#include <AFMotor.h>
//creates two objects to control the terminal 3 and 4 of motor shield 
AF_DCMotor motor1(3); 
AF_DCMotor motor2(4); 

const int led =  A3;      // the number of the LED pin
char command; 

void setup() 
{       
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
  pinMode(led, OUTPUT);
  Wire.begin();
  Wire.beginTransmission(0x27);
  int error;
  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);
  lcd.begin(16, 2); // initialize the lcd
  lcd.setBacklight(255);
  lcd.home(); lcd.clear();
  lcd.print("Alejandro's car ");

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
      lcd.setCursor(0, 1);
      lcd.print(" -- FORWARD --- ");
      break;
    case 'B':  
      back();
      lcd.setCursor(0, 1);
      lcd.print(" -- BACKWARD -- ");
      break;
    case 'L':  
      left();
      lcd.setCursor(0, 1);
      lcd.print(" ---  LEFT  --- ");
      break;
    case 'R':
      right();
      lcd.setCursor(0, 1);
      lcd.print(" ---  RIGHT --- ");
      break;
    case 'W':
      digitalWrite(led, HIGH);
      break;
    case 'w':
      digitalWrite(led, LOW);
      break;
    }
  } 
}

void forward()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
}

void back()
{
  motor1.setSpeed(255); 
  motor1.run(BACKWARD); //rotate the motor counterclockwise
  motor2.setSpeed(255); 
  motor2.run(BACKWARD); //rotate the motor counterclockwise
}

void left()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(0);
  motor2.run(RELEASE); //turn motor2 off
}

void right()
{
  motor1.setSpeed(0);
  motor1.run(RELEASE); //turn motor1 off
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
}

void Stop()
{
  motor1.setSpeed(0);
  motor2.run(RELEASE); //turn motor1 off
  motor2.setSpeed(0);
  motor2.run(RELEASE); //turn motor2 off
}


