#include <ServoMotor.h>


ServoMotor motor;

void setup() {
  motor.begin(9, 8);
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    delay(10);
    int val = Serial.parseInt();    //文字列データを数値に変換

    while (Serial.available() > 0) {//受信バッファクリア
      char t = Serial.read();
    }

    Serial.println(val);         //出力
    motor.setAbsoluteAngle(val);
    motor.startMotor(255);
  }
  delay(5);
}
