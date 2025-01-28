

void tes_boq() {
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
}