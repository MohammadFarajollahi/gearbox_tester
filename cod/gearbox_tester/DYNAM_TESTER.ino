

void dynam_test() {
  adc_in = 0;
  for (int i = 0; i < 80; i++) {
    adc_in += analogRead(analogPin);
    delay(5);
  }
  voltage_avg2 = adc_in / 80;
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

  tft.setTextFont(1);
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.fillRoundRect(150, 274, 110, 25, 1, TFT_BLACK);
  tft.setCursor(150, 274);
  tft.printf("%.2fV", voltage_avg2);

  if (voltage_avg2 < 5 && change5 == 0) {  // qaat
    change1 = 1;
    change2 = 0;
    change3 = 0;
    change4 = 0;
    change5 = 1;
    tft.drawJpgFile(SD, "/sim_qat.jpg", 10, 80);
  }

  if (voltage_avg2 < 12.9 && voltage_avg2 >= 9 && change1 == 0) {  // خاموش
    change1 = 1;
    change2 = 0;
    change3 = 0;
    change4 = 0;
    change5 = 0;
    tft.drawJpgFile(SD, "/CAR_OFF.jpg", 10, 80);
  }

  if (voltage_avg2 >= 12.9 && voltage_avg2 < 13.4 && change2 == 0) {  // ضعیف
    change1 = 0;
    change2 = 1;
    change3 = 0;
    change4 = 0;
    change5 = 0;
    tft.drawJpgFile(SD, "/DYNAM_PAEIN.jpg", 10, 80);
  }

  if (voltage_avg2 >= 13.4 && voltage_avg2 <= 14.5 && change3 == 0) {  // نرمال
    change1 = 0;
    change2 = 0;
    change3 = 1;
    change4 = 0;
    change5 = 0;
    tft.drawJpgFile(SD, "/DYNAM_OK.jpg", 10, 80);
  }



  if (voltage_avg2 > 14.5 && change4 == 0) {  // بالا
    change1 = 0;
    change2 = 0;
    change3 = 0;
    change4 = 1;
    change5 = 0;
    tft.drawJpgFile(SD, "/DYNAM_BALA.jpg", 10, 80);
  }

  keypad_();
  if (stop_ == 1) {
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
}