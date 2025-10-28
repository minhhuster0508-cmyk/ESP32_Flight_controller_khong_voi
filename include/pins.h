#pragma once
// I2C pins (đổi theo dây thật của m)
#ifndef I2C_SDA_PIN
#define I2C_SDA_PIN  4
#endif
#ifndef I2C_SCL_PIN
#define I2C_SCL_PIN  5
#endif

// Motor pins (PWM -> Gate AO3400; D->motor-, S->GND; GND chung)
#ifndef MOTOR_FL_PIN
#define MOTOR_FL_PIN 6
#endif
#ifndef MOTOR_FR_PIN
#define MOTOR_FR_PIN 7
#endif
#ifndef MOTOR_RL_PIN
#define MOTOR_RL_PIN 8
#endif
#ifndef MOTOR_RR_PIN
#define MOTOR_RR_PIN 9
#endif

// LEDC channels (mỗi motor 1 channel)
#define CH_M_FL 0
#define CH_M_FR 1
#define CH_M_RL 2
#define CH_M_RR 3
