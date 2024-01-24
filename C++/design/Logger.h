#pragma once
#include "../header.h"

class ILogger {
public:
    virtual void SetConfig() = 0;

    virtual void verbose(string log) = 0;
    virtual void debug(string log) = 0;
    virtual void warn(string log) = 0;
    virtual void error(string log) = 0;
};

class IFormatter {
public:
    virtual string format(string log) = 0;
};

class Formatter : public IFormatter {
    string filename, functionname, lineno, loglevel;
public:
    Formatter(string filname, string functionname, string lineno, string loglevel) {
        this->filename = filename;
        this->functionname = functionname;
        this->lineno = lineno;
        this->loglevel = loglevel;
    }
    string format(string log) override {
        stringstream ss;
        ss << setw(16) << filename;
        ss << setw(16) << functionname << ":" << lineno;
        ss << setw(16) << loglevel << "::";
        ss << log << endl;

        return ss.str();
    }
};

class Logger : public ILogger {
private:
    ostream& out;
    string fileName;
    string className;
    Formatter formatter;

    Logger() : className("Default"), out(std::cout) {}
    Logger(string className) : className(className), out(std::cout) {}
    Logger(string className, ostream& out) : className(className), out(out) {}

public:
    static Logger* GetLogger() {
        static Logger* logger = new Logger();

        return logger;
    }

    static Logger* GetLogger(string className) {
        static Logger* logger = new Logger(className);

        return logger;
    }

    static Logger* GetLogger(string className, ostream& out) {
        static Logger* logger = new Logger(className, out);

        return logger;
    }

    void SetConfig() override {
        // implement me
    }

    void verbose(string log) override {
        out << formatter.format(log) << endl;
    }

    void debug(string log) override {
        out << formatter.format(log) << endl;
    }

    void warn(string log) override {
        out << formatter.format(log) << endl;
    }

    void error(string log) override {
        out << formatter.format(log) << endl;
    }
};

#define Verbose(msg) verbose(__FILE__,__FUNCDNAME__,__LINE__,msg)

class LoggerClient {
public:
    static void test() {
        ILogger* log = Logger::GetLogger("Default", std::cout);
        log->verbose(Format());
        log->debug("Debug log");
        log->warn("Warn log");
        log->error("Error log");

        Log(Debug) << "x";
    }
};