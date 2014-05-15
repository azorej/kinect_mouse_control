#  include "kinect.h"

#  include "hand_tracker.h"
#  include "viewer.h"
#  include "utils.h"

#  include "NiTE.h"

BEGIN_KINECT_NAMESPACE

kinect_t::kinect_t()
    : _is_init(false)
{
}

kinect_t::~kinect_t()
{
    close();
}

void kinect_t::init()
{
    nite::Status niteRc;

    niteRc = nite::NiTE::initialize();
    if (niteRc != nite::STATUS_OK)
    {
        throw std::runtime_error("NiTE initialization failed");
    }

    _is_init = true;
}

void kinect_t::close()
{
    if(_is_init)
    {
        nite::NiTE::shutdown();
        _is_init = false;
    }
}

hand_tracker_t *kinect_t::create_hand_tracker()
{
    _hand_tracker.reset(new hand_tracker_t(&_command_queue));
    return _hand_tracker.get();
}

viewer_t *kinect_t::create_viewer()
{
    _viewer.reset(new viewer_t(&_command_queue));
    return _viewer.get();
}

void kinect_t::get_commands(command_queue_t *command_queue)
{
    //TODO add multithreading safeness
    _command_queue.swap(command_queue);
}

void kinect_t::loop()
{
    try
    {
        if(_is_init)
        {
            if(_hand_tracker) _hand_tracker->loop();
            if(_viewer) _viewer->loop();
        }
    }
    catch(...)
    {
        _command_queue->push(wrap_exception(std::current_exception()));
        return;
    }
}

END_KINECT_NAMESPACE
