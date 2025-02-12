

void tes_boq() {
  keypad_();
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