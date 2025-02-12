

void ohmetr() {

  if (start_ohm == 1) {
    adc_in = 0;
    for (int i = 0; i < 150; i++) {
      adc_in += analogRead(34);
      delay(1);
    }
    voltage_avg2 = adc_in / 150;
    float vv = voltage_avg2;
    if (vv >= 2700) voltage_avg2 /= 1.5;
    if (vv < 2600 && vv >= 2300) voltage_avg2 /= 2.5;
    if (vv < 2300 && vv >= 2000) voltage_avg2 /= 6;
    if (vv < 2000 && vv >= 1500) voltage_avg2 /= 18.3;
    if (vv < 1500 && vv >= 1000) voltage_avg2 /= 48;
    if (vv < 1000 && vv >= 200) voltage_avg2 /= 94;
    if (vv < 200 && vv >= 100) voltage_avg2 /= 85;
    if (vv < 100 && vv >= 50) voltage_avg2 /= 85;
    if (vv < 50 && vv >= 30) voltage_avg2 /= 20;
    if (vv < 30 && vv >= 5) voltage_avg2 /= 15;
    if (vv < 5) voltage_avg2 = 0;

    if (voltage_avg2 < 1000) {
      Serial.print("ADC:");
      Serial.print(vv);
      Serial.print("/RES:");
      Serial.println(voltage_avg2);
    }
    if (voltage_avg2 >= 1000) {
      Serial.print("ADC:");
      Serial.print(vv);
      Serial.print("/RES:");
      Serial.println(voltage_avg2 / 1000);
    }

    tft.setTextFont(1);
    tft.setTextSize(3);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.fillRoundRect(195, 245, 190, 40, 1, TFT_BLACK);
    tft.setCursor(120, 250);
    if (vv < 2700) {

      if (voltage_avg2 < 1000) {
        tft.printf("RES:%.2f OHM", voltage_avg2);
      }

      if (voltage_avg2 >= 1000) {
        voltage_avg2 /= 1000;
        tft.printf("RES:%.2f K", voltage_avg2);
      }
    }
    if (vv > 2700) tft.print("RES:---");
  }

  if (start_ohm == 0) {
    adc_in = 0;
    for (int i = 0; i < 100; i++) {
      adc_in += analogRead(analogPin);
      delay(1);
    }
    voltage_avg2 = adc_in / 100;
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
      alarm_show = 0;
      alarm_ohm = 0;
    }

    if (alarm_ohm == 1 && alarm_show == 0) {
      alarm_show = 1;
      digitalWrite(rele1, LOW);
      digitalWrite(rele2, LOW);
      digitalWrite(rele3, LOW);
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
      delay(1000);
      while (1) {
        keypad_();

        if (stop_ == 1) {
          break;
        }
      }
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
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
  }

  keypad_();

  if (start_ == 1) {
    start_ohm = 1;
    digitalWrite(rele1, LOW);
    digitalWrite(rele2, LOW);
    digitalWrite(rele3, HIGH);
    ledcWrite(pwmChannel, 255);
    ledcSetup(pwmChannel, 5000, pwmResolution);
  }

  if (stop_ == 1) {
    digitalWrite(rele3, LOW);
    ledcWrite(pwmChannel, 0);
    ledcSetup(pwmChannel, 0, pwmResolution);
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    tft.fillScreen(TFT_BLACK);
    tft.drawJpgFile(SD, "/main_menu2.jpg", 0, 0);
    change_menu = 1;
    main_menu_ = 1;
  }
}