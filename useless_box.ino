

// This is the sketch used for the 'useless_box' project.
// Have a look at the project on GitHub: github.com/DanielBaur/useless_box
// Modify the utilized pins under 'user definitions'.
// Add your own animations under 'useless profiles'.





// --------------------------------------------------
// imports
// --------------------------------------------------


#include <Servo.h>





// --------------------------------------------------
// user definitions
// --------------------------------------------------


int switch_pin = 2; // digital pin for toggle switch, digital, no PWM required (uno default: 2, Arduino Nano default: D2, which is referenced by 2)
int servo_lid_pin = 10; // PWM (Arduino UNO default: 10, Arduino Nano default: D10, which is referenced by 10)
int servo_switch_pin = 9; // PWM (Arduino UNO default: 9, Arduino Nano default: D9, which is referenced by 9)
int led_pin = 16; // choose the pin for the LED (Arduino Nano: 16)





// --------------------------------------------------
// definitions
// --------------------------------------------------


// general
int switch_val; // digital button signal (either HIGH or LOW)


// lid servo
Servo servo_lid; // erstellt ein Servo-Objekt um einen Servomotor zu steuern
int servo_lid_startpos = 180;
int servo_lid_endpos = 90;


// switch servo
Servo servo_switch; // erstellt ein Servo-Objekt um einen Servomotor zu steuern
int servo_switch_startpos = 180;
int servo_switch_midpos = 90;
int servo_switch_beforealmostendpos = 35;
int servo_switch_almostendpos = 15;
int servo_switch_endpos = 0;


// controlling the servos
void move_servo_to(Servo controlservo, int endpos, float time_s) {
  //void move_servo_to(int endpos, int time_s){
  //int currentpos = controlservo.read();
  int currentpos = controlservo.read();
  int stepsize_servo = 1;
  float steps_required = abs(endpos - currentpos)/stepsize_servo;
  float stepsize_ms = (1000 * time_s) / steps_required;
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


// standard
void useless_action_1() {
  delay(1500);
  move_servo_to(servo_lid, servo_lid_endpos, 0.5);
  delay(1500);
  move_servo_to(servo_switch, servo_switch_endpos, 1);
  delay(2000);
  move_servo_to(servo_switch, servo_switch_startpos, 1);
  delay(500);
  move_servo_to(servo_lid, servo_switch_startpos, 1);
  delay(1000);
}


// stopping midway, toggling switch, returning
void useless_action_2() {
  delay(1000);
  move_servo_to(servo_lid, servo_lid_endpos, 1);
  delay(1500);
  move_servo_to(servo_switch, servo_switch_midpos, 0.5);
  delay(2000);
  move_servo_to(servo_switch, servo_switch_endpos, 0.5);
  delay(500);
  move_servo_to(servo_switch, servo_switch_startpos, 0.5);
  delay(500);
  move_servo_to(servo_lid, servo_switch_startpos, 1);
  delay(1000);
}


// dribbling, switching off, returning
void useless_action_3() {
  delay(1000);
  move_servo_to(servo_lid, servo_lid_endpos, 0.25);
  delay(500);
  move_servo_to(servo_switch, servo_switch_almostendpos, 0.25); // 15
  delay(40);
  move_servo_to(servo_switch, servo_switch_beforealmostendpos, 0.25); // 35
  delay(40);
  move_servo_to(servo_switch, servo_switch_almostendpos, 0.25);
  delay(40);
  move_servo_to(servo_switch, servo_switch_beforealmostendpos, 0.25);
  delay(40);
  move_servo_to(servo_switch, servo_switch_almostendpos, 0.25);
  delay(40);
  move_servo_to(servo_switch, servo_switch_beforealmostendpos, 0.25);
  delay(40);
  move_servo_to(servo_switch, servo_switch_endpos, 0.15);
  delay(500);
  move_servo_to(servo_switch, servo_switch_startpos, 0.25);
  delay(500);
  move_servo_to(servo_lid, servo_switch_startpos, 1);
  delay(1000);
}


// switching off and returning
void useless_action_4() {
  delay(1000);
  move_servo_to(servo_lid, servo_lid_endpos, 0.25);
  delay(100);
  move_servo_to(servo_switch, servo_switch_endpos, 0.45);
  delay(40);
  move_servo_to(servo_switch, servo_switch_startpos, 0.45);
  delay(40);
  move_servo_to(servo_lid, servo_lid_startpos, 0.25);
  delay(1200);
  move_servo_to(servo_lid, servo_lid_endpos, 0.25);
  delay(40);
  move_servo_to(servo_switch, servo_switch_midpos, 0.25);
  delay(40);
  move_servo_to(servo_switch, servo_switch_startpos, 0.25);
  delay(40);
  move_servo_to(servo_lid, servo_lid_startpos, 0.25);
  delay(1000);
}


// trying but failing, retrying and returning
void useless_action_5() {
  delay(1000);
  move_servo_to(servo_lid, servo_lid_endpos, 0.25);
  delay(100);
  move_servo_to(servo_switch, servo_switch_almostendpos, 0.25);
  delay(40);
  move_servo_to(servo_switch, servo_switch_startpos, 0.45);
  delay(1200);
  move_servo_to(servo_switch, servo_switch_almostendpos, 0.75);
  delay(250);
  move_servo_to(servo_switch, servo_switch_endpos, 0.15);
  delay(40);
  move_servo_to(servo_switch, servo_switch_startpos, 0.45);
  delay(40);
  move_servo_to(servo_lid, servo_lid_startpos, 0.25);
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
      digitalWrite(led_pin, HIGH);
      useless_action_5();
    }
    else if (random_useless_action == 2) {
      digitalWrite(led_pin, HIGH);
      useless_action_2();
    }
    else if (random_useless_action == 3) {
      digitalWrite(led_pin, HIGH);
      useless_action_3();
    }
    else if (random_useless_action == 4) {
      digitalWrite(led_pin, HIGH);
      useless_action_4();
    }
    else if (random_useless_action == 5) {
      digitalWrite(led_pin, HIGH);
      useless_action_5();
    }
  }
}
