#include "board/i2c_bus.h"

I2CBus::I2CBus(TwoWire& wire, uint32_t freq) : _w(&wire), _freq(freq) {}

bool I2CBus::begin(int sda, int scl) {
  int useSDA = sda, useSCL = scl;
#ifdef I2C_SDA_PIN
  if (useSDA == -1) useSDA = I2C_SDA_PIN;
#endif
#ifdef I2C_SCL_PIN
  if (useSCL == -1) useSCL = I2C_SCL_PIN;
#endif

  bool ok;
  if (useSDA != -1 && useSCL != -1) ok = _w->begin(useSDA, useSCL, _freq);
  else { ok = _w->begin(); _w->setClock(_freq); }

#if defined(WIRE_HAS_TIMEOUT)
  _w->setWireTimeout(25000 /*us*/, true);
#endif
  return ok;
}

int I2CBus::scan(Stream* log) {
  int found = 0;
  for (uint8_t addr = 0x03; addr <= 0x77; ++addr) {
    _w->beginTransmission(addr);
    if (_w->endTransmission() == 0) {
      ++found;
      if (log) { log->print("I2C 0x"); if (addr < 16) log->print('0'); log->println(addr, HEX); }
    }
    delay(2);
  }
  if (log) { log->print("Found "); log->print(found); log->println(" device(s)"); }
  return found;
}

bool I2CBus::write(uint8_t addr, const uint8_t* data, size_t len) {
  _w->beginTransmission(addr);
  size_t n = _w->write(data, len);
  return (n == len) && (_w->endTransmission() == 0);
}

bool I2CBus::writeReg8(uint8_t addr, uint8_t reg, uint8_t value) {
  uint8_t b[2] = { reg, value };
  return write(addr, b, 2);
}

bool I2CBus::writeReg(uint8_t addr, uint8_t reg, const uint8_t* data, size_t len) {
  _w->beginTransmission(addr);
  _w->write(reg);
  size_t n = _w->write(data, len);
  return (n == len) && (_w->endTransmission() == 0);
}

bool I2CBus::read(uint8_t addr, uint8_t* dst, size_t len) {
  size_t n = _w->requestFrom((int)addr, (int)len);
  if (n != len) return false;
  for (size_t i = 0; i < len; ++i) dst[i] = _w->read();
  return true;
}

bool I2CBus::readReg(uint8_t addr, uint8_t reg, uint8_t* dst, size_t len) {
  _w->beginTransmission(addr);
  _w->write(reg);
  if (_w->endTransmission(false) != 0) return false; // repeated-start

  size_t n = _w->requestFrom((int)addr, (int)len);
  if (n != len) return false;
  for (size_t i = 0; i < len; ++i) dst[i] = _w->read();
  return true;
}

bool I2CBus::readReg8(uint8_t addr, uint8_t reg, uint8_t& value) {
  return readReg(addr, reg, &value, 1);
}

bool I2CBus::writeRead(uint8_t addr, const uint8_t* wbuf, size_t wlen, uint8_t* rbuf, size_t rlen) {
  _w->beginTransmission(addr);
  _w->write(wbuf, wlen);
  if (_w->endTransmission(false) != 0) return false; // repeated-start

  size_t n = _w->requestFrom((int)addr, (int)rlen);
  if (n != rlen) return false;
  for (size_t i = 0; i < rlen; ++i) rbuf[i] = _w->read();
  return true;
}

bool I2CBus::readU16BE(uint8_t addr, uint8_t reg, uint16_t& v) {
  uint8_t b[2]; if (!readReg(addr, reg, b, 2)) return false;
  v = (uint16_t(b[0]) << 8) | b[1]; return true;
}
bool I2CBus::readU24BE(uint8_t addr, uint8_t reg, uint32_t& v) {
  uint8_t b[3]; if (!readReg(addr, reg, b, 3)) return false;
  v = (uint32_t(b[0]) << 16) | (uint32_t(b[1]) << 8) | b[2]; return true;
}
bool I2CBus::readU32BE(uint8_t addr, uint8_t reg, uint32_t& v) {
  uint8_t b[4]; if (!readReg(addr, reg, b, 4)) return false;
  v = (uint32_t(b[0]) << 24) | (uint32_t(b[1]) << 16) | (uint32_t(b[2]) << 8) | b[3]; return true;
}
bool I2CBus::writeU16BE(uint8_t addr, uint8_t reg, uint16_t v) {
  uint8_t b[3] = { reg, uint8_t(v >> 8), uint8_t(v) };
  return write(addr, b, 3);
}
