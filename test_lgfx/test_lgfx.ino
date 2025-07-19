#include <LovyanGFX.hpp>

// Create display object
class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ST7796 _panel_instance;
  lgfx::Bus_SPI _bus_instance;

public:
  LGFX() {
    {  // SPI BUS CONFIG
      auto cfg = _bus_instance.config();
      cfg.spi_host = VSPI_HOST;
      cfg.spi_mode = 0;
      cfg.freq_write = 40000000;
      cfg.freq_read = 16000000;
      cfg.spi_3wire = false;
      cfg.use_lock = true;
      cfg.dma_channel = 1;

      cfg.pin_sclk = 14;
      cfg.pin_mosi = 13;
      cfg.pin_miso = 12;
      cfg.pin_dc = 2;


      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }


    {
      auto cfg = _panel_instance.config();
      cfg.pin_cs = 15;
      cfg.pin_rst = -1;
      cfg.pin_busy = -1;

      cfg.memory_width = 320;
      cfg.memory_height = 480;
      cfg.panel_width = 320;
      cfg.panel_height = 480;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      cfg.offset_rotation = 0;

      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits = 0;

      cfg.readable = false;
      cfg.invert = false;      // ← try inverting (some ST7796 need this)
      cfg.rgb_order = false;   // ← try BGR instead of RGB
      cfg.dlen_16bit = false;  // ← try 8-bit serial (not 16-bit parallel)
      cfg.bus_shared = true;

      _panel_instance.config(cfg);
    }

    setPanel(&_panel_instance);
  }
};

LGFX tft;


void setup() {
  Serial.begin(115200);
  pinMode(27, OUTPUT);
  digitalWrite(27, HIGH);  // backlight

  tft.init();
  tft.setRotation(3);

  // Set text color and background color
  tft.setTextColor(TFT_WHITE, TFT_BLACK);  // white text, black background
  tft.setTextSize(2);                      // text size multiplier (2x)

  // Draw text at position x=10, y=10
  tft.setCursor(100, 100);
  tft.println("Hello, ESP32!");
}

void loop() {
  // Fill solid color to verify SPI
  //  tft.fillScreen(TFT_RED);
  //  delay(1000);
  //  tft.fillScreen(TFT_GREEN);
  //  delay(1000);
  //  tft.fillScreen(TFT_BLUE);
  //  delay(1000);
  //  tft.fillScreen(TFT_BLACK);
  //  delay(1000);
}
