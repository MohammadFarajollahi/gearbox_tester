


void selenoeid_tester() {
  keypad_();
  if (ok_ == 1) {
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    tft.fillScreen(TFT_BLACK);
    tft.drawJpgFile(SD, "/main_menu.jpg", 0, 0);
    change_menu = 1;
    main_menu_ = 1;
  }


  if (right_ == 1) {
    digitalWrite(buzzer, HIGH);
    delay(50);
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
    delay(1);
  }

  if (left_ == 1) {
    digitalWrite(buzzer, HIGH);
    delay(50);
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
    delay(1);
  }

  if (up_ == 1) {
    digitalWrite(buzzer, HIGH);
    delay(50);
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
    delay(1);
  }

  if (down_ == 1) {
    digitalWrite(buzzer, HIGH);
    delay(50);
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
    delay(1);
  }
}