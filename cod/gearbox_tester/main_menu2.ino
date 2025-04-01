void main_menu2() {

  readBattery();
  char key = keypad.getKey();

  if (key) {
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    if (key == '1') {  //selonoeid
      menu_select = 1;
      digitalWrite(rele1, HIGH);
      digitalWrite(rele2, LOW);
      digitalWrite(rele3, LOW);
      ledcWrite(pwmChannel, dutyCycle);
      ledcSetup(pwmChannel, frequency, pwmResolution);

      tft.fillScreen(TFT_BLACK);
      tft.drawJpgFile(SD, "/selonoeid.jpg", 0, 0);

      main_menu_ = 0;
      change_menu = 0;
      tft.setTextFont(1);
      tft.setTextSize(3);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.fillRoundRect(358, 155, 90, 27, 15, TFT_BLACK);
      tft.setCursor(360, 159);
      int ss = map(dutyCycle, 0, 255, 0, 100);
      String s1 = String(ss) + "%";
      tft.println(s1);

      tft.fillRoundRect(78, 214, 110, 25, 15, TFT_BLACK);
      tft.setCursor(80, 215);
      s1 = String(frequency) + "Hz";
      tft.println(s1);

      tft.setTextFont(1);
      tft.setTextSize(2);
      tft.setTextColor(TFT_BLUE, TFT_BLACK);
      tft.fillRoundRect(90, 285, 95, 23, 15, TFT_BLACK);
      tft.setCursor(103, 289);
      s1 = " A";
      tft.println(s1);

      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.fillRoundRect(350, 285, 95, 23, 15, TFT_BLACK);
      tft.setCursor(359, 289);
      s1 = "12.1 V";
      tft.println(s1);

      for (int i = 0; i < 4; i++) {
        pinMode(rowPins[i], INPUT_PULLUP);
      }

      for (int i = 0; i < 3; i++) {
        pinMode(colPins[i], OUTPUT);
        digitalWrite(colPins[i], HIGH);  // فرض می‌کنیم که وقتی این پین‌ها HIGH باشند، دکمه فعال است.
      }
    }
    /////////////////////////////////////////////////////////////////////
    if (key == '2') {  //voltmetr
      menu_select = 2;
      digitalWrite(rele1, LOW);
      digitalWrite(rele2, LOW);
      digitalWrite(rele3, LOW);
      ledcWrite(pwmChannel, 255);
      ledcSetup(pwmChannel, 5000, pwmResolution);
      start = 0;
      tft.fillScreen(TFT_BLACK);
      main_menu_ = 0;
      change_menu = 0;
      tft.drawJpgFile(SD, "/kadr.jpg", 0, 0);
    }
    /////////////////////////////////////////////////////////////////////
    if (key == '3') {  //dynam
      menu_select = 3;
      digitalWrite(rele1, LOW);
      digitalWrite(rele2, LOW);
      digitalWrite(rele3, LOW);
      ledcWrite(pwmChannel, 255);
      ledcSetup(pwmChannel, 5000, pwmResolution);
      tft.fillScreen(TFT_BLACK);
      main_menu_ = 0;
      change_menu = 0;
      change1 = 0;
      change2 = 0;
      change3 = 0;
      change4 = 0;
      change5 = 0;
      tft.drawJpgFile(SD, "/DYNAM.jpg", 0, 0);
    }
    /////////////////////////////////////////////////////////////////////
    if (key == '4') {  //signal
      menu_select = 4;
      digitalWrite(rele1, LOW);
      digitalWrite(rele2, LOW);
      digitalWrite(rele3, LOW);
      ledcWrite(pwmChannel, 255);
      ledcSetup(pwmChannel, 5000, pwmResolution);
      tft.fillScreen(TFT_BLACK);
      main_menu_ = 0;
      change_menu = 0;
      show_fail = 1;
      freqFult = 0;
      tft.fillScreen(TFT_BLACK);
      tft.setTextSize(2);
      tft.setTextColor(TFT_WHITE);
      tft.print("Initializing...");
      delay(1000);
      tft.fillScreen(TFT_BLACK);
      drawGrid();
      tft.drawJpgFile(SD, "/oskop_signal.jpg", 0, 0);
    }
    /////////////////////////////////////////////////////////////////////
    if (key == '5') {  //boq
      menu_select = 5;
      digitalWrite(rele1, LOW);
      digitalWrite(rele2, HIGH);
      digitalWrite(rele3, LOW);
      ledcWrite(pwmChannel, 255);
      ledcSetup(pwmChannel, 5000, pwmResolution);
      tft.fillScreen(TFT_BLACK);
      main_menu_ = 0;
      change_menu = 0;
      tft.drawJpgFile(SD, "/boq.jpg", 90, 40);
    }
    /////////////////////////////////////////////////////////////////////
    if (key == '6') {  //ohm
      start_ohm = 0;
      alarm_ohm = 0;
      alarm_show = 0;
      check();
      if (alarm_ohm == 0) {
        // tft.fillScreen(TFT_BLACK);
        // tft.drawJpgFile(SD, "/alarm1.jpg", 0, 0);
        // while (1) {
        //   keypad_();

        //   if (start_ == 1) break;
        // }
        menu_select = 6;
        digitalWrite(rele1, LOW);
        digitalWrite(rele2, LOW);
        digitalWrite(rele3, LOW);
        ledcWrite(pwmChannel, 255);
        ledcSetup(pwmChannel, 5000, pwmResolution);
        tft.fillScreen(TFT_BLACK);
        main_menu_ = 0;
        change_menu = 0;
        tft.drawJpgFile(SD, "/OHM.jpg", 0, 0);
      }

      if (alarm_ohm == 1) {
        ledcWrite(pwmChannel, 0);
        ledcSetup(pwmChannel, 0, pwmResolution);
        digitalWrite(buzzer, HIGH);
        delay(150);
        digitalWrite(buzzer, LOW);
        delay(50);
        digitalWrite(buzzer, HIGH);
        delay(150);
        digitalWrite(buzzer, LOW);
        delay(50);
        digitalWrite(buzzer, HIGH);
        delay(150);
        digitalWrite(buzzer, LOW);
        delay(50);
        digitalWrite(buzzer, HIGH);
        delay(150);
        digitalWrite(buzzer, LOW);
        tft.fillScreen(TFT_BLACK);
        tft.drawJpgFile(SD, "/alarm2.jpg", 0, 0);
        delay(2000);
        while (1) {
          keypad_();

          if (stop_ == 1) {
            break;
          }
        }
        digitalWrite(buzzer, HIGH);
        delay(50);
        digitalWrite(buzzer, LOW);
        tft.fillScreen(TFT_BLACK);
        tft.drawJpgFile(SD, "/main_menu2.jpg", 0, 0);
        change_menu = 1;
        main_menu_ = 1;
      }
    }
  }
}


