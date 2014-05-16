#ifndef KINECT_LOOP_CONTROLLER_INTERFACE_H
#define KINECT_LOOP_CONTROLLER_INTERFACE_H

#include "defs.h"

BEGIN_KINECT_NAMESPACE

class loop_controller_interface
{
public:
    virtual ~loop_controller_interface() { }

    virtual void set_frequency(float) = 0;
    virtual void start_looping(std::function<void()> const&) = 0;
};

END_KINECT_NAMESPACE

#endif // LOOP_CONTROLLER_INTERFACE_H
