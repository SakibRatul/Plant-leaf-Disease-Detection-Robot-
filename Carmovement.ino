
#include <NewPing.h>

#define TRIGGER_PIN_F   4 // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN_F      2 // Arduino pin tied to echo pin on ping sensor.
#define TRIGGER_PIN_R     13
#define ECHO_PIN_R       12
#define MAX_DISTANCE 150 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define RIGHT_FORWARD 9
#define RIGHT_REVERSE 10
#define LEFT_FORWARD 5
#define LEFT_REVERSE 6

NewPing sonar_f(TRIGGER_PIN_F, ECHO_PIN_F, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar_r(TRIGGER_PIN_R, ECHO_PIN_R, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

unsigned int pingSpeed = 50; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
unsigned long pingTimer;     // Holds the next ping time.
float dist_f;
float dist_r;
int speed = 100;
int thresh = 40;
bool movingForward = false;
bool movingReverse = false;
void setup() {
  Serial.begin(19200); // Open serial monitor at 115200 baud to see ping results.
  pingTimer = millis(); // Start now.
}

void loop() {
  // Notice how there's no delays in this sketch to allow you to do other processing in-line while doing distance pings.
  if (millis() >= pingTimer) {   // pingSpeed milliseconds since last ping, do another ping.
    pingTimer += pingSpeed;      // Set the next ping time.
    sonar_f.ping_timer(echoCheck); // Send out the ping, calls "echoCheck" function every 24uS where you can check the ping status.
    sonar_r.ping_timer(echoCheck);
  }
  // Do other stuff here, really. Think of it as multi-tasking.
}
float forward(int speed, int dly=40){
  //movingForward = true;
  //movingReverse = false;
  for(int i=0; i< speed; i+= 20){
    analogWrite(RIGHT_FORWARD, i);
    analogWrite(LEFT_FORWARD, i);
    analogWrite(RIGHT_REVERSE, 0);
    analogWrite(LEFT_REVERSE, 0);
    delay(dly);
  }
}
float reverse(int speed, int dly=40){
  //movingForward = false;
  //movingReverse = true;
  for(int i=0; i< speed; i+= 20){
    analogWrite(RIGHT_FORWARD, 0);
    analogWrite(LEFT_FORWARD, 0);
    analogWrite(RIGHT_REVERSE, i);
    analogWrite(LEFT_REVERSE, i);
    delay(dly);
  }
}
float pause(){
  analogWrite(RIGHT_FORWARD, 0);
  analogWrite(LEFT_FORWARD, 0);
  analogWrite(RIGHT_REVERSE, 0);
  analogWrite(LEFT_REVERSE, 0);
  //movingForward = false;
  //movingReverse = false;
}
void echoCheck() { // Timer2 interrupt calls this function every 24uS where you can check the ping status.
  // Don't do anything here!
  if (sonar_f.check_timer() && sonar_r.check_timer()) { // This is how you check to see if the ping was received.
    // Here's where you can add code.
    dist_f = sonar_f.ping_result / US_ROUNDTRIP_CM;
    dist_r = sonar_r.ping_result / US_ROUNDTRIP_CM;
    if(dist_f > 60){
      Serial.println("moving forward");
      forward(speed);
    }
    else if(dist_r > 60){
      Serial.println("moving reverse");
      reverse(speed);

    }
    else{
      Serial.println("pausing");
      pause();
    }
    Serial.print("Ping front: ");Serial.print(dist_f);  Serial.print("cm  "); // Ping returned, uS result in ping_result, convert to cm with US_ROUNDTRIP_CM.
    Serial.print("Ping rear: ");Serial.print(dist_r);  Serial.println("cm"); 
  }
  // Don't do anything here!
}