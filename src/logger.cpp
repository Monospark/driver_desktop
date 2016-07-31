#include "logger.h"

#include <stdarg.h>

std::unique_ptr<Logger> Logger::instance;

void Logger::init(vr::IDriverLog* logFile)
{
    instance = std::make_unique<Logger>(logFile);
}

Logger Logger::get()
{
    if (!instance)
    {
        throw std::runtime_error("Logger has not been initialized");
    }

    return *instance;
}

Logger::Logger(vr::IDriverLog* logFile) : logFile(logFile) {}

void Logger::log(const std::string& msg, ...) const
{
#ifdef _DEBUG
    va_list args;
    va_start(args, msg);

    char buf[1024];
    vsprintf_s(buf, msg.c_str(), args);
    instance->logFile->Log(buf);

    va_end(args);
#endif
}
