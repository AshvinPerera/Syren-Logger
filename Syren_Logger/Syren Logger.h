#ifdef SYRENLOGGER_EXPORTS
#define SYRENLOGGER_API __declspec(dllexport)
#else
#define SYRENLOGGER_API __declspec(dllimport)
#endif

#include <string>
#include <vector>
#include <memory>

#include "console_colour_sink.h"
#include "console_sink.h"
#include "file_sink.h"

class SYRENLOGGER_API Logger {
	//Class used to create and get registered sinks (Interface to interact with sinks)
private:
	struct SinkEntry {
		// struct that represents a stored sink in the sink registry by sink name and a pointer to the sink
	private:
		std::string sink_name; // unique name of the sink
		std::shared_ptr<BaseSink> sink_ptr; // a pointer to the created sink stored as a pointer to the base class

	public:
		template <typename T>
		SinkEntry(const char* name, std::shared_ptr<T> init_ptr) {
			// constructs a sink entry that stores the name and pointer variables
			sink_name = std::string(name);
			sink_ptr = init_ptr;
		}

		std::shared_ptr<BaseSink> get_sink() {
			// gets the pointer to the stored sink in this entry
			return(sink_ptr);
		}

		std::string get_name() {
			// gets the name of the sink storedin this entry
			return(sink_name);
		}
	};

	std::vector<SinkEntry> sink_database; // database of created sinks (each entry is of type SinkEntry)

public:
	Logger() {}
	Logger(const Logger& log) {}

	void create_console_sink(const char* sink_name) {
		// dynamically creates a console sink and stores it in the registry if the sinks name is unique
		if (!sink_exists(sink_name)) {
			std::shared_ptr<ConsoleSink> console(new ConsoleSink(sink_name));
			sink_database.push_back(SinkEntry(sink_name, std::move(console)));
		}
	}

	void create_console_colour_sink(const char* sink_name) {
		// dynamically creates a console colour sink and stores it in the registry if the sinks name is unique
		if (!sink_exists(sink_name)) {
			std::shared_ptr<ConsoleColourSink> console(new ConsoleColourSink(sink_name));
			sink_database.push_back(SinkEntry(sink_name, std::move(console)));
		}
	}

	void create_file_sink(const char* sink_name, const char* file_name) {
		// dynamically creates a file sink and stores it in the registry if the sinks name is unique
		if (!sink_exists(sink_name)) {
			std::shared_ptr<FileSink> console(new FileSink(sink_name, file_name));
			sink_database.push_back(SinkEntry(sink_name, std::move(console)));
		}
	}

	std::shared_ptr<BaseSink> get_sink(const char* sink_name) {
		// returns a pointer to the named sink if the sink exists in the resgitry (base class pointer) 
		if (sink_exists(sink_name))
		{
			return(get_sink_ptr(sink_name));
		}

		return(nullptr);
	}

private:
	bool sink_exists(const char* name) {
		// checks the registry to see of the sink exists
		if (!sink_database.empty()) {
			for (SinkEntry registered : sink_database) {
				if (registered.get_name().compare(std::string(name)) == 0) {
					return(true);
				}
			}
		}
		return(false);
	}

	std::shared_ptr<BaseSink> get_sink_ptr(const char* name) {
		// returns a pointer to the base class of the required sink if the sink exists, otherwise returns nullptr
		if (!sink_database.empty()) {
			for (SinkEntry registered : sink_database) {
				if (registered.get_name().compare(std::string(name)) == 0) {
					return(registered.get_sink());
				}
			}
		}

		return(nullptr);
	}

};