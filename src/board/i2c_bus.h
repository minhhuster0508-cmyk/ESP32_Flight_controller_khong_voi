#pragma once
#include <Arduino.h>
#include <Wire.h>

#if __has_include("config.h")
  #include "config.h"
#endif

class I2CBus {
public:
  explicit I2CBus(TwoWire& wire = Wire, uint32_t freq = 400000);
  // ESP32: nếu sda/scl = -1 -> lấy từ config (nếu có) -> rơi về default variant
  bool begin(int sda = -1, int scl = -1);

  int  scan(Stream* log = &Serial);

  bool write(uint8_t addr, const uint8_t* data, size_t len);
  bool writeReg8(uint8_t addr, uint8_t reg, uint8_t value);
  bool writeReg(uint8_t addr, uint8_t reg, const uint8_t* data, size_t len);

  bool read(uint8_t addr, uint8_t* dst, size_t len);
  bool readReg(uint8_t addr, uint8_t reg, uint8_t* dst, size_t len);
  bool readReg8(uint8_t addr, uint8_t reg, uint8_t& value);
  bool writeRead(uint8_t addr, const uint8_t* wbuf, size_t wlen, uint8_t* rbuf, size_t rlen);

  bool readU16BE(uint8_t addr, uint8_t reg, uint16_t& v);
  bool readU24BE(uint8_t addr, uint8_t reg, uint32_t& v);
  bool readU32BE(uint8_t addr, uint8_t reg, uint32_t& v);
  bool writeU16BE(uint8_t addr, uint8_t reg, uint16_t v);

private:
  TwoWire* _w;
  uint32_t _freq;
};
