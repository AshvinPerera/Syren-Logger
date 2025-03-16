#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "common.h"
#include "base_sink.h"


class FileSink : public BaseSink
	// logs messages to a file
{
private:
	std::ofstream outdata; // file to log messages to

public:
	FileSink(const char* uniqueid, const char* file_name, const char* file_path = "", bool should_overwrite = false) : BaseSink(uniqueid) {
		// constructor used to set default formatter properties and opens the required file
		open_file(file_name, file_path, should_overwrite);
	}

	FileSink(const char* uniqueid, const char* file_name, const char* file_path, bool should_overwrite, LogLevel priority_level,
		std::string string_format, const unsigned init_decimal_places, bool init_precision)
		: BaseSink(uniqueid, priority_level, string_format, init_decimal_places, init_precision) {
		// constructor used to set individual formatter properties and opens the required file
		open_file(file_name, file_path, should_overwrite);
	}

	FileSink(const char* uniqueid, const char* file_name, const char* file_path, bool should_overwrite, LogLevel priority_level,
		const char* string_format, const unsigned init_decimal_places, bool init_precision)
		: BaseSink(uniqueid, priority_level, string_format, init_decimal_places, init_precision) {
		// constructor used to set individual formatter properties and opens the required file
		open_file(file_name, file_path, should_overwrite);
	}

	~FileSink() {
		// closes file when the sink is destroyed 
		if (outdata.is_open())
			outdata.close();
	}

private:
	FileSink& operator=(FileSink other) {}

	virtual void log(std::string message, LogLevel level)
	{
		// writes message to the file
		message = message + "\n";
		if (outdata.is_open())
			outdata << message;
	}

	void open_file(const char* file_name, const char* file_path = "", bool should_overwrite = false) {
		// opens the required file based on the file path and file name and sets the file to be overwritten if required
		std::string complete_file_name = std::string(file_path) + std::string(file_name);
		if (should_overwrite)
			outdata.open(complete_file_name.c_str(), std::ofstream::out | std::ofstream::trunc);
		else
			outdata.open(complete_file_name.c_str(), std::ofstream::out | std::ofstream::app);
	}

};



