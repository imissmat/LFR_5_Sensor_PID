//PID_FOLLOW function
bool stop_once_flag = false; // Flag for condition 1 (it will run just 1 time)
void line_follow() {
  u8g.setFont(u8g_font_7x14B);  // Set the font
  u8g.firstPage();
  do {
    u8g.drawStr(5, 35, "Line Following...");
  } while (u8g.nextPage());
  for (int i = 0; i <= 4; i++) {
    digitalWrite(led, HIGH);
    delay(50);
    digitalWrite(led, LOW);
    delay(50);
  }
  while (1) {
    sensor_reading();// 1 for black line and 0 for white line
        // Condition 1: Stop and blink once when specific sensors are triggered
    if (!stop_once_flag && sensor[0] == 0 && sensor[1] == 0 && sensor[2] == 1 && sensor[3] == 1 && sensor[4] == 1) {
      motor(0, 0); // Stop the robot
      digitalWrite(13, HIGH); // Turn on LED connected to D13
      delay(3000); // Wait for 3 seconds
      digitalWrite(13, LOW); // Turn off LED
      stop_once_flag = true; // Ensure this block runs only once
      motor(left_motor_speed, right_motor_speed); // Move forward
      continue;
    }
    //Straight Line Follow
    if (sensor[2] == 1) {
      f_sonar = front_sonar.ping_cm();
      if (5 < f_sonar && f_sonar < 20) {
        obstacle_avoid();
      }
      current_error = 3 - c;                                                 //error calculation
      PID_value = current_error * kp + kd * (current_error - previous_error);  //calculation of PID Value
      previous_error = current_error;
      //adjusting motor speed to keep the robot on line
      right_motor = right_motor_speed - PID_value;
      left_motor = left_motor_speed + PID_value;
      motor(left_motor, right_motor);
    }
    //all sensor in white surface
    if (sensor[0] == 0 && sensor[1] == 0 && sensor[2] == 0 && sensor[3] == 0 && sensor[4] == 0 ) {
      if (t == 'r') right();
      else if (t == 'l') left();
     else U_turn();
    }
    //Right Turn
    if ((sensor[4] == 0 && sensor[0] == 1) || (sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 1 && sensor[4] == 1) || (sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 0 && sensor[3] == 1 && sensor[4] == 0) || (sensor[0] == 0 && sensor[1] == 0 && sensor[2] == 0 && sensor[3] == 0 && sensor[4] == 1) || (sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 0 && sensor[4] == 0)) t = 'r';
    //Left Turn
    if (sensor[4] == 1 && sensor[0] == 0) t = 'l';
    //all sensor in black surface
   // if (sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 1 && sensor[4] == 1) {
    //  delay(30);
    //  sensor_reading();
      if ((sensor[0] + sensor[1] + sensor[2] + sensor[3] + sensor[4]) == 0) {
        motor(0, 0);  //stop
       // while ((sensor[0] + sensor[1] + sensor[2] + sensor[3] + sensor[4]) == 5) sensor_reading();
      } else if (sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 1 && sensor[4] == 1) t = 'r';
        else if (sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 0 && sensor[4] == 0) t ='r';
    }
  }

void right() {
  while (1) {
    motor(turn_speed, -turn_speed);
    while (sensor[2] == 0) sensor_reading();
    motor(-turn_speed, turn_speed);
    delay(20);
    break;
  }
}
void left() {
  while (1) {
    motor(-turn_speed, turn_speed);
    while (sensor[2] == 0) sensor_reading();
    motor(turn_speed, -turn_speed);
    delay(20);
    break;
  }
}
void U_turn() {
  while (1) {
    delay(120);
    digitalWrite(led, HIGH);
    motor(-turn_speed, turn_speed);
    while (sensor[2] == 0) sensor_reading();
    motor(turn_speed, -turn_speed);
    delay(20);
    digitalWrite(led, LOW);
    break;
  }
}