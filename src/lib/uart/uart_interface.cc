/* Copyright [2018] Sean Keys */

#include "uart_interface.h"

#include <fcntl.h>

#define LOGGING_LEVEL_1  // TODO move to bazel CC flags
#include "src/lib/logging/logger.h"

namespace PowerEFI {

UARTinterface::UARTinterface() {
  // TODO Auto-generated constructor stub
}

UARTinterface::~UARTinterface() {
  if (tcsetattr(_tty_fd, TCSAFLUSH, &_tty_state)) {
     LOG_ERR("Error tcsetattr()");
  }
}

bool UARTinterface::Init(const string& path) {
  // Setup UART
  errno = 0;
  _tty_fd = open(path.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
  if (errno != 0) {
    LOG_ERR("Problem opening port.");
    return false;
  }
  // Save state
  if (tcgetattr(_tty_fd, &_tty_state)) {
    LOG_ERR("Error tcgetattr()");
    return false;
  }
  // Copy and apply desired settings.
  struct termios tty_config;
  memcpy(&tty_config, &_tty_state, sizeof(struct termios));

  // Until we have more test data we will have to run at the default speed.
  if (cfsetospeed(&tty_config, B57600) || cfsetispeed(&tty_config, B57600)) {
    LOG_ERR("Error cfsetospeed()");
    return false;
  }
  // Apply other misc settings
  tty_config.c_cc[VMIN] = 0;
  tty_config.c_cc[VTIME] = 0;

  tty_config.c_iflag = tty_config.c_iflag
      & ~(IXON | ISTRIP | INPCK | PARMRK | INLCR | ICRNL | BRKINT | IGNBRK);
  tty_config.c_iflag = 0;
  tty_config.c_oflag = 0;
  tty_config.c_lflag = tty_config.c_lflag
      & ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
  tty_config.c_cflag = (tty_config.c_cflag & ~(CSIZE | PARENB)) | CS8;

  if (tcsetattr(_tty_fd, TCSAFLUSH, &tty_config)) {
    LOG_ERR("Error tcsetattr()");
    return false;
  }

  return true;
}

} /* namespace PowerEFI */
