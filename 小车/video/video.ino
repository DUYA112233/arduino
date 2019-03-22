#include <U8g2lib.h>
#include <U8x8lib.h>

//U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

uint8_t apple[704] = {};
void setup() {
  Serial.begin(115200);
  u8g2.begin();
}
void loop() {
  while (Serial.available() > 0){
    Serial.readBytes(apple, 704);
        u8g2.firstPage();
        do {
          u8g2.drawXBM(21,0, 64,86, apple);
        } while (u8g2.nextPage());
        Serial.print('1');
    }
}
