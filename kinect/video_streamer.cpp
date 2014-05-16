#include "video_streamer.h"

#include <stdexcept>

BEGIN_KINECT_NAMESPACE

video_streamer_t::video_streamer_t(command_queue_t &command_queue)
    : _command_queue(command_queue)
{
    openni::Device device;
    auto status = device.open(openni::ANY_DEVICE);
    if(status != openni::STATUS_OK) throw std::runtime_error("Viewer exception. Can't open device.");

    status = _video_stream.create(device, openni::SENSOR_DEPTH);
    if(status != openni::STATUS_OK) throw std::runtime_error("Viewer exception. Can't create depth video stream.");
}

vector2_t video_streamer_t::get_window_size()
{

    auto video_mode = _video_stream.getVideoMode();

    return {(float)video_mode.getResolutionX(), (float)video_mode.getResolutionY()};
}

void video_streamer_t::set_depth_callback(depth_callback_t&& func)
{
    _callback = func;
}

void video_streamer_t::loop()
{
    if(_callback)
    {
        openni::VideoFrameRef depth_frame;
        auto status = _video_stream.readFrame(&depth_frame);
        if(status != openni::STATUS_OK) throw std::runtime_error("Viewer exception. Cann't read video frame");

        depth_map_t depth_map(depth_frame.getWidth(), depth_frame.getHeight());
        depth_map.set_data((const openni::DepthPixel*)depth_frame.getData());

        _command_queue.push(std::bind(_callback, depth_map));
    }
}

END_KINECT_NAMESPACE
