/*
 * Logging.h
 *
 *  Created on: 6 Dec 2023
 *      Author: paulhackett
 */

#ifndef LOGGING_LOGGING_H_
#define LOGGING_LOGGING_H_

#include <iostream>


namespace Pch
{

namespace Log
{

#define LOG_DEBUG(aMsg)		std::cout << aMsg << std::endl

}	// namespace Log

}	// namespace Pch

#endif // LOGGING_LOGGING_H_
