#include "ServoMotor.h"

#include <Arduino.h>

ServoMotor::ServoMotor()
{
  _encoder_cnt = 0;
  _target = 0;
  _direction = 0;
  
}

void ServoMotor::begin(int PWM_pin, int DIR_pin)
{
  _motor_pin = PWM_pin;
  _dir_pin = DIR_pin;
  pinMode(encoder_a,INPUT_PULLUP);      //A相用信号入力　入力割り込みpinを使用　内蔵プルアップ有効
  pinMode(encoder_b,INPUT_PULLUP);      //B相用信号入力　内蔵プルアップ有効
  servoMotor = this;
  //digitalWservoMotorrite(motor_pin, 255); //PWM出力　255
  /* デジタル入力割り込みをA相に設定、立ち上がりエッジでencoder_pulse関数を呼び出し  */
  attachInterrupt(digitalPinToInterrupt(encoder_a), InterruptFunction, RISING);
}

//相対的な角度を設定
void ServoMotor::setRelativeAngle(int angle)
{
  _target = _encoder_cnt + (float)0.277777777777777 * (float)angle + 0.5;
  _direction = angle < 0 ? 1 : 0;
  Serial.println(_direction);
}

//絶対的な角度を設定
void ServoMotor::setAbsoluteAngle(int angle)
{
  int cal_angle;
  if (_encoder_cnt / 100 && angle == 360)
  {
    cal_angle = 0;
  } else {
    cal_angle = (int)((float)0.277777777777777 * (float)angle + 0.5) - _encoder_cnt % 101;
  }
  _target = _encoder_cnt + cal_angle;
  _direction = cal_angle < 0 ? 1 : 0;
  Serial.println(_target);
}

void ServoMotor::startMotor(int speed)
{
  if(_target == _encoder_cnt) return;

  if (_direction)
  {
    digitalWrite(_dir_pin, HIGH);
  } else {
    digitalWrite(_dir_pin, LOW);
  }
  digitalWrite(_motor_pin, speed);
}

void ServoMotor::encoder_pulse() {
  
  if (digitalRead(3)){
    _encoder_cnt++;
  } else {
    _encoder_cnt--;
  }
  

  if (_target == _encoder_cnt)
  {
    digitalWrite(9, 0);
    Serial.println("ok");
  }
}

ServoMotor* servoMotor;

// digitalPinToInterrupt関数は
void InterruptFunction()
{
  servoMotor->encoder_pulse();
}
