#include "SDR_Host_base.h"

/*******************************************************************************************

    AUTO-GENERATED CODE. DO NOT MODIFY

    The following class functions are for the base class for the component class. To
    customize any of these functions, do not modify them here. Instead, overload them
    on the child class

******************************************************************************************/

SDR_Host_base::SDR_Host_base(const char *uuid, const char *label) :
    Component(uuid, label),
    ThreadedComponent()
{

    loadProperties();
}

SDR_Host_base::~SDR_Host_base()
{
}

/*******************************************************************************************
    Framework-level functions
    These functions are generally called by the framework to perform housekeeping.
*******************************************************************************************/
void SDR_Host_base::start() throw (CORBA::SystemException, CF::Resource::StartError)
{
    Component::start();
    ThreadedComponent::startThread();
}

void SDR_Host_base::stop() throw (CORBA::SystemException, CF::Resource::StopError)
{
    Component::stop();
    if (!ThreadedComponent::stopThread()) {
        throw CF::Resource::StopError(CF::CF_NOTSET, "Processing thread did not die");
    }
}

void SDR_Host_base::releaseObject() throw (CORBA::SystemException, CF::LifeCycle::ReleaseError)
{
    // This function clears the component running condition so main shuts down everything
    try {
        stop();
    } catch (CF::Resource::StopError& ex) {
        // TODO - this should probably be logged instead of ignored
    }

    Component::releaseObject();
}

void SDR_Host_base::loadProperties()
{
}



