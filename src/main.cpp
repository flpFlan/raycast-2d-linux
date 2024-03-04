#include "camera.hpp"
#include "input.hpp"
#include "screen.hpp"
#include <thread>

int main(int /*argc*/, char * /*argv*/[]) {
  Camera camera;
  Screen screen;

  Input::Setup();

  while (1) {
    {
      char ch = Input::GetKeyUnblocked();
      if (ch == '\xff') {
        std::this_thread::yield();
        continue;
      }
      switch (ch) {
      case 'd':
        camera.right();
        break;
      case 's':
        camera.donw();
        break;
      case 'a':
        camera.left();
        break;
      case 'w':
        camera.up();
        break;
      }
    }

    camera.Show(screen);
    screen.Show();
    screen.Clear();
  }
}
