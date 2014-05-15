#  include "utils.h"

BEGIN_KINECT_NAMESPACE

command_t wrap_exception(std::exception_ptr&& excep)
{
    return command_t([excep](){if(excep) std::rethrow_exception(excep);});
}

END_KINECT_NAMESPACE
