#include <Arduino.h>

#ifndef ServoMotorLib1_h
#define ServoMotorLib1_h

void InterruptFunction();

struct ServoMotor{
public:
  //コンストラクタ
  ServoMotor();
  void begin(int PWM_pin, int DIR_pin);
  void setRelativeAngle(int angle);
  void setAbsoluteAngle(int angle);
  void startMotor(int speed);
  int getEncoder() { return _encoder_cnt; }

  void encoder_pulse();
private:
  const int encoder_a = 2;                     //A相pin2
  const int encoder_b = 3;                     //B相pin3
  int _motor_pin;
  int _dir_pin;
  int _direction;

  volatile int _encoder_cnt;                     //エンコーダカウント用変数
  volatile int _target;
  //割り込みが起こった際に実行される関数
  
};
extern ServoMotor* servoMotor;
#endif