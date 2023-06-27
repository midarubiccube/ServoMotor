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
  motor_pin = PWM_pin;
  dir_pin = DIR_pin;
  pinMode(encoder_a,INPUT_PULLUP);      //A相用信号入力　入力割り込みpinを使用　内蔵プルアップ有効
  pinMode(encoder_b,INPUT_PULLUP);      //B相用信号入力　内蔵プルアップ有効
  servoMotor = this;
  //digitalWservoMotorrite(motor_pin, 255); //PWM出力　255
  /* デジタル入力割り込みをA相に設定、立ち上がりエッジでencoder_pulse関数を呼び出し  */
  attachInterrupt(digitalPinToInterrupt(encoder_a), InterruptFunction, RISING);
}

void ServoMotor::setAngle(int angle)
{
  _target = _encoder_cnt + abs(0.277777777777777 * angle);
  _direction = angle < 0 ? 1 : 0;
  Serial.println(_direction);
}

void ServoMotor::startMotor(int speed)
{
  if (_direction)
  {
    digitalWrite(dir_pin, HIGH);
  } else {
    digitalWrite(dir_pin, LOW);
  }
  digitalWrite(motor_pin, speed);
}

void ServoMotor::encoder_pulse() {
  _encoder_cnt++;
  if (_target <= _encoder_cnt)
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
