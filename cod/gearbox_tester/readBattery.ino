


void readBattery() {
  ++readB;
  if (readB >= 50000) {
    readB = 0;

    BattAdc = 0;
    for (int i = 0; i < 100; i++) {
      BattAdc += analogRead(36);
      delay(1);
    }
    battaryVoltage = BattAdc / 100;

    battaryVoltage = map(battaryVoltage, 900, 1070, 0, 100);
    if (battaryVoltage > 100) battaryVoltage = 100;
    if (battaryVoltage < 0) battaryVoltage = 0;


    Serial.print("Adc:");
    Serial.print(BattAdc / 100);
    Serial.print(" /BAtt:");
    Serial.println(battaryVoltage);
    tft.setTextFont(1);
    tft.setTextSize(1);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.fillRoundRect(400, 0, 150, 10, 1, TFT_BLACK);
    tft.setCursor(400, 0);
    String batttext = "Battery:" + String(battaryVoltage) + "%";
    tft.println(batttext);
  }
}