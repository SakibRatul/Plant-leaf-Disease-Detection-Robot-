#include <Servo.h>
Servo Myservo;
#define trigPin 9  // Trig Pin Of HC-SR04
#define echoPin 8  // Echo Pin Of HC-SR04
#define MLa 4      //left motor 1st pin
#define MLb 5      //left motor 2nd pin
#define MRa 6      //right motor 1st pin
#define MRb 7      //right motor 2nd pin
#define en1 3
#define en2 11
long duration, distance;


void setup() {
  Serial.begin(9600);
  pinMode(MLa, OUTPUT);  // Set Motor Pins As O/P
  pinMode(MLb, OUTPUT);
  pinMode(MRa, OUTPUT);
  pinMode(MRb, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(trigPin, OUTPUT);  // Set Trig Pin As O/P To Transmit Waves
  pinMode(echoPin, INPUT);   //Set Echo Pin As I/P To Receive Reflected Waves
  analogWrite(en1, 100);
  analogWrite(en2, 100);
}
void loop() {
  Serial.begin(9600);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  // Transmit Waves For 10us
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH);  // Receive Reflected Waves
  distance = duration / 58.2;         // Get Distance
  Serial.println(distance);
  delay(10);
  digitalWrite(MRb, HIGH);  // Move Forward
  digitalWrite(MRa, LOW);
  digitalWrite(MLb, HIGH);
  digitalWrite(MLa, LOW);
}
