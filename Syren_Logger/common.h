#pragma once


enum class LogLevel { LTRACE = 0, LDEBUG = 1, LINFO = 2, LWARNING = 3, LERROR = 4, LFATAL = 5 }; // list of logging levels
enum class TimeZone { UTC = 0, COLOMBO = 2 }; // list of usable time zones when formatting strings
enum class Colour { DEFAULT, WHITE, BLUE, CYAN, RED, GREEN, YELLOW }; // list of colours that can be set by colour sinks

