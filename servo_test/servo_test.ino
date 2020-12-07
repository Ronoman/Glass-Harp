#include <Servo.h>

Servo s;

void setup() {
  // put your setup code here, to run once:
  s.attach(2);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  s.writeMicroseconds(map(analogRead(A0), 0, 1023, 450, 2000));
  Serial.println(map(analogRead(A0), 0, 1023, 450, 2000));
}
