

void drawGrid() {
  // رسم شبکه برای صفحه نمایشگر
  tft.setTextColor(TFT_DARKGREY);
  for (int x = 0; x < 480; x += 40) {
    tft.drawLine(x, 0, x, 320 - signalInfoHeight, TFT_DARKGREY);
  }
  for (int y = 0; y < 320 - signalInfoHeight; y += 40) {
    tft.drawLine(0, y, 480, y, TFT_DARKGREY);
  }
}

void drawSignalInfo(float voltage, float freq) {
  // نمایش اطلاعات سیگنال در پایین صفحه

  tft.setTextColor(TFT_YELLOW);
  tft.fillRect(0, 300 - signalInfoHeight, 480, 320, TFT_BLACK);


  if (voltage == 0) {
    ++test_voltage;
    if (test_voltage >= 3) {
      tft.fillRect(0, 300 - signalInfoHeight, 480, 320, TFT_BLACK);


      test_voltage = 10;
      tft.setCursor(200, 300 - signalInfoHeight + 10);
      tft.print("frequency: No Signal");
      tft.setCursor(10, 300 - signalInfoHeight + 10);
      tft.printf("Voltage: %.2f V", voltage);
      freqFult = 1;
      if (show_fail == 0) {
        tft.drawJpgFile(SD, "/test_signal.jpg", 200, 5);
        tft.drawJpgFile(SD, "/oskop_signal.jpg", 0, 0);
        show_fail = 1;
      }
    }
  } else {
    freqFult = 0;
    test_voltage = 0;
  }

  if (freqFult == 0) {
    if (voltage > 0) {
      tft.fillRect(0, 300 - signalInfoHeight, 480, signalInfoHeight, TFT_BLACK);
      tft.setCursor(200, 300 - signalInfoHeight + 10);
      tft.printf("frequency: %.2f Hz", freq);

      tft.setCursor(10, 300 - signalInfoHeight + 10);
      tft.printf("Voltage: %.2f V", voltage);
    }
    if (show_fail == 1) {
      show_fail = 0;
      //tft.fillScreen(TFT_BLACK);
      //drawGrid();
      if (voltage > 0) tft.drawJpgFile(SD, "/signal_ok.jpg", 200, 5);
      if (voltage == 0) tft.drawJpgFile(SD, "/test_signal.jpg", 200, 5);
    }
  }

  //tft.fillRoundRect(0, 290 - signalInfoHeight, 480, signalInfoHeight, 15, TFT_BLACK);
  tft.setCursor(10, 290);
  tft.printf("voltageScale: %.2f", signal_calib);

  tft.setCursor(260, 290);
  tft.printf("threshold: %d", sampleSize);
}

void drawWaveform() {
  for (int i = 0; i < sampleSize - 1; i++) {
    int x1 = i;
    int y1 = map(lastSamples[i], 0, 4095, 270 - signalInfoHeight - 1, 0);
    int x2 = i + 1;
    int y2 = map(lastSamples[i + 1], 0, 4095, 270 - signalInfoHeight - 1, 0);

    // پاک کردن موج قبلی
    tft.drawLine(x1, y1, x2, y2, TFT_BLACK);

    // رسم موج جدید
    y1 = map(samples[i], 0, 4095, 270 - signalInfoHeight - 1, 0);
    y2 = map(samples[i + 1], 0, 4095, 270 - signalInfoHeight - 1, 0);
    tft.drawLine(x1, y1, x2, y2, TFT_GREEN);
  }

  // ذخیره مقادیر فعلی برای حذف موج در فریم بعدی
  memcpy(lastSamples, samples, sizeof(samples));
}

void oskop() {

  unsigned long currentTime = micros();

  // خواندن نمونه‌ها
  for (int i = 0; i < sampleSize; i++) {
    samples[i] = analogRead(analogPin);
    samples[i] *= signal_calib;
    // تشخیص لبه‌ها برای محاسبه فرکانس
    static bool lastSignalState = false;
    bool currentSignalState = samples[i] > threshold;

    if (currentSignalState && !lastSignalState) {  // تشخیص لبه بالا
      unsigned long timeNow = micros();
      unsigned long pulseWidth = timeNow - lastEdgeTime;

      if (pulseWidth > debounceTime) {        // حذف نویز
        frequency_ = 1000000.0 / pulseWidth;  // فرکانس بر حسب هرتز
        lastEdgeTime = timeNow;
      }
    }
    lastSignalState = currentSignalState;
  }

  // رسم موج سیگنال
  drawWaveform();

  // محاسبه ولتاژ و نمایش مشخصات سیگنال
  float voltage = analogRead(analogPin) * voltageScale;
  voltage *= 6.833333;
  voltage_avg += voltage;
  ++volt_cout;
  if (volt_cout >= 3) {
    voltage_avg /= 3;
    voltage = voltage_avg;
    voltage_avg = 0;
    volt_cout = 0;
    drawSignalInfo(voltage, frequency_);
  }
  delay(10);
  keypad_();
  if (up_ == 1) {
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    //++debounceTime;
    sampleSize += 50;
    Serial.println(sampleSize);
    if (sampleSize > 1500) sampleSize = 1500;
  }


  if (down_ == 1) {
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    //--debounceTime;
    sampleSize -= 50;
    Serial.println(sampleSize);
    if (sampleSize < 500) sampleSize = 500;
  }


  if (left_ == 1) {
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    signal_calib -= .1;
    if (signal_calib < .1) signal_calib = .1;
    Serial.println(signal_calib);
  }

  if (right_ == 1) {
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    signal_calib += .1;
    Serial.println(signal_calib);
  }

  if (stop_ == 1) {
    digitalWrite(rele1, LOW);
    digitalWrite(rele2, LOW);
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