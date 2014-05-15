
///*******************************************************************************
//*                                                                              *
//*   PrimeSense NiTE 2.0 - Simple Tracker Sample                                *
//*   Copyright (C) 2012 PrimeSense Ltd.                                         *
//*                                                                              *
//*******************************************************************************/
//#  include "hand_tracker.h"

//#  include "logging_system.h"

//#  include <exception>
//#  include <string>
//#  include <sstream>
//#  include <thread>

//hand_tracker_t::hand_tracker_t()
//    : _lock_time_meter("Hand tracker lock time meter: ", (void (*)(const char*))&log, 500)
//{
//}

//void hand_tracker_t::init(std::shared_ptr<hand_buffer_t> data_buffer)
//{
//    _control_flag.store(false);

//    _remote_data_buffer = data_buffer;

//    nite::Status niteRc;

//    niteRc = nite::NiTE::initialize();
//    if (niteRc != nite::STATUS_OK)
//    {
//        throw std::runtime_error("NiTE initialization failed");
//    }

//    niteRc = _tracker.create();
//    if (niteRc != nite::STATUS_OK)
//    {
//        throw std::runtime_error("Couldn't create user tracker");
//    }

//    init_data_buffer();
//    init_hand_track();

//    log("Hand tracker init success!");
//}

//void hand_tracker_t::init_data_buffer()
//{
//    nite::HandTrackerFrameRef hand_frame;
//    nite::Status rc = _tracker.readFrame(&hand_frame);
//    if (rc != nite::STATUS_OK)
//    {
//        throw std::runtime_error("Get hand frame failed. Failed to initialize buffer");
//    }

//    openni::VideoFrameRef depth_frame = hand_frame.getDepthFrame();

//    if(!depth_frame.isValid())
//    {
//        throw std::runtime_error("Depth frame isn't valid. Failed to initialize buffer");
//    }

//    _data_buffer._depth_map.init(depth_frame.getWidth(), depth_frame.getHeight());
//    _data_buffer._is_init = true;

//    _remote_data_buffer->init(_data_buffer);
//}

//void hand_tracker_t::init_hand_track()
//{
//    //_tracker.startGestureDetection(nite::GESTURE_WAVE);
//    //_tracker.startGestureDetection(nite::GESTURE_CLICK);
//    _tracker.startGestureDetection(nite::GESTURE_HAND_RAISE);

//    log("Need wave, click or raise hand to start tracking your hand...");
//}

//void hand_tracker_t::close()
//{
//    nite::NiTE::shutdown();
//}

//void hand_tracker_t::start_tracking()
//{
//    _control_flag.store(true);
//    std::thread track_thread(std::bind(&hand_tracker_t::loop, this));
//    track_thread.detach();
//}

//void hand_tracker_t::stop_tracking(bool waiting)
//{
//    _control_flag.store(false);
//    if(waiting)
//    {
//        std::lock_guard<std::mutex> lock(_control_mutex);
//    }
//}

//void hand_tracker_t::loop()
//{
//    log("Start hand_tracker_loop");

//    std::lock_guard<std::mutex> control_lock(_control_mutex);

//    LoopPerSecondCounter loop_counter("Hand tracker: fps = ", (void (*)(const char*))&log, 500);
//    loop_counter.init();
//    while(_control_flag.load())
//    {
//        nite::HandTrackerFrameRef hand_frame;
//        nite::Status rc = _tracker.readFrame(&hand_frame);
//        if (rc != nite::STATUS_OK)
//        {
//            log("GetNextData failed");
//            break;
//        }

//        this->prepare_depth_map(hand_frame);
//        this->track(hand_frame);

//        {
//            _lock_time_meter.start();
//            auto lock = _remote_data_buffer->lock();
//            _lock_time_meter.stop();
//            _remote_data_buffer->swap(&_data_buffer);
//        }

//        ++loop_counter;
//    }
//}

//void hand_tracker_t::track(nite::HandTrackerFrameRef const& hand_frame)
//{
//    const nite::Array<nite::GestureData>& gestures = hand_frame.getGestures();
//    for (int i = 0; i < gestures.getSize(); ++i)
//    {
//        if (gestures[i].isComplete())
//        {
//            nite::HandId newId;
//            _tracker.startHandTracking(gestures[i].getCurrentPosition(), &newId);
//        }
//    }

//    const nite::Array<nite::HandData>& hands = hand_frame.getHands();
//    for (int i = 0; i < hands.getSize(); ++i)
//    {
//        const nite::HandData& hand = hands[i];
//        if (hand.isTracking())
//        {
//            const nite::Point3f& position = hand.getPosition();

//            _data_buffer._hand_global_coordinates.x = position.x;
//            _data_buffer._hand_global_coordinates.y = position.y;
//            _data_buffer._hand_global_coordinates.z = position.z;

//            auto status = _tracker.convertHandCoordinatesToDepth(position.x, position.y, position.z, &_data_buffer.hand_depth_coordinates().x, &_data_buffer.hand_depth_coordinates().y);
//            if(status != nite::STATUS_OK)
//            {
//                log("Nite coordinates conversion error. Global to depth");
//            }
////            std::stringstream ss;
////            ss<<"Hand tracking... "<<hand.getId()<<" ("<<hand.getPosition().x<<", "<<hand.getPosition().y<<", "<<hand.getPosition().z<<")";
////            log(ss.str().c_str());
//        }
//    }





////    const nite::Array<nite::GestureData>& gestures = handFrame.getGestures();
////    for (int i = 0; i < gestures.getSize(); ++i)
////    {
////        if (gestures[i].isComplete())
////        {
////            const nite::Point3f& position = gestures[i].getCurrentPosition();
////            printf("Gesture %d at (%f,%f,%f)\n", gestures[i].getType(), position.x, position.y, position.z);

////            nite::HandId newId;
////            m_pHandTracker->startHandTracking(gestures[i].getCurrentPosition(), &newId);
////        }
////    }

////        const nite::Array<nite::HandData>& hands= handFrame.getHands();
////        for (int i = 0; i < hands.getSize(); ++i)
////        {
////            const nite::HandData& user = hands[i];

////            if (!user.isTracking())
////            {
////                printf("Lost hand %d\n", user.getId());
////                nite::HandId id = user.getId();
////                HistoryBuffer<20>* pHistory = g_histories[id];
////                g_histories.erase(g_histories.find(id));
////                delete pHistory;
////            }
////            else
////            {
////                if (user.isNew())
////                {
////                    printf("Found hand %d\n", user.getId());
////                    g_histories[user.getId()] = new HistoryBuffer<20>;
////                }
////                // Add to history
////                HistoryBuffer<20>* pHistory = g_histories[user.getId()];
////                pHistory->AddPoint(user.getPosition());
////                // Draw history
////                DrawHistory(m_pHandTracker, user.getId(), pHistory);
////            }
////        }

//}

//void hand_tracker_t::prepare_depth_map(nite::HandTrackerFrameRef const& hand_frame)
//{
//    openni::VideoFrameRef depth_frame;

//    depth_frame = hand_frame.getDepthFrame();

//    if(depth_frame.isValid())
//    {
//        _data_buffer._depth_map.set_data((const openni::DepthPixel*)depth_frame.getData());
//    }
//}
