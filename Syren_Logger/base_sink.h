#pragma once

#include <memory>
#include <string>
#include <mutex>
#include <iostream>

#include <windows.h>

// check and define operating system to select class features that are platform dependent

#if defined(_WIN32) || defined(_WIN64)
#define WINDOWS 1
#define LINUX 0
#define UNKNOWN 0
#else
#ifdef __linux
#define WINDOWS 0
#define LINUX 1
#define UNKNOWN 0
#else
#define WINDOWS 0
#define LINUX 0
#define UNKNOWN 1
#endif
#endif

#include "common.h"
#include "str_fmt.h"


class BaseSink {
	// abstract base class that defines the basic interface and functionality of a sink
private:
	std::unique_ptr<StringFormat> string_formatter; // pointer that stores a unique instance of a string formatter
	LogLevel local_priority; // priority level of the sink (defaults to TRACE)
	const char* sink_name; // unique name of the sink			
	std::mutex sink_mutex; // mutex to lock a function call for thread safety

protected:
	enum class OperatingSystem { Windows, Linux, Unknown }; // list of operating systems
	OperatingSystem operating_system; // current operating system used by the derived class

public:
	BaseSink(const char* uniqueid)
		: sink_name(uniqueid) {
		// constructor used to set default formatter properties
		local_priority = LogLevel::LTRACE;
		string_formatter = std::unique_ptr<StringFormat>(new StringFormat());
		set_operating_system();
	}

	BaseSink(const char* uniqueid, LogLevel priority_level, std::string string_format, const unsigned init_decimal_places, bool init_precision)
		: local_priority(priority_level), sink_name(uniqueid) {
		// constructor used to set individual formatter properties
		string_formatter = std::unique_ptr<StringFormat>(new StringFormat(string_format, init_decimal_places, init_precision));
		set_operating_system();
	}

	BaseSink(const char* uniqueid, LogLevel priority_level, const char* string_format, const unsigned init_decimal_places, bool init_precision)
		: local_priority(priority_level), sink_name(uniqueid) {
		// constructor used to set individual formatter properties
		string_formatter = std::unique_ptr<StringFormat>(new StringFormat(string_format, init_decimal_places, init_precision));
		set_operating_system();
	}

	template<typename T, typename... Args>
	void Trace(const char* input_message, T t, Args... args) {
		// writes a thread safe TRACE priority message to sink (positional formatting version)
		if (LogLevel::LTRACE >= local_priority) {
			std::scoped_lock lock(sink_mutex);
			std::string message = string_formatter->format(sink_name, LogLevel::LTRACE, input_message, t, args...);
			log(message, LogLevel::LTRACE);
		}
	}

	void Trace(const char* input_message) {
		// writes a thread safe TRACE priority message to sink
		if (LogLevel::LTRACE >= local_priority) {
			std::scoped_lock lock(sink_mutex);
			std::string message = string_formatter->format(sink_name, LogLevel::LTRACE, input_message);
			log(message, LogLevel::LTRACE);
		}
	}

	template<typename T, typename... Args>
	void Debug(const char* input_message, T t, Args... args) {
		// writes a thread safe DEBUG priority message to sink (positional formatting version)
		if (LogLevel::LDEBUG >= local_priority) {
			std::scoped_lock lock(sink_mutex);
			std::string message = string_formatter->format(sink_name, LogLevel::LDEBUG, input_message, t, args...);
			log(message, LogLevel::LDEBUG);
		}
	}

	void Debug(const char* input_message) {
		// writes a thread safe DEBUG priority message to sink
		if (LogLevel::LDEBUG >= local_priority) {
			std::scoped_lock lock(sink_mutex);
			std::string message = string_formatter->format(sink_name, LogLevel::LDEBUG, input_message);
			log(message, LogLevel::LDEBUG);
		}
	}

	template<typename T, typename... Args>
	void Info(const char* input_message, T t, Args... args) {
		// writes a thread safe INFO priority message to sink (positional formatting version)
		if (LogLevel::LINFO >= local_priority) {
			std::scoped_lock lock(sink_mutex);
			std::string message = string_formatter->format(sink_name, LogLevel::LINFO, input_message, t, args...);
			log(message, LogLevel::LINFO);
		}
	}

