#ifndef SDR_HOST_BASE_IMPL_BASE_H
#define SDR_HOST_BASE_IMPL_BASE_H

#include <boost/thread.hpp>
#include <ossie/Component.h>
#include <ossie/ThreadedComponent.h>


class SDR_Host_base : public Component, protected ThreadedComponent
{
    public:
        SDR_Host_base(const char *uuid, const char *label);
        ~SDR_Host_base();

        void start() throw (CF::Resource::StartError, CORBA::SystemException);

        void stop() throw (CF::Resource::StopError, CORBA::SystemException);

        void releaseObject() throw (CF::LifeCycle::ReleaseError, CORBA::SystemException);

        void loadProperties();

    protected:

    private:
};
#endif // SDR_HOST_BASE_IMPL_BASE_H
