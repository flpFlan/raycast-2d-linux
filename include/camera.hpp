#pragma once
#include "screen.hpp"
#include "vec2.hpp"

// perspective camera

class Camera {
public:
  double moveSpeed = 0.1 * 5.0; // 移动速度
  double rotSpeed = 0.05 * 3.0; // 旋转速度

  Camera();
  Camera(float x, float y, float dx, float dy);

  void setPosition(vec2 position) { this->position = position; }
  void setDirection(float dx, float dy) { this->forward = vec2(dx, dy); }
  void Show(Screen &screen); // 将相机内容打印到屏幕
  void up();                 // 前进
  void donw();               // 后退
  void left();               // 左转
  void right();              // 右转

  vec2 getForward() { return forward; }
  vec2 getPosition() { return position; }

private:
  // UNIT VECTORS
  vec2 forward;                     // 相机方向
  vec2 position;                    // 相机位置
  double planeX = 0, planeY = 0.66; // 相机平面法向量
};
