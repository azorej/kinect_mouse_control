#ifndef KINECT_MAIN_H
#define KINECT_MAIN_H

#  include "defs.h"

#  include "loop_controller_interface.h"

#  include <functional>
#  include <memory>
#  include <queue>

BEGIN_KINECT_NAMESPACE

class hand_tracker_t;
class video_streamer_t;

class kinect_t
{
public:
    kinect_t();
    ~kinect_t();

    kinect_t(kinect_t const&) = delete;
    kinect_t& operator=(kinect_t const&) = delete;

    void init();
    void close();

    hand_tracker_t* create_hand_tracker();
    video_streamer_t* create_video_streamer();

    void swap_command_queue(command_queue_t* command_queue);

    /**
     *LoopContoller must inherit loop_controller_interface
     *and has default constructor
     */
    template <typename LoopController>
    void start();

private:
    std::unique_ptr<hand_tracker_t> _hand_tracker;
    std::unique_ptr<video_streamer_t> _viewer;
    std::unique_ptr<loop_controller_interface> _loop_controller;

    bool _is_init;
    command_queue_t _command_queue;

    void loop();
};

template <typename LoopController>
void kinect_t::start()
{
    _loop_controller.reset(new LoopController());
    _loop_controller->set_frequency(1.f/20.f);
    _loop_controller->start_looping(std::bind(&kinect_t::loop, this));
}

END_KINECT_NAMESPACE

#endif // KINECT_H
