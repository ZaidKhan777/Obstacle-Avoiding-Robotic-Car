#include <Servo.h>
Servo myservo;
#include <Ultrasonic.h>
Ultrasonic ultrasonic(12, 13);
int turning_distance = 20;
int obstacle_distance;
int angle = 90;
int turning_status = 0;
int forward_pin1 = 1;
int backward_pin1 = 2;
int forward_pin2 = 3;
int backward_pin2 = 4;

void setup() {
  pinMode(forward_pin1, OUTPUT);
  pinMode(forward_pin2, OUTPUT);
  pinMode(backward_pin1, OUTPUT);
  pinMode(backward_pin2, OUTPUT);
  myservo.attach(9);
}

void loop() {
  if (obstacle_distance > turning_distance) {
    stop();
    go_backward();
    delay(200);
    stop();
    for (angle = 90; angle >= 0; angle--) {
      myservo.write(angle);
    }
    distance_reader();
    if (obstacle_distance > turning_distance) {
      turning_status = 1;
    }

    for (angle = 0; angle <= 180; angle++) {
      myservo.write(angle);
    }
    distance_reader();
    if (obstacle_distance > turning_distance) {
      turning_status = 0;
    }

    for (angle = 180; angle >= 90; angle--) {
      myservo.write(angle);
    }

    if (turning_status == 1) {
      go_right();
      dealy(500);    
    } else {
      go_left();
      delay(500);
    }
  } else {
    go_forward();
  }
}

void stop() {
  digitalWrite(forward_pin1, LOW);
  digitalWrite(backward_pin1, LOW);
  digitalWrite(forward_pin2, LOW);
  digitalWrite(backward_pin2, LOW);
}

void go_forward() {
  digitalWrite(forward_pin1, HIGH);
  digitalWrite(forward_pin2, HIGH);
  digitalWrite(backward_pin1, LOW);
  digitalWrite(backward_pin2, LOW);
}

void go_backward() {
  digitalWrite(forward_pin1, LOW);
  digitalWrite(forward_pin2, LOW);
  digitalWrite(backward_pin1, HIGH);
  digitalWrite(backward_pin2, HIGH);
}

void go_right() {
  digitalWrite(forward_pin1, HIGH);
  digitalWrite(backward_pin1, LOW);
  digitalWrite(backward_pin2, HIGH);
  digitalWrite(forward_pin2, LOW);
}

void go_left() {
  digitalWrite(forward_pin1, LOW);
  digitalWrite(backward_pin1, HIGH);
  digitalWrite(backward_pin2, LOW);
  digitalWrite(forward_pin2, HIGH);
}

void distance_reader() {
  obstacle_distance = ultrasonic.read();
}
