#include "mainwindow.h"
#include "ui_mainwindow.h"

#  include "simple_loop_controller.h"

#  include <QTimer>

#  include "logging_system.h"
#  include "depth_view.h"
#  include "mouse_control.h"

#  include <thread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _is_track_started(false)
{
    ui->setupUi(this);

    try
    {
        _kinect.init();

        auto viewer = _kinect.create_viewer();

        _depth_view = new depth_view_t(this, viewer);
        ui->verticalLayout->insertWidget(1, _depth_view, 4);

        _kinect.start<simple_loop_controller_t>();
    }
    catch(std::exception const& excep)
    {
        log(excep.what());
    }

    log("Let's go!");




    //_remote_hand_buffer = std::make_shared<hand_buffer_t>();

//    QTimer* log_timer = new QTimer(this);
//    connect(log_timer, SIGNAL(timeout()), this, SLOT(print_log()));
//    log_timer->start(100);

//    try
//    {
//        _hand_tracker.init(_remote_hand_buffer);

//        _hand_buffer.init(*_remote_hand_buffer);

//        QTimer* buffer_swap_timer = new QTimer(this);
//        connect(buffer_swap_timer, SIGNAL(timeout()), this, SLOT(swap_hand_buffers()));
//        buffer_swap_timer->start(50);//20 times per second

//        new mouse_control_t(this, _hand_buffer);
//    }
//    catch(std::exception const& ex)
//    {
//        add_log_message(ex.what());
//        ui->track_button->setDisabled(true);
//    }
}

MainWindow::~MainWindow()
{
//    if(_is_track_started)
//    {
//        _hand_tracker.stop_tracking(true);
//    }
    delete ui;
}

void MainWindow::add_log_message(QString const& msg)
{
    ui->log_window->append(msg);
}

void MainWindow::print_log()
{
    auto msgs = logging_system_t::singleton().get();
    for(auto const& m : msgs)
    {
        add_log_message(QString(m.c_str()));
    }
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_track_button_clicked()
{
    if(_is_track_started)
    {
        _hand_tracker.stop_tracking(true);
        _is_track_started = false;
    }
    else
    {
        _hand_tracker.start_tracking();
        _is_track_started = true;
    }
}

void MainWindow::swap_hand_buffers()
{
    auto lock = _remote_hand_buffer->lock();
   _remote_hand_buffer->swap(&_hand_buffer);
}
