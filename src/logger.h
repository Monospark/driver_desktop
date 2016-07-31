#pragma once

#include <string>
#include <openvr_driver.h>
#include <memory>

class Logger final
{
public:
    static void init(vr::IDriverLog* logFile);
    static Logger get();

    Logger(vr::IDriverLog* logFile);
    void log(const std::string& msg, ...) const;

private:
    static std::unique_ptr<Logger> instance;

    vr::IDriverLog* logFile;
};
