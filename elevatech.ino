#include <Servo.h>

Servo elevator_servo;
Servo door_servo;

#define C_BUTTON_G 2
#define C_BUTTON_1 3
#define C_BUTTON_2 4

#define L_BUTTON_G 7
#define L_BUTTON_1 6
#define L_BUTTON_2 5

int C_button_state_G = 0;
int C_button_state_1 = 0;
int C_button_state_2 = 0;

int L_button_state_G = 0;
int L_button_state_1 = 0;
int L_button_state_2 = 0;

int target_floor = 0;
int last_floor = 3;

void setup() {
    Serial.begin(9600);
    elevator_servo.attach(9);
    door_servo.attach(10);

    pinMode(C_BUTTON_G, INPUT);
    pinMode(C_BUTTON_1, INPUT);
    pinMode(C_BUTTON_2, INPUT);
    pinMode(L_BUTTON_G, INPUT);
    pinMode(L_BUTTON_1, INPUT);
    pinMode(L_BUTTON_2, INPUT);
}

void G_floor_call() {
    int sleep = abs(last_floor - target_floor);
    sleep = sleep * 2000;
    elevator_servo.write(88);
    delay(sleep);
    elevator_servo.write(95);
    delay(1000);
    door_servo.write(90);
	delay(1000);
    G_to_floors();
}

void G_to_floors() {
    while (true) {
        L_button_state_G = digitalRead(L_BUTTON_G);
        L_button_state_1 = digitalRead(L_BUTTON_1);
        L_button_state_2 = digitalRead(L_BUTTON_2);

        if(L_button_state_G == HIGH) {
            last_floor = 1;
            G_to_G();
        }
        else if(L_button_state_1 == HIGH) {
            last_floor = 2;
            G_to_1();
        }
        delay(500);
    }
}

void G_to_G() {
    door_servo.write(0);
    delay(1000);
    door_servo.write(90);
    delay(1000);
    door_servo.write(0);
    delay(1000);
}

void G_to_1() {
    door_servo.write(0);
    delay(1000);
    elevator_servo.write(88);
    delay(2000);
    elevator_servo.write(93.5);
    delay(1000);
    door_servo.write(90);
    delay(5000);
    door_servo.write(0);
    delay(1000);
}

void loop() {
    elevator_servo.write(93.5);   
    door_servo.write(0);        

    C_button_state_G = digitalRead(C_BUTTON_G);
    C_button_state_1 = digitalRead(C_BUTTON_1);
    C_button_state_2 = digitalRead(C_BUTTON_2);

    if (C_button_state_G == HIGH) {
        target_floor = 1;
        G_floor_call();
    }
}