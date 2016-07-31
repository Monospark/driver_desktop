#pragma once

#include <openvr_driver.h>
#include "tracked_device.h"

class HmdMock final : public TrackedDevice, public vr::IVRDisplayComponent
{
public:
    HmdMock(vr::IServerDriverHost* driverHost);

protected:
    bool getBoolProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) override;
    float getFloatProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) override;
    int32_t getInt32Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) override;
    uint64_t getUint64Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) override;
    std::string getStringProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) override;
    vr::HmdMatrix34_t getMatrix34Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) override;

    void* getComponent(const std::string& identifier) override;

private:
    void GetWindowBounds(int32_t* pnX, int32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) override;
    bool IsDisplayOnDesktop() override;
    bool IsDisplayRealDisplay() override;
    void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) override;
    void GetEyeOutputViewport(vr::EVREye eEye, uint32_t* pnX, uint32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) override;
    void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) override;
    vr::DistortionCoordinates_t ComputeDistortion(vr::EVREye eEye, float fU, float fV) override;

    std::string serialNumber;
    std::string modelNumber;
    int32_t windowX;
    int32_t windowY;
    int32_t windowWidth;
    int32_t windowHeight;
    int32_t renderWidth;
    int32_t renderHeight;
    float secondsFromVsyncToPhotons;
    float displayFrequency;
    float ipd;
};
