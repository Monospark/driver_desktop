#pragma once

#include <openvr_driver.h>
#include "hmd_mock.h"
#include <memory>

class ServerDriver final : public vr::IServerTrackedDeviceProvider
{
    vr::EVRInitError Init(
        vr::IDriverLog* pDriverLog,
        vr::IServerDriverHost* pDriverHost,
        const char* pchUserDriverConfigDir,
        const char* pchDriverInstallDir) override;
    void Cleanup() override;
    const char* const* GetInterfaceVersions() override;
    uint32_t GetTrackedDeviceCount() override;
    vr::ITrackedDeviceServerDriver* GetTrackedDeviceDriver(uint32_t unWhich) override;
    vr::ITrackedDeviceServerDriver* FindTrackedDeviceDriver(const char* pchId) override;
    void RunFrame() override;
    bool ShouldBlockStandbyMode() override;
    void EnterStandby() override;
    void LeaveStandby() override;

    std::unique_ptr<vr::ITrackedDeviceServerDriver> hmdMock;
};
