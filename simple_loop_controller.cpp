#include "simple_loop_controller.h"

#  include <QTimer>

void simple_loop_controller_t::set_frequency(float freq)
{
    _frequency = freq;
}

void simple_loop_controller_t::start_looping(std::function<void ()> const& func)
{
    _func = func;

    auto timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(do_loop()));
    timer->start(1000.f/_frequency);
}

void simple_loop_controller_t::do_loop()
{
    _func();
}

