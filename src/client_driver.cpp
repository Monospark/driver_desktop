#include "client_driver.h"
#include <vector>
#include "logger.h"

vr::EVRInitError ClientDriver::Init(
    vr::EClientDriverMode eDriverMode,
    vr::IDriverLog* pDriverLog,
    vr::IClientDriverHost* pDriverHost,
    const char* pchUserDriverConfigDir,
    const char* pchDriverInstallDir)
{
    clientDriverHost = pDriverHost;
    Logger::init(pDriverLog);
    Logger::get().log("Starting up client driver\n");
    return vr::VRInitError_None;
}

void ClientDriver::Cleanup() {}

bool ClientDriver::BIsHmdPresent(const char* pchUserDriverConfigDir)
{
    return true;
}

vr::EVRInitError ClientDriver::SetDisplayId(const char* pchDisplayId)
{
    return vr::VRInitError_None;
}

vr::HiddenAreaMesh_t ClientDriver::GetHiddenAreaMesh(vr::EVREye eEye)
{
    vr::HiddenAreaMesh_t mesh;
    mesh.pVertexData = nullptr;
    mesh.unTriangleCount = 0;
    return mesh;
}

uint32_t ClientDriver::GetMCImage(
    uint32_t* pImgWidth,
    uint32_t* pImgHeight,
    uint32_t* pChannels,
    void* pDataBuffer,
    uint32_t unBufferLen)
{
    return 0;
}
