/*
 * logger.h
 *
 *  Created on: Jan 21, 2018
 *      Author: skeys
 */

#ifndef SRC_LIB_LOGGING_LOGGER_H_
#define SRC_LIB_LOGGING_LOGGER_H_


#include "log-impl.h"

extern logging::logger< logging::file_log_policy > log_inst;

#ifdef LOGGING_LEVEL_1
#define LOG log_inst.print< logging::severity_type::debug >
#define LOG_ERR log_inst.print< logging::severity_type::error >
#define LOG_WARN log_inst.print< logging::severity_type::warning >
#else
#define LOG(...)
#define LOG_ERR(...)
#define LOG_WARN(...)
#endif

#ifdef LOGGING_LEVEL_2
#define ELOG log_inst.print< logging::severity_type::debug >
#define ELOG_ERR log_inst.print< logging::severity_type::error >
#define ELOG_WARN log_inst.print< logging::severity_type::warning >
#else
#define ELOG(...)
#define ELOG_ERR(...)
#define ELOG_WARN(...)
#endif


#endif /* SRC_LIB_LOGGING_LOGGER_H_ */
