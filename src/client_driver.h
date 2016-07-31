#pragma once

#include <openvr_driver.h>
#include "settings.hpp"

class ClientDriver final : public vr::IClientTrackedDeviceProvider
{
public:
    vr::EVRInitError Init(
        vr::EClientDriverMode eDriverMode,
        vr::IDriverLog* pDriverLog,
        vr::IClientDriverHost* pDriverHost,
        const char* pchUserDriverConfigDir,
        const char* pchDriverInstallDir) override;
    void Cleanup() override;
    bool BIsHmdPresent(const char* pchUserDriverConfigDir) override;
    vr::EVRInitError SetDisplayId(const char* pchDisplayId) override;
    vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye) override;
    uint32_t GetMCImage(
        uint32_t* pImgWidth,
        uint32_t* pImgHeight,
        uint32_t* pChannels,
        void* pDataBuffer,
        uint32_t unBufferLen) override;

private:
    vr::IClientDriverHost* clientDriverHost;
};
