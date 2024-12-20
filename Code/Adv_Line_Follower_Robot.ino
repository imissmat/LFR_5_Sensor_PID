#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST);
#include <NewPing.h>
//Ultrasonic Pin Connected with Arduino
NewPing front_sonar(4, 4, 40);

//Motor pins
#define rmf 9
#define rmb 8
#define lmf 7
#define lmb 6
//EnA and EnB
#define rms 10  //EnA
#define lms 3  //EnB

//buttons and LED pin
#define button1 11
#define button2 12
#define led 13

float c;
int left_motor_speed = 150, right_motor_speed = 150;
int left_motor, right_motor;
int kp = 50, kd = 500, PID_value;
float current_error, previous_error;
int turn_speed = 120;
char t;
int f_sonar;

int sensor[6];  //to store the sensor value
int threshold = 531;    //threshold = (max_value + min_value) / 2

void setup() {
  u8g.setColorIndex(1);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(rms, OUTPUT);
  pinMode(lms, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_fub14);
    u8g.drawStr(10, 20, "BLINDERS");
    u8g.setFont(u8g_font_5x7r);
    u8g.drawStr(2, 40, "Push 1 = Follow Line");
    u8g.drawStr(2, 50, "Push 2 = Check Sensors");
  } while (u8g.nextPage());
  while (digitalRead(button1) == 0) line_follow();
  while (digitalRead(button2) == 0) {
    display_value();
    //analog_value()
    //motor_test();
  }
}