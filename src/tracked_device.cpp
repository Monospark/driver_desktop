#include "tracked_device.h"
#include "logger.h"

TrackedDevice::TrackedDevice(const std::string& name)
    : name(name), activated(false), objectId(vr::k_unTrackedDeviceIndexInvalid) {}

TrackedDevice::~TrackedDevice() {}

void TrackedDevice::onActivate() {}

void TrackedDevice::onDeactivate() {}

void TrackedDevice::onPowerOff() {}

void TrackedDevice::update() {}

vr::EVRInitError TrackedDevice::Activate(uint32_t unObjectId) {
    objectId = unObjectId;
    activated = true;
    onActivate();
    Logger::get().log("Activated %s with id %d\n", name.c_str(), unObjectId);
    return vr::VRInitError_None;
}

void TrackedDevice::Deactivate() {
    objectId = vr::k_unTrackedDeviceIndexInvalid;
    activated = false;
    onDeactivate();
    Logger::get().log("Deactivated %s\n", name.c_str());
}

void TrackedDevice::PowerOff()
{
    onPowerOff();
    Logger::get().log("Powered off %s", name.c_str());
}

void* TrackedDevice::GetComponent(const char* pchComponentNameAndVersion)
{
    return getComponent(pchComponentNameAndVersion);
}

void TrackedDevice::DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize)
{
    Logger::get().log(pchRequest);
    if (unResponseBufferSize >= 1)
    {
        pchResponseBuffer[0] = 0;
    }
}

vr::DriverPose_t TrackedDevice::GetPose()
{
    return pose;
}

uint32_t TrackedDevice::GetStringTrackedDeviceProperty(
    vr::ETrackedDeviceProperty prop,
    char* pchValue,
    uint32_t unBufferSize,
    vr::ETrackedPropertyError* pError)
{
    *pError = vr::TrackedProp_Success;
    std::string value = getStringProperty(prop, pError);
    if (*pError == vr::TrackedProp_Success)
    {
        if (value.size() + 1 > unBufferSize)
        {
            *pError = vr::TrackedProp_BufferTooSmall;
        }
        else
        {
            strcpy_s(pchValue, unBufferSize, value.c_str());
        }
        return static_cast<uint32_t>(value.size() + 1);
    }
    return 0;
}

bool TrackedDevice::GetBoolTrackedDeviceProperty(
    vr::ETrackedDeviceProperty prop,
    vr::ETrackedPropertyError* pError)
{
    *pError = vr::TrackedProp_Success;
    return getBoolProperty(prop, pError);
}

float TrackedDevice::GetFloatTrackedDeviceProperty(
    vr::ETrackedDeviceProperty prop,
    vr::ETrackedPropertyError* pError)
{
    *pError = vr::TrackedProp_Success;
    return getFloatProperty(prop, pError);
}

int32_t TrackedDevice::GetInt32TrackedDeviceProperty(
    vr::ETrackedDeviceProperty prop,
    vr::ETrackedPropertyError* pError)
{
    *pError = vr::TrackedProp_Success;
    return getInt32Property(prop, pError);
}

uint64_t TrackedDevice::GetUint64TrackedDeviceProperty(
    vr::ETrackedDeviceProperty prop,
    vr::ETrackedPropertyError* pError)
{
    *pError = vr::TrackedProp_Success;
    return getUint64Property(prop, pError);
}

vr::HmdMatrix34_t TrackedDevice::GetMatrix34TrackedDeviceProperty(
    vr::ETrackedDeviceProperty prop,
    vr::ETrackedPropertyError* pError)
{
    *pError = vr::TrackedProp_Success;
    return getMatrix34Property(prop, pError);
}
