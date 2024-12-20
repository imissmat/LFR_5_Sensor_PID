void frontsonar() {
  f_sonar = front_sonar.ping_cm();
}

void sonar_test() {
  while (1) {
    f_sonar = front_sonar.ping_cm();
    Serial.print("f_sonar: ");
    Serial.print(f_sonar);
    if (2 < f_sonar && f_sonar < 30) {
      Serial.println("front Detected");
    } else {
      Serial.println("Not Detected");
    }
  }
}void obstacle_avoid() {
  // Stop the robot when an obstacle is detected
    motor(0, 0);
    f_sonar = front_sonar.ping_cm();


  // Resume line following after the obstacle is removed
  while (1) {
    line_follow(); // Call the line-following function
    if (f_sonar < 25) { // If an obstacle is detected again, break the loop
      break;
    }
  }
}