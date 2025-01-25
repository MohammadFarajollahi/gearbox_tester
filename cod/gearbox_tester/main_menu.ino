

void main_menu() {

  if (change_menu == 1) {
    change_menu = 0;
    tft.fillScreen(TFT_BLACK);

    if (main_menu_select == 1) tft.drawJpgFile(SD, "/tester_shirbarqi.jpg", 0, 0);
    if (main_menu_select == 2) tft.drawJpgFile(SD, "/voltmetr.jpg", 0, 0);
    if (main_menu_select == 3) tft.drawJpgFile(SD, "/tester_dynam.jpg", 0, 0);
    if (main_menu_select == 4) tft.drawJpgFile(SD, "/signal.jpg", 0, 0);
    if (main_menu_select == 5) tft.drawJpgFile(SD, "/buzzer.jpg", 0, 0);
    if (main_menu_select == 6) tft.drawJpgFile(SD, "/setting.jpg", 0, 0);

    delay(500);
  }


  if (digitalRead(k_right) == LOW) {
    ++main_menu_select;
    change_menu = 1;
    if (main_menu_select > 6) main_menu_select = 1;
    delay(500);
  }

  if (digitalRead(k_left) == LOW) {
    --main_menu_select;
    change_menu = 1;
    if (main_menu_select < 1) main_menu_select = 6;
    delay(500);
  }

  if (digitalRead(k_ok) == LOW) {


    if (menu_select == 1) {
      tft.fillScreen(TFT_BLACK);
      tft.drawJpgFile(SD, "/selonoeid.jpg", 0, 0);
      menu_select = main_menu_select;
      main_menu_ = 0;
      change_menu = 0;
      delay(1000);
    }
  }
}