	void Info(const char* input_message) {
		// writes a thread safe INFO priority message to sink
		if (LogLevel::LINFO >= local_priority) {
			std::scoped_lock lock(sink_mutex);
			std::string message = string_formatter->format(sink_name, LogLevel::LINFO, input_message);
			log(message, LogLevel::LINFO);
		}
	}

	template<typename T, typename... Args>
	void Warning(const char* input_message, T t, Args... args) {
		// writes a thread safe WARNING priority message to sink (positional formatting version)
		if (LogLevel::LWARNING >= local_priority) {
			std::scoped_lock lock(sink_mutex);
			std::string message = string_formatter->format(sink_name, LogLevel::LWARNING, input_message, t, args...);
			log(message, LogLevel::LWARNING);
		}
	}

	void Warning(const char* input_message) {
		// writes a thread safe WARNING priority message to sink 
		if (LogLevel::LWARNING >= local_priority) {
			std::scoped_lock lock(sink_mutex);
			std::string message = string_formatter->format(sink_name, LogLevel::LWARNING, input_message);
			log(message, LogLevel::LWARNING);
		}
	}

	template<typename T, typename... Args>
	void Error(const char* input_message, T t, Args... args) {
		// writes a thread safe ERROR priority message to sink (positional formatting version)
		if (LogLevel::LERROR >= local_priority) {
			std::scoped_lock lock(sink_mutex);
			std::string message = string_formatter->format(sink_name, LogLevel::LERROR, input_message, t, args...);
			log(message, LogLevel::LERROR);
		}
	}

	void Error(const char* input_message) {
		// writes a thread safe ERROR priority message to sink
		if (LogLevel::LERROR >= local_priority) {
			std::scoped_lock lock(sink_mutex);
			std::string message = string_formatter->format(sink_name, LogLevel::LERROR, input_message);
			log(message, LogLevel::LERROR);
		}
	}

	template<typename T, typename... Args>
	void Fatal(const char* input_message, T t, Args... args) {
		// writes a thread safe FATAL priority message to sink (positional formatting version)
		if (LogLevel::LFATAL >= local_priority) {
			std::scoped_lock lock(sink_mutex);
			std::string message = string_formatter->format(sink_name, LogLevel::LFATAL, input_message, t, args...);
			log(message, LogLevel::LFATAL);
		}
	}

	void Fatal(const char* input_message) {
		// writes a thread safe FATAL priority message to sink 
		if (LogLevel::LFATAL >= local_priority) {
			std::scoped_lock lock(sink_mutex);
			std::string message = string_formatter->format(sink_name, LogLevel::LFATAL, input_message);
			log(message, LogLevel::LFATAL);
		}
	}

	void set_formatting_properties(std::string output_format, unsigned decimal_places, bool set_precision, TimeZone time_zone) {
		// changes the string formatters properties
		string_formatter->set_string_format(output_format);
		if (set_precision) {
			string_formatter->enable_precision();
			string_formatter->set_decimal_places(decimal_places);
		}
		else
			string_formatter->disable_precision();

		string_formatter->set_time_zone(time_zone);

	}

	void set_formatting_properties(const char* output_format, unsigned decimal_places, bool set_precision, TimeZone time_zone) {
		// changes the string formatters properties
		string_formatter->set_string_format(output_format);
		if (set_precision) {
			string_formatter->enable_precision();
			string_formatter->set_decimal_places(decimal_places);
		}
		else
			string_formatter->disable_precision();

		string_formatter->set_time_zone(time_zone);
	}


	void set_log_priority(LogLevel new_level) {
		// changes the logging priority level if this sink
		local_priority = new_level;
	}

private:
	virtual void log(std::string message, LogLevel level) = 0; // pure virtual function that defines the logging functionality 
	void set_operating_system() {
		// set operating system based on macro value
		if (WINDOWS == 1) {
			operating_system = OperatingSystem::Windows;
		}
		else if (LINUX == 1) {
			operating_system = OperatingSystem::Linux;
		}
		else {
			operating_system = OperatingSystem::Unknown;
		}
	}
};
