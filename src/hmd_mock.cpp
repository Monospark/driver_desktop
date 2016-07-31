#include "hmd_mock.h"

#include "settings.hpp"
#include "logger.h"

using namespace Settings;

namespace
{
const std::string SECTION = "driver_desktop";

const std::string SERIAL_NUMBER("serialNumber");
const std::string MODEL_NUMBER("modelNumber");
const std::string WINDOW_X("windowX");
const std::string WINDOW_Y("windowY");
const std::string WINDOW_WIDTH("windowWidth");
const std::string WINDOW_HEIGHT("windowHeight");
const std::string RENDER_WIDTH("renderWidth");
const std::string RENDER_HEIGHT("windowHeight");
const std::string VSYNC_TO_PHOTONS("secondsFromVsyncToPhotons");
const std::string DISPLAY_FREQUENCY("displayFrequency");
}

HmdMock::HmdMock(vr::IServerDriverHost* driverHost)
    : TrackedDevice("hmd mock")
{
    vr::IVRSettings* s = driverHost->GetSettings(vr::IVRSettings_Version);
    ipd = FloatEntry(SECTION, vr::k_pch_SteamVR_IPD_Float, 0.065f).parseValue(s);
    serialNumber = StringEntry(SECTION, SERIAL_NUMBER, "").parseValue(s);
    modelNumber = StringEntry(SECTION, MODEL_NUMBER, "").parseValue(s);
    windowX = IntEntry(SECTION, WINDOW_X, 0).parseValue(s);
    windowY = IntEntry(SECTION, WINDOW_Y, 0).parseValue(s);
    windowWidth = IntEntry(SECTION, WINDOW_WIDTH, 800).parseValue(s);
    windowHeight = IntEntry(SECTION, WINDOW_HEIGHT, 600).parseValue(s);
    renderWidth = IntEntry(SECTION, RENDER_WIDTH, 800).parseValue(s);
    renderHeight = IntEntry(SECTION, RENDER_HEIGHT, 600).parseValue(s);
    secondsFromVsyncToPhotons = FloatEntry(SECTION, VSYNC_TO_PHOTONS, 0.0f).parseValue(s);
    displayFrequency = FloatEntry(SECTION, DISPLAY_FREQUENCY, 0.0f).parseValue(s);

    Logger::get().log("Loaded settings\n");
    Logger::get().log("IPD: %f\n", ipd);
    Logger::get().log("Serial number: %s\n", serialNumber.c_str());
    Logger::get().log("Seconds from vsync to photons: %f\n", secondsFromVsyncToPhotons);
    Logger::get().log("Display frequency: %f\n", displayFrequency);
    
    pose = {};
    pose.poseIsValid = true;
    pose.result = vr::TrackingResult_Running_OK;
    pose.deviceIsConnected = true;
    pose.qWorldFromDriverRotation = vr::HmdQuaternion_t{ 1, 0, 0, 0 };
    pose.qDriverFromHeadRotation = vr::HmdQuaternion_t{ 1, 0, 0, 0 };
}

void* HmdMock::getComponent(const std::string& identifier)
{
    if (0 == _stricmp(identifier.c_str(), vr::IVRDisplayComponent_Version))
    {
        return static_cast<vr::IVRDisplayComponent*>(this);
    }

    return nullptr;
}

bool HmdMock::getBoolProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError)
{
    switch (prop)
    {
    case vr::Prop_IsOnDesktop_Bool:
        return true;
    }

    *pError = vr::TrackedProp_ValueNotProvidedByDevice;
    return false;
}

float HmdMock::getFloatProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError)
{
    switch (prop)
    {
    case vr::Prop_UserIpdMeters_Float:
        return ipd;

    case vr::Prop_UserHeadToEyeDepthMeters_Float:
        return 0.0f;

    case vr::Prop_DisplayFrequency_Float:
        return displayFrequency;

    case vr::Prop_SecondsFromVsyncToPhotons_Float:
        return secondsFromVsyncToPhotons;
    }

    *pError = vr::TrackedProp_ValueNotProvidedByDevice;
    return 0;
}

int32_t HmdMock::getInt32Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError)
{
    switch (prop)
    {
    case vr::Prop_DeviceClass_Int32:
        return vr::TrackedDeviceClass_HMD;
    }

    *pError = vr::TrackedProp_UnknownProperty;
    return 0;
}

uint64_t HmdMock::getUint64Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError)
{
    switch (prop)
    {
    case vr::Prop_CurrentUniverseId_Uint64:
        // return a constant that's not 0 (invalid) or 1 (reserved for Oculus)
        return 2;
    }

    *pError = vr::TrackedProp_ValueNotProvidedByDevice;
    return 0;
}

vr::HmdMatrix34_t HmdMock::getMatrix34Property(
    vr::ETrackedDeviceProperty prop,
    vr::ETrackedPropertyError* pError)
{
    vr::HmdMatrix34_t mat;
    mat.m[0][0] = 1.0f;
    mat.m[0][1] = 0.0f;
    mat.m[0][2] = 0.0f;
    mat.m[0][3] = 0.0f;
    mat.m[1][0] = 0.0f;
    mat.m[1][1] = 1.0f;
    mat.m[1][2] = 0.0f;
    mat.m[1][3] = 0.0f;
    mat.m[2][0] = 0.0f;
    mat.m[2][1] = 0.0f;
    mat.m[2][2] = 1.0f;
    mat.m[2][3] = 0.0f;
    return mat;
}

std::string HmdMock::getStringProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) {
    *pError = vr::TrackedProp_Success;
    switch (prop)
    {
    case vr::Prop_ModelNumber_String:
        return modelNumber;

    case vr::Prop_SerialNumber_String:
        return serialNumber;
    }

    *pError = vr::TrackedProp_ValueNotProvidedByDevice;
    return "";
}

void HmdMock::GetWindowBounds(int32_t* pnX, int32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight)
{
    *pnX = windowX;
    *pnY = windowY;
    *pnWidth = windowWidth;
    *pnHeight = windowHeight;
}

bool HmdMock::IsDisplayOnDesktop()
{
    return true;
}

bool HmdMock::IsDisplayRealDisplay()
{
    return false;
}

void HmdMock::GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight)
{
    *pnWidth = renderWidth;
    *pnHeight = renderHeight;
}

void HmdMock::GetEyeOutputViewport(vr::EVREye eEye, uint32_t* pnX, uint32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight)
{
    *pnY = 0;
    *pnWidth = windowWidth / 2;
    *pnHeight = windowHeight;

    if (eEye == vr::Eye_Left)
    {
        *pnX = 0;
    } else
    {
        *pnX = windowWidth / 2;
    }
}

void HmdMock::GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom)
{
    *pfLeft = -1.0;
    *pfRight = 1.0;
    *pfTop = -1.0;
    *pfBottom = 1.0;
}

vr::DistortionCoordinates_t HmdMock::ComputeDistortion(vr::EVREye eEye, float fU, float fV)
{
    vr::DistortionCoordinates_t coordinates;
    coordinates.rfBlue[0] = fU;
    coordinates.rfBlue[1] = fV;
    coordinates.rfGreen[0] = fU;
    coordinates.rfGreen[1] = fV;
    coordinates.rfRed[0] = fU;
    coordinates.rfRed[1] = fV;
    return coordinates;
}
