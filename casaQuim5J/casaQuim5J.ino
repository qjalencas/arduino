#include <Servo.h>

const int buttonPin = 2; 
const int ledPin1 = 13;  
const int ledPin2 = 12; 
const int ledPin3 = 11; 
const int ledPin4 = 10; 
const int ledPin5 = 9;  


int buttonState = 0;         
int lastButtonState = 0;   
int ledState1 = LOW;         

Servo servoMotor;

unsigned long milli1;

const int trigPin = 6;
const int echoPin = 7;
long duration, distance;


bool isDoorOpen = false;
bool handDetected = false;

void setup() {
  
  Serial.begin(9600);
  
  servoMotor.attach(8);
    
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servoMotor.write(0);
  milli1 = millis();

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT); 
  pinMode(ledPin4, OUTPUT); 
  pinMode(ledPin5, OUTPUT); 

  pinMode(buttonPin, INPUT);

  digitalWrite(ledPin1, ledState1);
  digitalWrite(ledPin2, ledState1);
  digitalWrite(ledPin3, ledState1);
  digitalWrite(ledPin4, ledState1);
  digitalWrite(ledPin5, ledState1);
}

void loop() {
  if (millis() - milli1 >= 1000) {

  milli1 = millis();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= 10) {
    if (!handDetected) {
      handDetected = true;

      if (isDoorOpen) {
        servoMotor.write(0);
        isDoorOpen = false;
        Serial.println("Porta tancada");
        
      }
      else {

        servoMotor.write(90);
        isDoorOpen = true;
        Serial.println("Pora oberta");
        
      }
    }
    }
    else {
      handDetected = false;
    }
  }
 
 buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    lastButtonState = buttonState;

    if (buttonState == HIGH) {
      ledState1 = !ledState1;
      digitalWrite(ledPin1, ledState1);
      digitalWrite(ledPin2, ledState1);
      digitalWrite(ledPin3, ledState1);
      digitalWrite(ledPin4, ledState1);
      digitalWrite(ledPin5, ledState1);
        
      delay (25);
    }
  }
}

    
