#include <Servo.h>

#define SERVO_COUNT 2

Servo *fingers[SERVO_COUNT];

int pins[SERVO_COUNT] = {2, 3};
int positions[SERVO_COUNT] = {1591, 450};

//Add this to positions to move servo away from glass. May need to be negative
const int OFFSET_TO_OFF = -100;

int buttonPin = 10;
int potPin = A0;

void setup() {
    Serial.begin(9600);

    for(int i = 0; i < SERVO_COUNT; i++) {
        Servo *servo = new Servo();
        servo->attach(pins[i]);
        servo->writeMicroseconds(positions[i]);

        fingers[i] = servo;
    }

    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(potPin, INPUT);

    Serial.println("`r` to reset servo position, `p` to play a glass, `s` to stop playing a glass. Follow each letter with 2 numbers: First is module number, second is glass number (0-indexed)");
    Serial.println("For example, `r03` will start reset sequence for module 1 glass 4");
}

void loop() {
    if(Serial.available() > 0) {
        char c = Serial.read();
        delay(10);
        int servoIdx = getServo();
        //Serial.println(servoIdx);

        if(c == 'r') {
            Serial.print("Beginning reset sequence for servo ");
            Serial.print(servoIdx);
            Serial.println();
            Serial.println("Begin moving potentiometer. For finer control, press the button, then move the potentiometer back to the 0 position. To stop, send `s`.");

            int map_out_low = 450;
            int map_out_high = 2000;

            int current_pos = map(analogRead(potPin), 0, 1023, map_out_low, map_out_high);

            while(Serial.read() != 's') {
                if(digitalRead(buttonPin) == 0) {
                    map_out_low = current_pos;
                    map_out_high = map_out_low + 200;

                    Serial.println("Range smaller, move pot to 0...");

                    while(analogRead(potPin) != 0) {
                        delay(100);
                    }

                    Serial.println("Potentiometer at 0, resuming");
                }

                int pot = analogRead(potPin);
                current_pos = map(analogRead(potPin), 0, 1023, map_out_low, map_out_high);

                fingers[servoIdx]->writeMicroseconds(current_pos);
            }

            positions[servoIdx] = current_pos;

            Serial.print("Servo ");
            Serial.print(servoIdx);
            Serial.print(" final position is ");
            Serial.print(current_pos);
            Serial.println();

            Serial.println("Current positions array:");
            printPositions();
        } else if(c == 'p') {
            Serial.print("Playing servo ");
            Serial.print(servoIdx);
            Serial.println();

            fingers[servoIdx]->writeMicroseconds(positions[servoIdx]);
        } else if(c == 's') {
            Serial.print("Stopping servo ");
            Serial.print(servoIdx);
            Serial.println();

            fingers[servoIdx]->writeMicroseconds(positions[servoIdx] + OFFSET_TO_OFF);
        } else {
            Serial.println("`r` to reset servo position, `p` to play a glass, `s` to stop playing a glass");
        }
    }
}

int getServo() {
    if(Serial.available() == 0) {
        return 0;
    }

    int module = Serial.read() - 48;
    //Serial.print("Module ");
    //Serial.print(module);
    //Serial.println();
    delay(10);
    int glass = Serial.read() - 48;
    //Serial.print("Glass ");
    //Serial.print(glass);
    //Serial.println();
    delay(10);

    return 5*module + glass;
}

void printPositions() {
    Serial.print("{");

    for(int i = 0; i < SERVO_COUNT - 1; i++) {
        Serial.print(positions[i]);
        Serial.print(", ");
    }

    Serial.print(positions[SERVO_COUNT - 1]);
    Serial.print("}");
    Serial.println();
}
