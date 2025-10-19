#include <Arduino.h>
#include <Servo.h>
#define BASE_LINK 0xFF
#define SHOULDER_LINK 0xFE
#define ELBOW_LINK 0xFD
#define WRIST_LINK 0xFC
#define GRIPPER_LINK 0xFB
Servo joint[5];

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 5; i++) {
    joint[i].attach(i + 4);
  }
  joint[0].write(90);  // Gripper
  joint[1].write(90);  // Wrist
  joint[2].write(180); // Elbow
  joint[3].write(0);   // Shoulder
  joint[4].write(90);  // Base
}
// ...existing code...
void loop() {
  if (Serial.available() >= 2) {
    uint8_t id = Serial.read();
    int degree = Serial.read();

    // Match the ID to the joint index
    int8_t joint_index = -1;
    if (id - 0xFB >= 0 && id - 0xFB <= 4) {
      joint_index = id - 0xFB; // Map IDs to joint indices
    }

    if (joint_index != -1) {
      if (degree >= 0 && degree <= 180) {
        joint[joint_index].write(degree);
      }
    }
  }
}
// ...existing code...