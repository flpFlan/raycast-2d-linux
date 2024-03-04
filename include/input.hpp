#pragma once

class Input {
private:
  static void _SetTTYRaw();
  static int _ResetTTY();

public:
  static void Setup();
  static char GetKeyUnblocked();
};
