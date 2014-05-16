#ifndef KINECT_VIEWER_H
#define KINECT_VIEWER_H

#include "defs.h"
#include "utils.h"
#include "depth_map.h"

#include "OpenNI.h"

#include <memory>
#include <functional>

BEGIN_KINECT_NAMESPACE

typedef std::function<void(depth_map_t&)> depth_callback_t;

class video_streamer_t
{
public:
    explicit video_streamer_t(command_queue_t& command_queue);

    vector2_t get_window_size();

    void set_depth_callback(depth_callback_t&& func);

    void loop();

private:
    depth_callback_t _callback;
    command_queue_t& _command_queue;
    openni::VideoStream _video_stream;
};

END_KINECT_NAMESPACE

#endif // VIEWER_H
