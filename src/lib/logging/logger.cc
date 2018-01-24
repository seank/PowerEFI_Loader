/*
 * logger.c
 *
 *  Created on: Jan 21, 2018
 *      Author: skeys
 */

#include "logger.h"

static logging::logger< logging::file_log_policy > log_inst( "execution.log" );

