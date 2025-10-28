#pragma once
#include <stdint.h>
#include "types.h"
#include "pins.h"

namespace Cfg {
  // System / Loop
  inline constexpr int SERIAL_BAUD   = 115200;
  inline constexpr int LOOP_CTRL_HZ  = 250;
  inline constexpr int LOOP_SENS_HZ  = 500;

  // I2C
  inline constexpr uint32_t I2C_SPEED_HZ = 400000;

  // I2C addresses 
  inline constexpr uint8_t ADDR_MPU  = 0x68; // 0x69 nếu AD0=VCC
  inline constexpr uint8_t ADDR_TOF  = 0x29; // VL53L0X
  inline constexpr uint8_t ADDR_BARO = 0x76; // 0x77 nếu SDO=VCC

  // PWM 
  inline constexpr int PWM_FREQ      = 24000;
  inline constexpr int PWM_RES_BITS  = 12;
  inline constexpr int THROTTLE_MIN  = 0;
  inline constexpr int THROTTLE_MAX  = (1<<PWM_RES_BITS)-1;
  inline constexpr int ARM_MIN       = 20;

  // PID 
  inline constexpr PidGains PID_RP  {0.90f, 0.15f, 0.015f};
  inline constexpr PidGains PID_YAW {0.80f, 0.00f, 0.000f};

  // Kalman noise
  inline constexpr float KF_Q_ANGLE = 0.003f;
  inline constexpr float KF_Q_BIAS  = 0.003f;
  inline constexpr float KF_R_MEAS  = 0.03f;

  // IMU orientation
  inline constexpr int   AXIS_SIGN_X = +1;
  inline constexpr int   AXIS_SIGN_Y = +1;
  inline constexpr int   AXIS_SIGN_Z = +1;
  inline constexpr float BOARD_YAW_DEG = 0.0f;
}
