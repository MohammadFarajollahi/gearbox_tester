

void keypad_() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("key:");
    Serial.println(key);

    if (key == '1') {
      m1 = 1;
    }

    if (key == '2') {
      up_ = 1;
    }

    if (key == '3') {
      m2 = 1;
    }

    if (key == '4') {
      left_ = 1;
    }

    if (key == '5') {
      ok_ = 1;
    }

    if (key == '6') {
      right_ = 1;
    }

    if (key == '7') {
      m3 = 1;
    }

    if (key == '8') {
      down_ = 1;
    }

    if (key == '9') {
      m4 = 1;
    }

    if (key == '*') {
      start_ = 1;
    }

    if (key == '0') {
      zero = 1;
    }

    if (key == '#') {
      stop_ = 1;
    }
  } else {
    up_ = 0;
    down_ = 0;
    left_ = 0;
    right_ = 0;
    ok_ = 0;
    m1 = 0;
    m2 = 0;
    m3 = 0;
    m4 = 0;
    zero = 0;
    start_ = 0;
    stop_ = 0;
  }
}