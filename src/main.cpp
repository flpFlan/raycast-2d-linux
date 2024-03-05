#include "camera.hpp"
#include "input.hpp"
#include "screen.hpp"
#include <thread>

// NOTE: before run this program, you must do the following manually
// 1. set font size of your terminal(emulator) to 9
// 2. fullscreen your terminal(emulator)
int main(int /*argc*/, char * /*argv*/[]) {
  Camera camera;
  Screen screen;

  Input::Setup();
  camera.Show(screen);
  screen.Show();
  screen.Clear();

  while (true) {
    switch (Input::GetKeyUnblocked()) {
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
    case 'q':
      exit(EXIT_SUCCESS);
    default: // '\xff' or invalid key
      std::this_thread::yield();
      continue;
    }

    camera.Show(screen);
    screen.Show();
    screen.Clear();
  }
}
