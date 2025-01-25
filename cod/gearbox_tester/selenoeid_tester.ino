


void  selenoeid_tester(){

   if (digitalRead(k_ok) == LOW) {
      change_menu = 1;
      main_menu_ = 1;
    }

    
    if (digitalRead(k_right) == LOW) {
      frequency += 1; // افزایش فرکانس
      if (frequency > 10000) frequency = 50; // محدود کردن فرکانس
      ledcSetup(pwmChannel, frequency, pwmResolution);
      Serial.print("Frequency set to: ");
      Serial.println(frequency);
    }

     if (digitalRead(k_left) == LOW) {
      frequency -= 1; // افزایش فرکانس
      if (frequency < 10) frequency = 10; // محدود کردن فرکانس
      ledcSetup(pwmChannel, frequency, pwmResolution);
      Serial.print("Frequency set to: ");
      Serial.println(frequency);
    }

    if (digitalRead(k_up) == LOW) { 
      dutyCycle += 1; // افزایش دیوتی سایکل
      if (dutyCycle > 255) dutyCycle = 0; // محدود کردن دیوتی سایکل
      ledcWrite(pwmChannel, dutyCycle);
      Serial.print("Duty cycle set to: ");
      Serial.println(dutyCycle * 100 / 255); // نمایش درصد
    }

    if (digitalRead(k_down) == LOW) { 
      dutyCycle -= 1; // افزایش دیوتی سایکل
      if (dutyCycle < 1) dutyCycle = 1; // محدود کردن دیوتی سایکل
      ledcWrite(pwmChannel, dutyCycle);
      Serial.print("Duty cycle set to: ");
      Serial.println(dutyCycle * 100 / 255); // نمایش درصد
    }
}