#ifndef KINECT_HAND_TRACKER_H
#define KINECT_HAND_TRACKER_H

#include "defs.h"
#include "utils.h"

#include "NiTE.h"

#include <vector>
#include <functional>

BEGIN_KINECT_NAMESPACE

struct hand_t
{
    nite::HandId id;
    vector2_t depth_coordinates;
    vector3_t global_coordinates;
};


typedef std::vector<hand_t> hand_arr_t;

typedef std::function<void(hand_arr_t)> hand_callback_t;


class hand_tracker_t
{
public:
    explicit hand_tracker_t(command_queue_t& command_queue);

    void start_tracking();
    void stop_tracking();

    void set_callback(hand_callback_t&& func);

    void loop();

private:
    nite::HandTracker _tracker;
    hand_callback_t _callback;
    command_queue_t& _command_queue;

    void check_gestures(nite::HandTrackerFrameRef const& hand_frame);
    void track_hands(nite::HandTrackerFrameRef const& hand_frame);
};

END_KINECT_NAMESPACE

#endif // HAND_TRACKER_H
