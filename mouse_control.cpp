//#include "mouse_control.h"

//#  include <logging_system.h>

//#  include <QTimer>

//mouse_control_t::mouse_control_t(QObject *parent, hand_buffer_t& hand_buffer) :
//    QObject(parent)
//  , _hand_buffer(hand_buffer)
//{
//    _display = XOpenDisplay(NULL);

//    if(!_display)
//    {
//        log("Error! Can't open display!");
//    }
//    else
//    {
//        QTimer* mouse_timer = new QTimer(this);
//        connect(mouse_timer, SIGNAL(timeout()), this, SLOT(handle_mouse()));
//        mouse_timer->start(50);
//    }
//}

//mouse_control_t::~mouse_control_t()
//{
//    if(_display)
//    {
//        XCloseDisplay(_display);
//    }
//}

//void mouse_control_t::handle_mouse()
//{
//    auto const& coords = _hand_buffer.hand_depth_coordinates();
//    _coordinates.push_front({coords.x, coords.y});
//    if(_coordinates.size()>10)
//    {
//        _coordinates.pop_back();
//    }

//    if(_coordinates.size()>1)
//    {
//        auto dist = *(++_coordinates.begin()) - *_coordinates.begin();
//        dist.y = -dist.y;

//        XWarpPointer(_display, None, None, 0, 0, 0, 0, dist.x, dist.y);
//    }

//    XFlush(_display);
//}
