void sensor_reading() {
  float a;
  float b;
  for (int i = 0; i < 5; i++) {
    if (i < 4) {  //analog read from arduino analog pins except A4 and A5
      sensor[i] = analogRead(i);
    } else {
      sensor[i] = analogRead(i + 2);
    }
    if (sensor[i] > threshold) {
      sensor[i] = 0;
    } else {
      sensor[i] = 1;
    }
  }
  a = (sensor[0] * 1 + sensor[1] * 2 + sensor[2] * 3 + sensor[3] * 4 + sensor[4] * 5);
  b = (sensor[0] + sensor[1] + sensor[2] + sensor[3] + sensor[4]);
  if (b > 0) c = a / b;
}

void display_value() {
  while (1) {
    for (int i = 0; i < 5; i++) {
      if (i < 4) sensor[i] = analogRead(i);
      else sensor[i] = analogRead(i + 2);
      if (sensor[i] > threshold) sensor[i] = 1;
      else sensor[i] = 0;
    }
    f_sonar = front_sonar.ping_cm();
    u8g.setFont(u8g_font_7x14B);
    u8g.firstPage();
    do {
      for (byte i = 0; i < 6; i++) {
        if (i == 4) u8g.setPrintPos(15, 25);
        else if (i == 3) u8g.setPrintPos(30, 25);
        else if (i == 2) u8g.setPrintPos(50, 25);
        else if (i == 1) u8g.setPrintPos(70, 25);
        else if (i == 0) u8g.setPrintPos(90, 25);
        u8g.print(sensor[i]);
        u8g.drawStr(40, 45, "Sonar");
        u8g.setPrintPos(50, 60);
        u8g.print(f_sonar);
      }
    } while (u8g.nextPage());
  }
}

void analog_value() {
  while (1) {
    for (int i = 0; i < 5; i++) {
      if (i < 4) sensor[i] = analogRead(i);
      else sensor[i] = analogRead(i + 2);
    }
    u8g.setFont(u8g_font_7x14B);  // Set the font
    u8g.firstPage();
    do {
      for (byte i = 0; i < 6; i++) {
        if (i == 2) u8g.setPrintPos(5, 42);
        else if (i == 3) u8g.setPrintPos(5, 57);
        else if (i == 1) u8g.setPrintPos(50, 42);
        else if (i == 4) u8g.setPrintPos(50, 57);
        else if (i == 0) u8g.setPrintPos(95, 42);
        u8g.print(sensor[i]);
      }
    } while (u8g.nextPage());
  }
}