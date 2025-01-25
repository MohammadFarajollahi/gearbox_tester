
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#define CS_PIN 32  // پایه CS برای ESP32-S3 (می‌تواند بسته به سیم‌کشی تغییر کند)
#include <Arduino.h>

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <algorithm>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>
class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ILI9488 _panel_instance;
  lgfx::Light_PWM _light_instance;
  lgfx::Bus_SPI _bus_instance;
public:

  LGFX(void) {
    {
      auto cfg = _bus_instance.config();  // バス設定用の構造体を取得します。

      // SPIバスの設定
      cfg.spi_host = VSPI_HOST;  // 使用するSPIを選択  ESP32-S2,C3 : SPI2_HOST or SPI3_HOST / ESP32 : VSPI_HOST or HSPI_HOST
      // ※ ESP-IDFバージョンアップに伴い、VSPI_HOST , HSPI_HOSTの記述は非推奨になるため、エラーが出る場合は代わりにSPI2_HOST , SPI3_HOSTを使用してください。
      cfg.spi_mode = 0;                   // SPI通信モードを設定 (0 ~ 3)
      cfg.freq_write = 40000000;          // 送信時のSPIクロック (最大80MHz, 80MHzを整数で割った値に丸められます)
      cfg.freq_read = 16000000;           // 受信時のSPIクロック
      cfg.spi_3wire = true;               // 受信をMOSIピンで行う場合はtrueを設定
      cfg.use_lock = true;                // トランザクションロックを使用する場合はtrueを設定
      cfg.dma_channel = SPI_DMA_CH_AUTO;  // 使用するDMAチャンネルを設定 (0=DMA不使用 / 1=1ch / 2=ch / SPI_DMA_CH_AUTO=自動設定)
      // ※ ESP-IDFバージョンアップに伴い、DMAチャンネルはSPI_DMA_CH_AUTO(自動設定)が推奨になりました。1ch,2chの指定は非推奨になります。
      cfg.pin_sclk = 18;                       // SPIのSCLKピン番号を設定
      cfg.pin_mosi = 23;                       // SPIのMOSIピン番号を設定
      cfg.pin_miso = 19;                       // SPIのMISOピン番号を設定 (-1 = disable)
      cfg.pin_dc = 2;                          // SPIのD/Cピン番号を設定  (-1 = disable)
      _bus_instance.config(cfg);               // 設定値をバスに反映します。
      _panel_instance.setBus(&_bus_instance);  // バスをパネルにセットします。
    }

    {  // 表示パネル制御の設定を行います。
      auto cfg = _panel_instance.config();
      cfg.pin_cs = 4;     // CS
      cfg.pin_rst = -1;   // RST
      cfg.pin_busy = -1;  // BUSY
      cfg.panel_width = 320;
      cfg.panel_height = 480;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      cfg.offset_rotation = 0;
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits = 1;
      cfg.readable = true;
      cfg.invert = false;
      cfg.rgb_order = false;
      cfg.dlen_16bit = false;  // 16bit
      cfg.bus_shared = true;   // SDカードとバスを共有している場合 trueに設定(drawJpgFile等でバス制御を行います)
      cfg.memory_width = 320;
      cfg.memory_height = 480;
      _panel_instance.config(cfg);
    }


    setPanel(&_panel_instance);
  }
};
LGFX tft;

unsigned long total = 0;
unsigned long tn = 0;



int sd_ok;

int main_menu_select = 1;
int change_menu = 1;
int menu_select;
int main_menu_ = 1;


int k_up = 17;
int k_down = 16;
int k_right = 13;
int k_left = 12;
int k_ok = 5;

///**************pwm***************
const int pwmPin = 15;        // پین خروجی PWM (پین موردنظر خود را وارد کنید)
const int pwmChannel = 0;     // کانال PWM (می‌توانید از 0 تا 15 انتخاب کنید)
const int pwmResolution = 8;  // رزولوشن PWM (بیت‌ها: 8 بیت = 0-255)
int frequency = 50;           // فرکانس اولیه PWM (برحسب هرتز)
int dutyCycle = 10;           // دیوتی سایکل اولیه (50% از 0-255)

void setup() {
  Serial.begin(115200);

  pinMode(k_up, INPUT_PULLUP);
  pinMode(k_down, INPUT_PULLUP);
  pinMode(k_right, INPUT_PULLUP);
  pinMode(k_left, INPUT_PULLUP);
  pinMode(k_ok, INPUT_PULLUP);

  tft.begin();
  tft.setRotation(3); /* Landscape orientation, flipped */ /* TFT init */
  if (!SD.begin(CS_PIN)) {
    Serial.println("Failed to initialize SD card.");
    return;
    sd_ok = 0;
  }

  tft.fillScreen(TFT_BLACK);
    sd_ok = 1;
  tft.fillScreen(TFT_BLACK);
  tft.drawJpgFile(SD, "/start_logo.jpg", 0, 0);
  delay(1000);
  tft.fillScreen(TFT_BLACK);

  Serial.println("ُstart program");

  // تنظیمات کانال PWM
  ledcSetup(pwmChannel, frequency, pwmResolution);
  // اتصال کانال PWM به پین مشخص شده
  ledcAttachPin(pwmPin, pwmChannel);
  // مقدار اولیه دیوتی سایکل
  ledcWrite(pwmChannel, dutyCycle);
  Serial.println("Ready to control frequency and duty cycle.");
}

void loop() {

  if (main_menu_ == 1) main_menu();
  if (main_menu_ == 0) select_menu();
}
