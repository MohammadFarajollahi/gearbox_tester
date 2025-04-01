

void selenoeid_tester() {

  adc_in = 0;
  for (int i = 0; i < 100; i++) {
    adc_in += analogRead(26);
    delay(1);
  }
  voltage_avg2 = adc_in / 100;

  //voltage_avg2 /= 3.1;
  voltage_avg2 -= 1800;
  voltage_avg2 /= 125;
  voltage_avg2 -= .18;
  // Serial.print("Current Value: ");
  // Serial.println(voltage_avg2);
  if (voltage_avg2 >= 0) {
    tft.setTextFont(1);
    tft.setTextSize(2);
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.fillRoundRect(90, 285, 99, 23, 15, TFT_BLACK);
    tft.setCursor(103, 289);
    tft.printf("%.2f A", voltage_avg2);
  }

  //keypad_();
  // بررسی فشار دادن دکمه
  for (int col = 0; col < 3; col++) {
    digitalWrite(colPins[col], LOW);  // فعال کردن ستون

    for (int row = 0; row < 4; row++) {
      if (digitalRead(rowPins[row]) == LOW) {  // بررسی فشار دادن دکمه
        char pressedKey = keys2[row][col];

        if (pressedKey == '#') {  //exit
          digitalWrite(rele1, LOW);
          digitalWrite(rele2, LOW);
          digitalWrite(rele3, LOW);
          ledcWrite(pwmChannel, 0);
          ledcSetup(pwmChannel, 0, pwmResolution);
          digitalWrite(15, 0);
          digitalWrite(buzzer, HIGH);
          delay(50);
          digitalWrite(buzzer, LOW);
          tft.fillScreen(TFT_BLACK);
          tft.drawJpgFile(SD, "/main_menu2.jpg", 0, 0);
          change_menu = 1;
          main_menu_ = 1;
        }
        ///////////////////////////////////////////////////////right///
        if (pressedKey == '6') {
          if (!keyPressed) {  // اگر دکمه قبلاً فشرده نشده باشد
            keyPressed = true;
            lastPressTime = millis();
            digitalWrite(buzzer, HIGH);
            delay(1);
            digitalWrite(buzzer, LOW);
            frequency += 1;                           // افزایش فرکانس
            if (frequency >= 1000) frequency = 1000;  // محدود کردن فرکانس
            ledcSetup(pwmChannel, frequency, pwmResolution);
            Serial.print("Frequency set to: ");
            Serial.println(frequency);
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setTextFont(1);
            tft.setTextSize(3);
            tft.fillRoundRect(78, 214, 110, 25, 15, TFT_BLACK);
            tft.setCursor(80, 215);
            String s1 = String(frequency) + "Hz";
            tft.println(s1);
          }

          // زمانی که دکمه نگه داشته می‌شود
          if (millis() - lastPressTime >= repeatInterval) {
            digitalWrite(buzzer, HIGH);
            delay(1);
            digitalWrite(buzzer, LOW);
            frequency += 1;                           // افزایش فرکانس
            if (frequency >= 1000) frequency = 1000;  // محدود کردن فرکانس
            ledcSetup(pwmChannel, frequency, pwmResolution);
            Serial.print("Frequency set to: ");
            Serial.println(frequency);
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setTextFont(1);
            tft.setTextSize(3);
            tft.fillRoundRect(78, 214, 110, 25, 15, TFT_BLACK);
            tft.setCursor(80, 215);
            String s1 = String(frequency) + "Hz";
            tft.println(s1);
            lastPressTime = millis();  // بروزرسانی زمان
          }
        }
        ///////////////////////////////////////////////////////left///
        if (pressedKey == '4') {
          if (!keyPressed) {  // اگر دکمه قبلاً فشرده نشده باشد
            keyPressed = true;
            lastPressTime = millis();
            digitalWrite(buzzer, HIGH);
            delay(1);
            digitalWrite(buzzer, LOW);
            frequency -= 1;                     // افزایش فرکانس
            if (frequency <= 1) frequency = 1;  // محدود کردن فرکانس
            ledcSetup(pwmChannel, frequency, pwmResolution);
            Serial.print("Frequency set to: ");
            Serial.println(frequency);
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setTextFont(1);
            tft.setTextSize(3);
            tft.fillRoundRect(78, 214, 110, 25, 15, TFT_BLACK);
            tft.setCursor(80, 215);
            String s1 = String(frequency) + "Hz";
            tft.println(s1);
          }

          // زمانی که دکمه نگه داشته می‌شود
          if (millis() - lastPressTime >= repeatInterval) {
            digitalWrite(buzzer, HIGH);
            delay(1);
            digitalWrite(buzzer, LOW);
            frequency -= 1;                     // افزایش فرکانس
            if (frequency <= 1) frequency = 1;  // محدود کردن فرکانس
            ledcSetup(pwmChannel, frequency, pwmResolution);
            Serial.print("Frequency set to: ");
            Serial.println(frequency);
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setTextFont(1);
            tft.setTextSize(3);
            tft.fillRoundRect(78, 214, 110, 25, 15, TFT_BLACK);
            tft.setCursor(80, 215);
            String s1 = String(frequency) + "Hz";
            tft.println(s1);
            lastPressTime = millis();  // بروزرسانی زمان
          }
        }
        ///////////////////////////////////////////////////////up///
        if (pressedKey == '2') {
          if (!keyPressed) {  // اگر دکمه قبلاً فشرده نشده باشد
            keyPressed = true;
            lastPressTime = millis();
            digitalWrite(buzzer, HIGH);
            delay(1);
            digitalWrite(buzzer, LOW);
            dutyCycle += 2;                        // افزایش دیوتی سایکل
            if (dutyCycle > 255) dutyCycle = 255;  // محدود کردن دیوتی سایکل
            ledcWrite(pwmChannel, dutyCycle);
            Serial.print("Duty cycle set to: ");
            Serial.println(dutyCycle * 100 / 255);  // نمایش درصد
            tft.setTextFont(1);
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setTextSize(3);
            tft.fillRoundRect(358, 155, 90, 27, 15, TFT_BLACK);
            tft.setCursor(360, 159);
            int ss = map(dutyCycle, 0, 255, 0, 100);
            String s1 = String(ss) + "%";
            tft.println(s1);
          }

          // زمانی که دکمه نگه داشته می‌شود
          if (millis() - lastPressTime >= repeatInterval) {
            digitalWrite(buzzer, HIGH);
            delay(1);
            digitalWrite(buzzer, LOW);
            dutyCycle += 2;                        // افزایش دیوتی سایکل
            if (dutyCycle > 255) dutyCycle = 255;  // محدود کردن دیوتی سایکل
            ledcWrite(pwmChannel, dutyCycle);
            Serial.print("Duty cycle set to: ");
            Serial.println(dutyCycle * 100 / 255);  // نمایش درصد
            tft.setTextFont(1);
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setTextSize(3);
            tft.fillRoundRect(358, 155, 90, 27, 15, TFT_BLACK);
            tft.setCursor(360, 159);
            int ss = map(dutyCycle, 0, 255, 0, 100);
            String s1 = String(ss) + "%";
            tft.println(s1);
            lastPressTime = millis();  // بروزرسانی زمان
          }
        }
        //////

        ///////////////////////////////////////////////////////down///
        if (pressedKey == '8') {
          if (!keyPressed) {  // اگر دکمه قبلاً فشرده نشده باشد
            keyPressed = true;
            lastPressTime = millis();
            digitalWrite(buzzer, HIGH);
            delay(1);
            digitalWrite(buzzer, LOW);
            dutyCycle -= 2;                    // افزایش دیوتی سایکل
            if (dutyCycle < 1) dutyCycle = 1;  // محدود کردن دیوتی سایکل
            ledcWrite(pwmChannel, dutyCycle);
            Serial.print("Duty cycle set to: ");
            Serial.println(dutyCycle * 100 / 255);  // نمایش درصد
            tft.setTextFont(1);
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setTextSize(3);
            tft.fillRoundRect(358, 155, 90, 27, 15, TFT_BLACK);
            tft.setCursor(360, 159);
            int ss = map(dutyCycle, 0, 255, 0, 100);
            String s1 = String(ss) + "%";
            tft.println(s1);
          }

          // زمانی که دکمه نگه داشته می‌شود
          if (millis() - lastPressTime >= repeatInterval) {
            digitalWrite(buzzer, HIGH);
            delay(1);
            digitalWrite(buzzer, LOW);
            dutyCycle -= 2;                    // افزایش دیوتی سایکل
            if (dutyCycle < 1) dutyCycle = 1;  // محدود کردن دیوتی سایکل
            ledcWrite(pwmChannel, dutyCycle);
            Serial.print("Duty cycle set to: ");
            Serial.println(dutyCycle * 100 / 255);  // نمایش درصد
            tft.setTextFont(1);
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setTextSize(3);
            tft.fillRoundRect(358, 155, 90, 27, 15, TFT_BLACK);
            tft.setCursor(360, 159);
            int ss = map(dutyCycle, 0, 255, 0, 100);
            String s1 = String(ss) + "%";
            tft.println(s1);
            lastPressTime = millis();  // بروزرسانی زمان
          }
        }
        //////
      }
    }

    digitalWrite(colPins[col], HIGH);  // غیرفعال کردن ستون
  }

  // زمانی که دکمه رها می‌شود
  if (keyPressed) {
    bool keyReleased = true;
    for (int col = 0; col < 3; col++) {
      digitalWrite(colPins[col], LOW);  // فعال کردن ستون برای بررسی رها شدن دکمه
      for (int row = 0; row < 4; row++) {
        if (digitalRead(rowPins[row]) == LOW) {
          keyReleased = false;  // اگر دکمه هنوز فشرده باشد
        }
      }
      digitalWrite(colPins[col], HIGH);  // غیرفعال کردن ستون
    }

    if (keyReleased) {
      keyPressed = false;  // دکمه رها شده است
    }
  }
  //////////////////////////

  // if (stop_ == 1) {
  //   digitalWrite(rele1, LOW);
  //   digitalWrite(rele2, LOW);
  //   digitalWrite(rele3, LOW);
  //   ledcWrite(pwmChannel, 0);
  //   ledcSetup(pwmChannel, 0, pwmResolution);
  //   digitalWrite(15, 0);
  //   digitalWrite(buzzer, HIGH);
  //   delay(50);
  //   digitalWrite(buzzer, LOW);
  //   tft.fillScreen(TFT_BLACK);
  //   tft.drawJpgFile(SD, "/main_menu2.jpg", 0, 0);
  //   change_menu = 1;
  //   main_menu_ = 1;
  // }


  // if (right_ == 1) {
  //   digitalWrite(buzzer, HIGH);
  //   delay(50);
  //   digitalWrite(buzzer, LOW);
  //   frequency += 1;                           // افزایش فرکانس
  //   if (frequency >= 1000) frequency = 1000;  // محدود کردن فرکانس
  //   ledcSetup(pwmChannel, frequency, pwmResolution);
  //   Serial.print("Frequency set to: ");
  //   Serial.println(frequency);
  //   tft.setTextColor(TFT_WHITE, TFT_BLACK);
  //   tft.setTextFont(1);
  //   tft.setTextSize(3);
  //   tft.fillRoundRect(78, 214, 110, 25, 15, TFT_BLACK);
  //   tft.setCursor(80, 215);
  //   String s1 = String(frequency) + "Hz";
  //   tft.println(s1);
  //   delay(1);
  // }

  // if (left_ == 1) {
  //   digitalWrite(buzzer, HIGH);
  //   delay(50);
  //   digitalWrite(buzzer, LOW);
  //   frequency -= 1;                     // افزایش فرکانس
  //   if (frequency <= 1) frequency = 1;  // محدود کردن فرکانس
  //   ledcSetup(pwmChannel, frequency, pwmResolution);
  //   Serial.print("Frequency set to: ");
  //   Serial.println(frequency);
  //   tft.setTextColor(TFT_WHITE, TFT_BLACK);
  //   tft.setTextFont(1);
  //   tft.setTextSize(3);
  //   tft.fillRoundRect(78, 214, 110, 25, 15, TFT_BLACK);
  //   tft.setCursor(80, 215);
  //   String s1 = String(frequency) + "Hz";
  //   tft.println(s1);
  //   delay(1);
  // }

  // if (up_ == 1) {
  //   digitalWrite(buzzer, HIGH);
  //   delay(50);
  //   digitalWrite(buzzer, LOW);
  //   dutyCycle += 2;                        // افزایش دیوتی سایکل
  //   if (dutyCycle > 255) dutyCycle = 255;  // محدود کردن دیوتی سایکل
  //   ledcWrite(pwmChannel, dutyCycle);
  //   Serial.print("Duty cycle set to: ");
  //   Serial.println(dutyCycle * 100 / 255);  // نمایش درصد
  //   tft.setTextFont(1);
  //   tft.setTextColor(TFT_WHITE, TFT_BLACK);
  //   tft.setTextSize(3);
  //   tft.fillRoundRect(358, 155, 90, 27, 15, TFT_BLACK);
  //   tft.setCursor(360, 159);
  //   int ss = map(dutyCycle, 0, 255, 0, 100);
  //   String s1 = String(ss) + "%";
  //   tft.println(s1);
  //   delay(1);
  // }

  // if (down_ == 1) {
  //   digitalWrite(buzzer, HIGH);
  //   delay(50);
  //   digitalWrite(buzzer, LOW);
  //   dutyCycle -= 2;                    // افزایش دیوتی سایکل
  //   if (dutyCycle < 1) dutyCycle = 1;  // محدود کردن دیوتی سایکل
  //   ledcWrite(pwmChannel, dutyCycle);
  //   Serial.print("Duty cycle set to: ");
  //   Serial.println(dutyCycle * 100 / 255);  // نمایش درصد
  //   tft.setTextFont(1);
  //   tft.setTextColor(TFT_WHITE, TFT_BLACK);
  //   tft.setTextSize(3);
  //   tft.fillRoundRect(358, 155, 90, 27, 15, TFT_BLACK);
  //   tft.setCursor(360, 159);
  //   int ss = map(dutyCycle, 0, 255, 0, 100);
  //   String s1 = String(ss) + "%";
  //   tft.println(s1);
  //   delay(1);
  // }
}