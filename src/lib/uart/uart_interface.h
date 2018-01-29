/* Copyright [2018] Sean Keys */

#ifndef SRC_LIB_UART_UART_INTERFACE_H_
#define SRC_LIB_UART_UART_INTERFACE_H_

#include <termios.h>

#include <string>

namespace PowerEFI {

using std::string;

class UARTinterface {
 public:
  UARTinterface();
  bool Init(const string& portname);
  virtual ~UARTinterface();
 protected:
  int _tty_fd;
  struct termios _tty_state;
};

} /* namespace PowerEFI */

#endif /* SRC_LIB_UART_UART_INTERFACE_H_ */
