#  include "viewer.h"

BEGIN_KINECT_NAMESPACE

viewer_t::viewer_t(command_queue_t *command_queue)
    : _command_queue(command_queue)
{
    openni::Device device;
    auto status = device.open(openni::ANY_DEVICE);
    if(status != openni::STATUS_OK) throw std::runtime_error("Viewer exception. Can't open device.");

    status = _video_stream.create(device, openni::SENSOR_DEPTH);
    if(status != openni::STATUS_OK) throw std::runtime_error("Viewer exception. Can't create depth video stream.");
}

void viewer_t::set_callback(viewer_callback_t&& func)
{
    _callback = func;
}

void viewer_t::loop()
{
    if(_callback)
    {
        openni::VideoFrameRef depth_frame;
        auto status = _video_stream.readFrame(&depth_frame);
        if(status != openni::STATUS_OK) throw std::runtime_error("Viewer exception. Cann't read video frame");

        depth_map_t depth_map(depth_frame.getWidth(), depth_frame.getHeight());
        depth_map.set_data((const openni::DepthPixel*)depth_frame.getData());

        _command_queue->push(std::bind(_callback, depth_map));
    }
}

END_KINECT_NAMESPACE
