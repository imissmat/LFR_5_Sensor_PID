//motor function
void motor(int left_motor, int right_motor) {
  if (left_motor > 0) {
    digitalWrite(lmf, 1);
    digitalWrite(lmb, 0);
  } else {
    left_motor = -(left_motor);
    digitalWrite(lmf, 0);
    digitalWrite(lmb, 1);
  }
  if (right_motor > 0) {
    digitalWrite(rmf, 1);
    digitalWrite(rmb, 0);
  } else {
    right_motor = -(right_motor);
    digitalWrite(rmf, 0);
    digitalWrite(rmb, 1);
  }

  if (left_motor > 250) left_motor = 250;
  if (right_motor > 250) right_motor = 250;

  analogWrite(lms, left_motor);
  analogWrite(rms, right_motor);
}

void motor_test() {
  motor(200, 200);
  delay(3000);
  motor(0, 0);
  return;
}