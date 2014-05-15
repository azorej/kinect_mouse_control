#ifndef HAND_TRACKER_H
#define HAND_TRACKER_H

#  include "hand_buffer.h"

#  include <memory>
#  include <atomic>

#  include "utils.h"

class hand_tracker_t
{
public:
    hand_tracker_t();

    ~hand_tracker_t()
    {
        close();
    }

    void init(std::shared_ptr<hand_buffer_t> data_buffer);
    void close();

    void loop();

    void track(const nite::HandTrackerFrameRef &hand_frame);

    void start_tracking();
    void stop_tracking(bool waiting);

private:
    nite::HandTracker _tracker;
    std::mutex _control_mutex;
    std::atomic_bool _control_flag;

    hand_buffer_t _data_buffer;
    std::shared_ptr<hand_buffer_t> _remote_data_buffer;

    void prepare_depth_map(nite::HandTrackerFrameRef const& hand_frame);

    TimeMeter _lock_time_meter;

    void init_data_buffer();
    void init_hand_track();
};

#endif // HAND_TRACKER_H
