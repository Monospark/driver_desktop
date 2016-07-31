#include <openvr_driver.h>
#include "client_driver.h"
#include "server_driver.h"

#define HMD_DLL_EXPORT extern "C" __declspec( dllexport )

ClientDriver clientDriver;
ServerDriver serverDriver;

HMD_DLL_EXPORT void* HmdDriverFactory(const char* pInterfaceName, int* pReturnCode)
{
    if (0 == strcmp(vr::IServerTrackedDeviceProvider_Version, pInterfaceName))
    {
        return &serverDriver;
    }
    if (0 == strcmp(vr::IClientTrackedDeviceProvider_Version, pInterfaceName))
    {
        return &clientDriver;
    }

    if (pReturnCode)
    {
        *pReturnCode = vr::VRInitError_Init_InterfaceNotFound;
    }

    return nullptr;
}
