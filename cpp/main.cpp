#include <iostream>
#include "ossie/ossieSupport.h"

#include "SDR_Host.h"
int main(int argc, char* argv[])
{
    SDR_Host_i* SDR_Host_servant;
    Component::start_component(SDR_Host_servant, argc, argv);
    return 0;
}

