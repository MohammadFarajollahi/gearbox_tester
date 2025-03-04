

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
  }

  if (left_ == 1) {
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    --main_menu_select;
    change_menu = 1;
    if (main_menu_select < 1) main_menu_select = 5;
  }

  if (ok_ == 1) {
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    menu_select = main_menu_select;
    if (menu_select == 1) {  //selonoeid
      digitalWrite(rele1, HIGH);
      digitalWrite(rele2, LOW);
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
      s1 = "2.3 A";
      tft.println(s1);

      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.fillRoundRect(350, 285, 95, 23, 15, TFT_BLACK);
      tft.setCursor(359, 289);
      s1 = "12.3 V";
      tft.println(s1);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (menu_select == 2) {  //voltmetr
      digitalWrite(rele1, LOW);
      digitalWrite(rele2, LOW);
      ledcWrite(pwmChannel, 255);
      ledcSetup(pwmChannel, 5000, pwmResolution);
      start = 0;
      tft.fillScreen(TFT_BLACK);
      main_menu_ = 0;
      change_menu = 0;
      tft.drawJpgFile(SD, "/kadr.jpg", 0, 0);
    }

    if (menu_select == 3) {  //dynam
      digitalWrite(rele1, LOW);
      digitalWrite(rele2, LOW);
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

    ///////////////////////////////////////////////////////////////////////////////
    if (menu_select == 4) {  //oskop
      digitalWrite(rele1, LOW);
      digitalWrite(rele2, LOW);
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

    /////////////////////////////////////////////////////////////////////////////////////////
    if (menu_select == 5) {  //test boq
      digitalWrite(rele1, LOW);
      digitalWrite(rele2, HIGH);
      ledcWrite(pwmChannel, 255);
      ledcSetup(pwmChannel, 5000, pwmResolution);
      tft.fillScreen(TFT_BLACK);
      main_menu_ = 0;
      change_menu = 0;
      tft.drawJpgFile(SD, "/boq.jpg", 0, 0);
    }
  }
}