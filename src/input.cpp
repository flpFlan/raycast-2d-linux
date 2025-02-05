#include <input.hpp>

#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

static struct termios orig_termios;

void Input::Setup() {
  std::atexit((void (*)())_ResetTTY);
  _SetTTYRaw();
  int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void Input::_SetTTYRaw() {
  struct termios raw;

  raw = orig_termios; /* copy original and then modify below */

  /* input modes - clear indicated ones giving: no break, no CR to NL,
     no parity check, no strip char, no start/stop output (sic) control */
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

  /* output modes - clear giving: no post processing such as NL to CR+NL */
  raw.c_oflag &= ~(OPOST);

  /* control modes - set 8 bit chars */
  raw.c_cflag |= (CS8);

  /* local modes - clear giving: echoing off, canonical off (no erase with
     backspace, ^U,...),  no extended functions, no signal chars (^Z,^C) */
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

  /* control chars - set return condition: min number of bytes and timer */
  raw.c_cc[VMIN] = 5;
  raw.c_cc[VTIME] = 8; /* after 5 bytes or .8 seconds
                          after first byte seen      */
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 0; /* immediate - anything       */
  raw.c_cc[VMIN] = 2;
  raw.c_cc[VTIME] = 0; /* after two bytes, no timer  */
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 8; /* after a byte or .8 seconds */

  /* put terminal in raw mode after flushing */
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int Input::_ResetTTY() {
  /* flush and reset */
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) < 0)
    return -1;
  return 0;
}

char Input::GetKeyUnblocked() { return std::getchar(); }
