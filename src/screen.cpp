#include "screen.hpp"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

Screen::Screen() {
  // 窗口大小
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  WIDTH = w.ws_col;
  HEIGHT = w.ws_row;
  Setup();
  Clear();
}

void Screen::Clear() {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (i >= HEIGHT / 2)
        canvas[i * WIDTH + j] = 15;
      else
        canvas[i * WIDTH + j] = 0;
    }
  }
}

void Screen::DrawPoint(int x, int y,
                       byte luminuns) { //(x,y)处亮度为luminuns的点
  if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT) {
    return;
  } else {
    canvas[y * WIDTH + x] = luminuns;
  }
}

void Screen::DrawLine(int x0, int y0, int x1, int y1, byte luminuns) {
  if (x0 < 0 || y0 < 0 || x0 >= WIDTH || y0 >= HEIGHT)
    return;
  if (x1 < 0 || y1 < 0 || x1 >= WIDTH || y1 >= HEIGHT)
    return;
  int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int erro = (dx > dy ? dx : -dy) / 2;

  while (canvas[y0 * WIDTH + x0] = luminuns, x0 != x1 || y0 != y1) {
    int e2 = erro;
    if (e2 > -dx) {
      erro -= dy;
      x0 += sx;
    }
    if (e2 < dy) {
      erro += dx;
      y0 += sy;
    }
  }
}

void Screen::Show() {
  char *frame = new char[WIDTH * HEIGHT];
  for (int i = 0; i < HEIGHT - 1; i++) {
    frame[WIDTH * i + WIDTH - 1] = '\n'; // 除了最后一行填充换行符
  }
  frame[WIDTH * HEIGHT - 1] = '\0'; // 字符串末尾

  // 将画布与边界投影到frame上
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH - 1; j++) {
      frame[i * WIDTH + j] = brightness(canvas[WIDTH * i + j]);
    }
  }
  for (int i = 0; i < HEIGHT; ++i) {
    frame[WIDTH * i] = '@';
    frame[WIDTH * i + WIDTH - 2] = '@';
  }
  for (int j = 0; j < WIDTH - 1; ++j) {
    frame[j] = '@';
    frame[WIDTH * (HEIGHT - 1) + j] = '@';
  }
  FillScreenWithString(frame);
  delete[] frame;
}

inline int Screen::Height() { return HEIGHT; }

inline int Screen::Width() { return WIDTH; }

Screen::~Screen() { delete[] canvas; }

void Screen::FillScreenWithString(const char *frame) {
  std::cout << "\033[H" << std::endl;
  fputs(frame, stdout);
}

void Screen::Setup() {

  // 全屏
  // SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, nullptr);

  // 设置字体大小
  // CONSOLE_FONT_INFOEX cf = {0};
  // cf.cbSize = sizeof cf;
  // cf.dwFontSize.X = dW;
  // cf.dwFontSize.Y = dH;
  // wcscpy_s(cf.FaceName, L"Terminal");
  // SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, &cf);
  // 光标隐藏
  std::cout << "\e[?25l" << std::endl;
  // 设置控制台屏幕缓冲区大小
  // HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
  // CONSOLE_SCREEN_BUFFER_INFO csbi;
  // GetConsoleScreenBufferInfo(hstdout, &csbi);
  // csbi.dwSize.X = csbi.dwMaximumWindowSize.X;
  // csbi.dwSize.Y = csbi.dwMaximumWindowSize.Y;
  // SetConsoleScreenBufferSize(hstdout, csbi.dwSize);

  // 移动窗口Y
  // MoveWindow(console, 0, 0, GetSystemMetrics(SM_CXSCREEN),
  // GetSystemMetrics(SM_CYSCREEN), TRUE);
}
