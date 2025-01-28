

void main_menu() {
  keypad_();
  if (change_menu == 1) {
    change_menu = 0;
    //tft.fillScreen(TFT_BLACK);

    if (main_menu_select == 1) tft.drawJpgFile(SD, "/shirbarqi_tester.jpg", 100, 65);
    if (main_menu_select == 2) tft.drawJpgFile(SD, "/voltmetr1.jpg", 100, 65);
    if (main_menu_select == 3) tft.drawJpgFile(SD, "/dynamtester.jpg", 100, 65);
    if (main_menu_select == 4) tft.drawJpgFile(SD, "/signal1.jpg", 100, 65);
    if (main_menu_select == 5) tft.drawJpgFile(SD, "/boq.jpg", 100, 65);
    //if (main_menu_select == 6) tft.drawJpgFile(SD, "/setting.jpg", 0, 0);

    delay(100);
  }


  if (right_ == 1) {
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    ++main_menu_select;
    change_menu = 1;
    if (main_menu_select > 5) main_menu_select = 1;
    delay(250);
  }

  if (left_ == 1) {
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    --main_menu_select;
    change_menu = 1;
    if (main_menu_select < 1) main_menu_select = 5;
    delay(250);
  }

  if (ok_ == 1) {
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    menu_select = main_menu_select;
    if (menu_select == 1) {
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
      delay(500);
    }


    if (menu_select == 4) {
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
  }
}