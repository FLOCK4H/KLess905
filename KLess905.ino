#include <SPI.h>

#define NRF905_TXE_PIN 4  // TX Enable (high for transmit mode)
#define NRF905_CE_PIN 5   // Chip Enable
#define NRF905_PWR_PIN 16 // Power Up
#define NRF905_CSN_PIN 15 // Chip Select Not (CSN), needed to access SPI

// Pins for SPI configuration (to set 115 channel (~433.9Mhz))
#define SCK_PIN 18  // SPI clock pin
#define MOSI_PIN 23 // SPI MOSI pin
#define MISO_PIN 19 // SPI MISO pin

void setup() {
  pinMode(NRF905_TXE_PIN, OUTPUT);
  pinMode(NRF905_CE_PIN, OUTPUT);
  pinMode(NRF905_PWR_PIN, OUTPUT);
  pinMode(NRF905_CSN_PIN, OUTPUT);

  digitalWrite(NRF905_TXE_PIN, LOW);
  digitalWrite(NRF905_CE_PIN, LOW);
  digitalWrite(NRF905_PWR_PIN, LOW);

  // start SPI communication
  digitalWrite(NRF905_CSN_PIN, HIGH);

  digitalWrite(NRF905_PWR_PIN, HIGH);
  delay(100);  // Allow NRF905 to power up

  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, NRF905_CSN_PIN);
  
  Serial.begin(115200);

  // Configure NRF905 for 433.92 MHz
  configureNRF905(115); // CH_NO = 115 for ~433.9 MHz

  // Enable transmit mode
  digitalWrite(NRF905_TXE_PIN, HIGH);
}

void configureNRF905(uint16_t ch_no) {
 // Configure registry accordingly to NRF905 datasheet
  uint8_t config[10];

  config[0] = ch_no & 0xFF;

  config[1] = ((0 << 5) | // AUTO_RETRAN = 0
               (0 << 4) | // RX_RED_PWR = 0
               (0b11 << 2) | // PA_PWR = 11 (max power)
               (0 << 1) | // HFREQ_PLL = 0 for 433 MHz
               ((ch_no >> 8) & 0x01)); // CH_NO[8]

  config[2] = ((0 << 7) |
               (0b100 << 4) | // TX_AFW = 4 bytes
               (0 << 3) | // Reserved
               (0b100)); // RX_AFW = 4 bytes

  config[3] = ((0 << 6) |
               (0b100000));

  config[4] = ((0 << 6) |
               (0b100000));

  config[5] = 0xE7;
  config[6] = 0xE7;
  config[7] = 0xE7;
  config[8] = 0xE7;
  config[9] = ((1 << 7) | // CRC_MODE = 1 (16-bit CRC)
               (1 << 6) | // CRC_EN = 1 (enable CRC)
               (0b011 << 3) | // XOF = 011 (16 MHz)
               (0 << 2) | // UP_CLK_EN = 0
               (0b00)); // UP_CLK_FREQ = 00

  digitalWrite(NRF905_CSN_PIN, LOW);
  SPI.transfer(0x00);
  for (int i = 0; i < 10; i++) {
    SPI.transfer(config[i]);
  }
  digitalWrite(NRF905_CSN_PIN, HIGH);
}

void sendRandomData() {
  // CE HIGH to start transmission
  digitalWrite(NRF905_CE_PIN, HIGH);
  delayMicroseconds(10); // CE must be high for at least 10 us
  digitalWrite(NRF905_CE_PIN, LOW);
  delay(10);
}

void setTXPayload() {
  uint8_t tx_payload[32];

  for (int i = 0; i < 32; i++) {
    tx_payload[i] = 256;
  }

  digitalWrite(NRF905_CSN_PIN, LOW);
  SPI.transfer(0x20); // Command to write TX payload
  for (int i = 0; i < 32; i++) {
    SPI.transfer(tx_payload[i]);
  }
}

int main() {
  setTXPayload();
  digitalWrite(NRF905_CSN_PIN, HIGH);
  while (1) {
    sendRandomData();
    Serial.println("Jamming...");
  }
}

void loop() {
  main();
}