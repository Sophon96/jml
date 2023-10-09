#include <internal/logger.hpp>
#include <iostream>
#include <string>

namespace jml {

const std::string get_severity_text(enum Severity s) {
    return severity_text[(int)s];
}

enum Severity Log::get_severity() { return this->severity; }

std::string Log::get_message() { return this->message; }

Log &Log::operator<<(enum Severity s) {
    this->severity = s;
    return *this;
}

Log &Log::operator<<(std::string m) {
    this->message += m;
    return *this;
}

Log &Log::operator<<(int m) {
    this->message += std::to_string(m);
    return *this;
}

Log::Log(enum Severity s) : severity(s) {}
Log::Log(enum Severity s, std::string m) : severity(s), message(m) {}

Logger *Logger::_instance = nullptr;
Logger *Logger::Instance(enum Severity s) {
    if (_instance == nullptr) {
        _instance = new Logger(s);
    }
    return _instance;
}

Logger::Logger(enum Severity s) { this->global_log_level = s; }

std::string Logger::render(Log l) {
    return "[" + get_severity_text(l.get_severity()) + "]: " + l.get_message();
}

void Logger::log(enum Severity s, std::string m) {
    Log l = Log(s, m);
    this->log(l);
}

void Logger::log(Log l) {
    // Print log if log level is low enough for l
    if (l.get_severity() >= this->global_log_level) {
        std::cerr << this->render(l);
    }
}

void Logger::set_global_log_level(enum Severity s) {
    this->global_log_level = s;
}

} // namespace jml
