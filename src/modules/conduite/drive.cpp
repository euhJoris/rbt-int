#include <Arduino.h>

// Define pins 
#define ENA 9 //speed controller for right motor
#define IN1 10 //for left motor
#define IN2 11 //for left motor

#define ENB 3 //speed controller for right motor
#define IN3 12 //for right motor
#define IN4 13 //for right motor

#define FORWARD_BTN 1
#define BACKWARD_BTN 21
#define LEFT_BTN 19
#define RIGHT_BTN 18

bool active = false;

void intialize_motors_ports(){
    Serial.println("Intialisation des ports pour la direction ...");
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(FORWARD_BTN, INPUT_PULLUP);
    pinMode(BACKWARD_BTN, INPUT_PULLUP);
    pinMode(LEFT_BTN, INPUT_PULLUP);
    pinMode(RIGHT_BTN, INPUT_PULLUP);
    Serial.println("Fin d'initialisation des ports pour la direction ...");

    // Turn off motors - Initial state
	digitalWrite(IN1, LOW);
	digitalWrite(IN2, LOW);
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, LOW);
}

void speedControl(int motors_speed) {
	// For PWM maximum possible values are 0 to 255
    if(motors_speed >= 0 && motors_speed <= 256) { 
        analogWrite(ENA, motors_speed);
        analogWrite(ENB, motors_speed);
        active = true;
    } else {
        Serial.println("Invalid speed value. Please enter a value between 0 and 255.");
        return;
    }
}

void directionControl() {
    while(active){
        if (digitalRead(FORWARD_BTN) == LOW){
            // Turn on motor A & B and move on
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
        }else {
            // Stop moving
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, LOW);
        }

        if (digitalRead(BACKWARD_BTN) == LOW){
            // Turn on motor A & B and back up
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);
        }else {
            // Stop moving
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, LOW);
        }
    }
}