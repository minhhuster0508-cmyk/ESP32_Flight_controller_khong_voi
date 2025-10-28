#pragma once
#include <stdint.h>

// PID gains 
struct PidGains { float kp, ki, kd; };

// Trạng thái cảm biến & ước lượng 
struct State {
  // IMU raw 
  float ax = 0.0f; // gia tốc trục X (g)
  float ay = 0.0f; // gia tốc trục Y (g)
  float az = 0.0f; // gia tốc trục Z (g)
  float gx = 0.0f; // gyro X (deg/s)
  float gy = 0.0f; // gyro Y (deg/s)
  float gz = 0.0f; // gyro Z (deg/s)

  // Giá trị đã fusion
  float roll  = 0.0f; // deg
  float pitch = 0.0f; // deg
  float yaw   = 0.0f; // deg

  // Cao độ (tùy nguồn: VL53L0X hoặc BMP280 đã lọc)
  float alt   = 0.0f; 
};
