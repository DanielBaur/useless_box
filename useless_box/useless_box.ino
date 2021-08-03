/* Basic Digital Read
   This is the sketch used for the 'useless_box' project, which is dedicated towards the realization of a personal useless box.
   modules:
       - button: https://www.arduino.cc/en/Tutorial/DigitalInputPullup
       - servo:
*/




// --------------------------------------------------
// imports
// --------------------------------------------------

#include <Servo.h>





// --------------------------------------------------
// definitions
// --------------------------------------------------


// general
int switch_pin = 2; // choose the pin for the button signal
int switch_val; // digital button signal (either HIGH or LOW)
int led_pin = 13; // choose the pin for the LED


// lid servo
Servo servo_lid; // erstellt ein Servo-Objekt um einen Servomotor zu steuern
int servo_lid_pin = 10;
int servo_lid_startpos = 180;
int servo_lid_endpos = 90;


// switch servo
Servo servo_switch; // erstellt ein Servo-Objekt um einen Servomotor zu steuern
int servo_switch_pin = 9;
int servo_switch_startpos = 180;
int servo_switch_endpos = 0;


// controlling the servos
void move_servo_to(Servo controlservo, int endpos, int time_s) {
  //void move_servo_to(int endpos, int time_s){
  //int currentpos = controlservo.read();
  int currentpos = controlservo.read();
  int stepsize_servo = 10;
  float stepsize_ms = (1000 * time_s) / (stepsize_servo * abs(endpos - currentpos));
  if (endpos > currentpos) {
    for (int pos = currentpos; pos <= endpos; pos += stepsize_servo) {
      controlservo.write(pos);
      delay(stepsize_ms);
    }
    controlservo.write(endpos);
  }
  else if (endpos < currentpos) {
    for (int pos = currentpos; pos >= endpos; pos -= stepsize_servo) {
      controlservo.write(pos);
      delay(stepsize_ms);
    }
    controlservo.write(endpos);
  }
  else {
    delay(time_s);
  }
  Serial.print("\n\n\n");
}





// --------------------------------------------------
// useless profiles
// --------------------------------------------------


void useless_action_1_standard() {
  delay(1500);
  move_servo_to(servo_lid, servo_lid_endpos, 1);
  delay(1500);
  move_servo_to(servo_switch, servo_switch_endpos, 1);
  delay(2000);
  move_servo_to(servo_switch, servo_switch_startpos, 1);
  delay(500);
  move_servo_to(servo_lid, servo_switch_startpos, 1);
  delay(1000);
}





// --------------------------------------------------
// setup
// --------------------------------------------------


void setup() {
  Serial.begin(9600);
  pinMode(switch_pin, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);
  servo_switch.attach(servo_switch_pin);
  servo_switch.write(servo_switch_startpos);
  servo_lid.attach(servo_lid_pin);
  servo_lid.write(servo_lid_startpos);
}





// --------------------------------------------------
// loop
// --------------------------------------------------


void loop() {

  switch_val = digitalRead(switch_pin);  // read input value

  // switch closed ---> LED off
  if (switch_val == HIGH) {
    digitalWrite(led_pin, LOW);
  }

  // switch open ---> do useless stuff
  else {
    int random_useless_action = random(1,100);
    Serial.print(random_useless_action);

    // animation
    if (random_useless_action == 1) {
      Serial.print("randac: ");
      Serial.print(random_useless_action);
      digitalWrite(led_pin, HIGH);
      useless_action_1_standard();
    }
  }
}
