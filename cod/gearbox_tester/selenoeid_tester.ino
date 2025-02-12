


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

  // float adc_voltage = voltage_avg2 * (3.3 / 4096.0);
  // float current_voltage = adc_voltage;
  // float current = (current_voltage - 2.5) / 0.100;
  Serial.print("Current Value: ");
  Serial.println(voltage_avg2);

  tft.setTextFont(1);
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.fillRoundRect(90, 285, 99, 23, 15, TFT_BLACK);
  tft.setCursor(103, 289);
  tft.printf("%.2f A", voltage_avg2);

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