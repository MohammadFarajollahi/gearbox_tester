#define TFT_GREY 0x5AEB

float ltx = 0;                  // Saved x coord of bottom of needle
uint16_t osx = 120, osy = 120;  // Saved x & y coords
uint32_t updateTime = 0;        // time for next update

int old_analog = -999;   // Value last displayed
int old_digital = -999;  // Value last displayed

int value[6] = { 0, 0, 0, 0, 0, 0 };
int old_value[6] = { -1, -1, -1, -1, -1, -1 };
int d = 0;


void voltmetr() {


  if (start == 0) {
    start = 1;
    analogMeter();  // Draw analogue meter
    tft.drawJpgFile(SD, "/VOLTMETER.jpg", 265, 1);
  }


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

  //voltage_avg2 = exp((voltage_avg2 + 1122.62) / 957.51) / 1.33;

  d = map(voltage_avg2, 0, 40, 0, 100);

  plotNeedle(d, 0);  // It takes between 2 and 12ms to replot the needle with zero delay
                     //Serial.println(millis()-t); // Print time taken for meter update

  tft.setTextFont(1);
  tft.setTextSize(4);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.fillRoundRect(250, 180, 185, 50, 1, TFT_BLACK);
  tft.setCursor(55, 195);
  tft.printf("VOLTAGE:%.2f V", voltage_avg2);

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


// #########################################################################
//  Draw the analogue meter on the screen
// #########################################################################
void analogMeter() {
  tft.setTextSize(1);
  // Meter outline
  tft.fillRect(0, 0, 239, 126, TFT_GREY);
  tft.fillRect(5, 3, 230, 119, TFT_WHITE);

  tft.setTextColor(TFT_BLACK);  // Text colour

  // Draw ticks every 5 degrees from -50 to +50 degrees (100 deg. FSD swing)
  for (int i = -50; i < 51; i += 5) {
    // Long scale tick length
    int tl = 15;

    // Coodinates of tick to draw
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (100 + tl) + 120;
    uint16_t y0 = sy * (100 + tl) + 140;
    uint16_t x1 = sx * 100 + 120;
    uint16_t y1 = sy * 100 + 140;

    // Coordinates of next tick for zone fill
    float sx2 = cos((i + 5 - 90) * 0.0174532925);
    float sy2 = sin((i + 5 - 90) * 0.0174532925);
    int x2 = sx2 * (100 + tl) + 120;
    int y2 = sy2 * (100 + tl) + 140;
    int x3 = sx2 * 100 + 120;
    int y3 = sy2 * 100 + 140;

    // Yellow zone limits
    if (i >= -50 && i < 0) {
     tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_GREEN);
     tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREEN);
    }

    // Green zone limits
    if (i >= 0 && i < 25) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_ORANGE);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_ORANGE);
    }

    // Orange zone limits
    if (i >= 25 && i < 50) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_RED);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_RED);
    }

    // Short scale tick length
    if (i % 25 != 0) tl = 8;

    // Recalculate coords incase tick lenght changed
    x0 = sx * (100 + tl) + 120;
    y0 = sy * (100 + tl) + 140;
    x1 = sx * 100 + 120;
    y1 = sy * 100 + 140;

    // Draw tick
    tft.drawLine(x0, y0, x1, y1, TFT_BLACK);

    // Check if labels should be drawn, with position tweaks
    if (i % 25 == 0) {
      // Calculate label positions
      x0 = sx * (100 + tl + 10) + 120;
      y0 = sy * (100 + tl + 10) + 140;
      switch (i / 25) {
        case -2: tft.drawCentreString("0", x0, y0 - 12, 2); break;
        case -1: tft.drawCentreString("10", x0, y0 - 9, 2); break;
        case 0: tft.drawCentreString("20", x0, y0 - 6, 2); break;
        case 1: tft.drawCentreString("30", x0, y0 - 9, 2); break;
        case 2: tft.drawCentreString("40", x0, y0 - 12, 2); break;
      }
    }

    // Now draw the arc of the scale
    sx = cos((i + 5 - 90) * 0.0174532925);
    sy = sin((i + 5 - 90) * 0.0174532925);
    x0 = sx * 100 + 120;
    y0 = sy * 100 + 140;
    // Draw scale arc, don't draw the last part
    if (i < 50) tft.drawLine(x0, y0, x1, y1, TFT_BLACK);
  }

  tft.drawString("VOLT", 5 + 230 - 40, 119 - 20, 2);  // Units at bottom right
  tft.drawCentreString("VOLT", 120, 70, 4);           // Comment out to avoid font 4
  tft.drawRect(5, 3, 230, 119, TFT_BLACK);            // Draw bezel line

  plotNeedle(0, 0);  // Put meter needle at 0
}

// #########################################################################
// Update needle position
// This function is blocking while needle moves, time depends on ms_delay
// 10ms minimises needle flicker if text is drawn within needle sweep area
// Smaller values OK if text not in sweep area, zero for instant movement but
// does not look realistic... (note: 100 increments for full scale deflection)
// #########################################################################
void plotNeedle(int value, byte ms_delay) {
  tft.setTextSize(1);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  char buf[8];
  dtostrf(value, 4, 0, buf);
  tft.drawRightString("DC", 40, 119 - 20, 2);

  if (value < -10) value = -10;  // Limit value to emulate needle end stops
  if (value > 110) value = 110;

  // Move the needle util new value reached
  while (!(value == old_analog)) {
    if (old_analog < value) old_analog++;
    else old_analog--;

    if (ms_delay == 0) old_analog = value;  // Update immediately id delay is 0

    float sdeg = map(old_analog, -10, 110, -150, -30);  // Map value to angle
    // Calcualte tip of needle coords
    float sx = cos(sdeg * 0.0174532925);
    float sy = sin(sdeg * 0.0174532925);

    // Calculate x delta of needle start (does not start at pivot point)
    float tx = tan((sdeg + 90) * 0.0174532925);

    // Erase old needle image
    tft.drawLine(120 + 20 * ltx - 1, 140 - 20, osx - 1, osy, TFT_WHITE);
    tft.drawLine(120 + 20 * ltx, 140 - 20, osx, osy, TFT_WHITE);
    tft.drawLine(120 + 20 * ltx + 1, 140 - 20, osx + 1, osy, TFT_WHITE);

    // Re-plot text under needle
    tft.setTextColor(TFT_BLACK);
    tft.drawCentreString("VOLT", 120, 70, 4);  // // Comment out to avoid font 4

    // Store new needle end coords for next erase
    ltx = tx;
    osx = sx * 98 + 120;
    osy = sy * 98 + 140;

    // Draw the needle in the new postion, magenta makes needle a bit bolder
    // draws 3 lines to thicken needle
    tft.drawLine(120 + 20 * ltx - 1, 140 - 20, osx - 1, osy, TFT_RED);
    tft.drawLine(120 + 20 * ltx, 140 - 20, osx, osy, TFT_MAGENTA);
    tft.drawLine(120 + 20 * ltx + 1, 140 - 20, osx + 1, osy, TFT_RED);

    // Slow needle down slightly as it approaches new postion
    if (abs(old_analog - value) < 10) ms_delay += ms_delay / 5;

    // Wait before next update
    delay(ms_delay);
  }
}
