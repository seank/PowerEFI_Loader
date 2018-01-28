/*
 * logger.c
 *
 *  Created on: Jan 21, 2018
 *      Author: skeys
 */

#include "log-impl.h"

#include <cstring>

using namespace logging;

void file_log_policy::open_ostream(const std::string& name) {
  out_stream->open(name.c_str(), std::ios_base::binary | std::ios_base::out);
  if (!out_stream->is_open()) {
    throw(std::runtime_error("LOGGER: Unable to open an output stream"));
  }
}

void file_log_policy::close_ostream() {
  if (out_stream) {
    out_stream->close();
  }
}

void file_log_policy::write(const std::string& msg) {
  std::string log_msg = msg;
  // Add system call error details.
  if (errno != 0) {
    std::string sys_msg = strerror(errno);
    errno = 0;
    log_msg += " Error info: ";
    log_msg += sys_msg;
  }

  (*out_stream) << log_msg << std::endl;
    std::cout << log_msg << std::endl;
}

file_log_policy::~file_log_policy() {
  if (out_stream) {
    close_ostream();
  }
}


logging::logger< logging::file_log_policy > log_inst( "execution.log" );
