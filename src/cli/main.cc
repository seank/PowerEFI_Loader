/*
 * main.cc
 *
 *  Created on: Jan 21, 2018
 *      Author: skeys
 */


#include <iostream>

#define LOGGING_LEVEL_1  // TODO move to bazel CC flags
#include "src/lib/logging/logger.h"
#include "src/lib/uart/uart_interface.h"
using std::cout;
using std::string;

//static logging::logger< logging::file_log_policy > log_inst( "execution.log" );


int main() {

  LOG("Starting PowerEFI SmartFusion2 CLI loader.");

  PowerEFI::UARTinterface uart_if;
  string path = "/dev/ttyUSB0";
  uart_if.Init(path);

  for (int i = 0; i < 100; ++i) {
    uart_if.WriteByte('h');
    uint8_t b;
    uart_if.ReadByte(&b, 2000001);
    std::cout << "read " << b << std::endl;
  }


  return 0;
}

