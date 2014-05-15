#ifndef KINECT_VIEWER_H
#define KINECT_VIEWER_H

#  include "defs.h"
#  include "depth_map.h"

#  include "OpenNI.h"

#  include <functional>

BEGIN_KINECT_NAMESPACE

typedef std::function<void(depth_map_t&&)> viewer_callback_t;

class viewer_t
{
public:
    explicit viewer_t(command_queue_t* command_queue);

    void set_callback(viewer_callback_t&& func);

    void loop();

private:
    viewer_callback_t _callback;
    command_queue_t* _command_queue;
    openni::VideoStream _video_stream;
};

END_KINECT_NAMESPACE

#endif // VIEWER_H
