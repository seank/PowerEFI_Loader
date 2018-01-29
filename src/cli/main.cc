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
  string path = "/bad/path";
  uart_if.Init(path);

  return 0;
}

