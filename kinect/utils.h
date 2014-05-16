#ifndef KINECT_UTILS_H
#define KINECT_UTILS_H

#  include "defs.h"

BEGIN_KINECT_NAMESPACE

struct vector2_t
{
    float x;
    float y;
};

struct vector3_t
{
    float x;
    float y;
    float z;
};

command_t wrap_exception(std::exception_ptr&& excep);

END_KINECT_NAMESPACE

#endif // UTILS_H
