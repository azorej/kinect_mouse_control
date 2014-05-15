#  include "hand_tracker.h"

BEGIN_KINECT_NAMESPACE

hand_tracker_t::hand_tracker_t(command_queue_t *command_queue)
    : _command_queue(command_queue)
{
    auto niteRc = _tracker.create();
    if (niteRc != nite::STATUS_OK)
    {
        throw std::runtime_error("Couldn't create NiTE hand tracker");
    }
}

void hand_tracker_t::start_tracking()
{
    _tracker.startGestureDetection(nite::GESTURE_HAND_RAISE);
}

void hand_tracker_t::stop_tracking()
{
    _tracker.stopGestureDetection(nite::GESTURE_HAND_RAISE);
}

void hand_tracker_t::set_callback(hand_callback_t&& func)
{
    _callback = func;
}

void hand_tracker_t::loop()
{
    if(_callback)
    {
        nite::HandTrackerFrameRef hand_frame;
        nite::Status rc = _tracker.readFrame(&hand_frame);

        if (rc != nite::STATUS_OK) throw std::runtime_exception("Hand tracker error. Can't read hand frame.");

        check_gestures(hand_frame);
        track_hands(hand_frame);
    }
}

void hand_tracker_t::check_gestures(const nite::HandTrackerFrameRef &hand_frame)
{
    auto gestures = hand_frame.getGestures();
    for (auto gesture: gestures)
    {
        if(gesture.isComplete())
        {
            nite::HandId newId;
            _tracker.startHandTracking(gestures[i].getCurrentPosition(), &newId);
        }
    }
}

void hand_tracker_t::track_hands(const nite::HandTrackerFrameRef &hand_frame)
{
    hand_arr_t hand_arr;
    auto hands = hand_frame.getHands();
    for (auto hand: hands)
    {
        if(hand.isTracking())
        {
            hand_t hand_info;
            hand_info.id = hand.getId();

            const nite::Point3f& position = hand.getPosition();
            hand_info.global_coordinates.set(position.x, position.y, position.z);

            auto& depth_c = hand_info.depth_coordinates;

            auto status = _tracker.convertHandCoordinatesToDepth(position.x, position.y, position.z, &depth_c.x, &depth_c.y);

            if(status != nite::STATUS_OK) throw std::runtime_exception("Hand tracker error. Can't convert hand coordinates.");

            hand_arr.push_back(hand);
        }
    }

    command_t track_command = std::bind(_callback, std::move(hand_arr));
    _command_queue->push(track_command);
}

END_KINECT_NAMESPACE
