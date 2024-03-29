#ifndef SIMPLE_LOOP_CONTROLLER_H
#define SIMPLE_LOOP_CONTROLLER_H

#include "kinect/loop_controller_interface.h"

#include <QObject>

class simple_loop_controller_t : public QObject, public kinect::loop_controller_interface
{
    Q_OBJECT

public:
    void set_frequency(float freq) override;
    void start_looping(std::function<void()> const& func) override;

private:
    std::function<void()> _func;
    float _frequency;

private slots:
    void do_loop();
};

#endif // SIMPLE_LOOP_CONTROLLER_H
