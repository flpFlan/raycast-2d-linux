#pragma once

using byte = unsigned char;

// //双缓冲
// int active = 0;
// COORD coord = {0,0};
// DWORD bytes = 0;
// //创建新的控制台缓冲区
// HANDLE buf0 = CreateConsoleScreenBuffer(
//     GENERIC_WRITE,//定义进程可以往缓冲区写数据
//     FILE_SHARE_WRITE,//定义缓冲区可共享写权限
//     NULL,
//     CONSOLE_TEXTMODE_BUFFER,
//     NULL
// );
// HANDLE buf1 = CreateConsoleScreenBuffer(
//     GENERIC_WRITE,//定义进程可以往缓冲区写数据
//     FILE_SHARE_WRITE,//定义缓冲区可共享写权限
//     NULL,
//     CONSOLE_TEXTMODE_BUFFER,
//     NULL
// );

constexpr int dW = 9, dH = 9; // 字体大小

class Screen {
public:
  int WIDTH = 80;
  int HEIGHT = 40;

  Screen();
  // 画布清除
  void Clear();
  // 画点
  void DrawPoint(int x, int y, byte luminuns);
  // 画线 bresenham
  void DrawLine(int x0, int y0, int x1, int y1, byte luminuns);
  // 将画布渲染至屏幕
  void Show();

  inline int Height();

  inline int Width();

  ~Screen();

private:
  byte *canvas = new byte[WIDTH * HEIGHT];

  void Setup();

  void FillScreenWithString(const char *frame);

  constexpr char brightness(byte n) const {
    return " .,^:-+abcdwf$&%#@"[n * 18 / 256];
  }
};
