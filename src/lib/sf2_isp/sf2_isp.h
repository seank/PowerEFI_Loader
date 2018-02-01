/*
 * SF2_isp.h
 *
 *  Created on: Jan 31, 2018
 *      Author: skeys
 */

#ifndef SRC_LIB_SF2_ISP_SF2_ISP_H_
#define SRC_LIB_SF2_ISP_SF2_ISP_H_

#include "src/lib/uart/uart_interface.h"

#define BOOL (uint8_t)
#define DWORD (int64_t)

namespace PowerEFI {

typedef enum ISPmode : unsigned char {
  authenticate = 0,
  program = 1,
  verify = 2
}ISPmode;


class SF2isp {
 public:
  SF2isp();
  virtual ~SF2isp();
  bool load(ISPmode Action_code, UARTinterface *uart_interface, string&
      file_name);
};

} /* namespace PowerEFI */

#endif /* SRC_LIB_SF2_ISP_SF2_ISP_H_ */
