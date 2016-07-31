#include "server_driver.h"
#include "logger.h"

vr::EVRInitError ServerDriver::Init(
    vr::IDriverLog* pDriverLog,
    vr::IServerDriverHost* pDriverHost,
    const char* pchUserDriverConfigDir,
    const char* pchDriverInstallDir)
{
    Logger::init(pDriverLog);
    hmdMock = std::make_unique<HmdMock>(pDriverHost);
    Logger::get().log("Starting up driver server\n");
    return vr::VRInitError_None;
}

void ServerDriver::Cleanup()
{
    Logger::get().log("Shutting down driver server\n");
    hmdMock.reset();
}

const char* const* ServerDriver::GetInterfaceVersions()
{
    return vr::k_InterfaceVersions;
}

uint32_t ServerDriver::GetTrackedDeviceCount()
{
    return 1;
}

vr::ITrackedDeviceServerDriver* ServerDriver::GetTrackedDeviceDriver(uint32_t unWhich)
{
    return hmdMock.get();
}

vr::ITrackedDeviceServerDriver* ServerDriver::FindTrackedDeviceDriver(const char* pchId)
{
    return hmdMock.get();
}

void ServerDriver::RunFrame()
{
    
}

bool ServerDriver::ShouldBlockStandbyMode()
{
    return false;
}

void ServerDriver::EnterStandby() {}

void ServerDriver::LeaveStandby() {}
