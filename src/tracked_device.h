#pragma once

#include <openvr_driver.h>
#include <string>
#include <vector>

class TrackedDevice : public vr::ITrackedDeviceServerDriver
{
public:
    TrackedDevice(const std::string& name);
    virtual ~TrackedDevice();

protected:
    virtual bool getBoolProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) = 0;
    virtual float getFloatProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) = 0;
    virtual int32_t getInt32Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) = 0;
    virtual uint64_t getUint64Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) = 0;
    virtual std::string getStringProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) = 0;
    virtual vr::HmdMatrix34_t getMatrix34Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) = 0;
    virtual void* getComponent(const std::string& identifier) = 0;

    virtual void onActivate();
    virtual void onDeactivate();
    virtual void onPowerOff();
    virtual void update();

    vr::DriverPose_t pose;

private:
    vr::EVRInitError Activate(uint32_t unObjectId) override;
    void Deactivate() override;
    void PowerOff() override;
    void* GetComponent(const char* pchComponentNameAndVersion) override;
    void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) override;
    vr::DriverPose_t GetPose() override;

    uint32_t GetStringTrackedDeviceProperty(
        vr::ETrackedDeviceProperty prop,
        char * pchValue,
        uint32_t unBufferSize,
        vr::ETrackedPropertyError * pError) override;
    bool GetBoolTrackedDeviceProperty(
        vr::ETrackedDeviceProperty prop,
        vr::ETrackedPropertyError *pError) override;
    float GetFloatTrackedDeviceProperty(
        vr::ETrackedDeviceProperty prop,
        vr::ETrackedPropertyError * pError) override;
    int32_t GetInt32TrackedDeviceProperty(
        vr::ETrackedDeviceProperty prop,
        vr::ETrackedPropertyError * pError) override;
    uint64_t GetUint64TrackedDeviceProperty(
        vr::ETrackedDeviceProperty prop,
        vr::ETrackedPropertyError * pError) override;
    vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(
        vr::ETrackedDeviceProperty prop,
        vr::ETrackedPropertyError * pError) override;

    const std::string name;
    bool activated;
    uint32_t objectId;
};
