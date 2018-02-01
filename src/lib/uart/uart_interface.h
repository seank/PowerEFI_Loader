/* Copyright [2018] Sean Keys */

#ifndef SRC_LIB_UART_UART_INTERFACE_H_
#define SRC_LIB_UART_UART_INTERFACE_H_

#include <stdint.h>
#include <termios.h>

#include <string>

namespace PowerEFI {

using std::string;

class UARTinterface {
 public:
  UARTinterface();
  bool Init(const string& portname);
  virtual ~UARTinterface();
  bool WriteByte(const uint8_t byte);
  bool ReadByte(uint8_t* byte, uint32_t timeout_usec);
  bool WriteFile(uint8_t *file, size_t len, int32_t *bytesProcessed);
  bool ReadFile();
 protected:
  int _tty_fd;
  struct termios _tty_state;
};

} /* namespace PowerEFI */

#endif /* SRC_LIB_UART_UART_INTERFACE_H_ */
