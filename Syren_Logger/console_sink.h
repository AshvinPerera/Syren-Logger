#pragma once

#include <string>
#include <iostream>

#include "common.h"
#include "base_sink.h"


class ConsoleSink : public BaseSink
	// logs data to the console 
{
public:
	ConsoleSink(const char* uniqueid) : BaseSink(uniqueid) {} // constructor used to set default formatter properties

	ConsoleSink(const char* uniqueid, LogLevel priority_level, std::string string_format, const unsigned init_decimal_places, bool init_precision)
		: BaseSink(uniqueid, priority_level, string_format, init_decimal_places, init_precision) {}
	// constructor used to set individual formatter properties

	ConsoleSink(const char* uniqueid, LogLevel priority_level, const char* string_format, const unsigned init_decimal_places, bool init_precision)
		: BaseSink(uniqueid, priority_level, string_format, init_decimal_places, init_precision) {}
	// constructor used to set individual formatter properties

private:
	ConsoleSink& operator=(ConsoleSink other) {}

	virtual void log(std::string message, LogLevel level) {
		// prints logging message to the console 
		message = message + "\n";
		printf(message.c_str());
	}

};
