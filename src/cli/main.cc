/*
 * main.cc
 *
 *  Created on: Jan 21, 2018
 *      Author: skeys
 */


#include <iostream>

#define LOGGING_LEVEL_1  // TODO move to bazel CC flags
#include "src/lib/logging/logger.h"

using std::cout;

//static logging::logger< logging::file_log_policy > log_inst( "execution.log" );


int main() {

  LOG("Starting PowerEFI SmartFusion2 CLI loader.");
  return 0;
}