void check() {
  ledcWrite(pwmChannel, 255);
  ledcSetup(pwmChannel, 5000, pwmResolution);
  delay(1000);
  adc_in = 0;
  for (int i = 0; i < 150; i++) {
    adc_in += analogRead(analogPin);
    delay(5);
  }
  voltage_avg2 = adc_in / 150;
  Serial.println(voltage_avg2);
  if (voltage_avg2 < 340) voltage_avg2 /= 83;
  if (voltage_avg2 >= 340 && voltage_avg2 < 500) voltage_avg2 /= 94;
  if (voltage_avg2 >= 500 && voltage_avg2 < 740) voltage_avg2 /= 105.4;
  if (voltage_avg2 >= 740 && voltage_avg2 < 870) voltage_avg2 /= 104.8;
  if (voltage_avg2 >= 870 && voltage_avg2 < 1145) voltage_avg2 /= 114;
  if (voltage_avg2 >= 1145 && voltage_avg2 < 1273) voltage_avg2 /= 115.1;
  if (voltage_avg2 >= 1273 && voltage_avg2 < 1403) voltage_avg2 /= 116.3;
  if (voltage_avg2 >= 1403 && voltage_avg2 < 1535) voltage_avg2 /= 117.8;
  if (voltage_avg2 >= 1535 && voltage_avg2 < 1670) voltage_avg2 /= 119.1;
  if (voltage_avg2 >= 1670 && voltage_avg2 < 1930) voltage_avg2 /= 120.3;
  if (voltage_avg2 >= 1930 && voltage_avg2 < 2199) voltage_avg2 /= 122;
  if (voltage_avg2 >= 2199 && voltage_avg2 < 2460) voltage_avg2 /= 122.6;
  if (voltage_avg2 >= 2460 && voltage_avg2 < 2735) voltage_avg2 /= 124.1;
  if (voltage_avg2 >= 2735) voltage_avg2 /= 125;

  if (voltage_avg2 > 1) {
    alarm_ohm = 1;
  }

  if (voltage_avg2 < 1) {
    alarm_ohm = 0;
  }
}