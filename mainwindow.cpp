#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "simple_loop_controller.h"
#include "logging_system.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    //,_is_track_started(false)
{
    ui->setupUi(this);

    logging_system_t::singleton().set_destination(ui->log_window);

    try
    {
        _kinect.init();

        //_kinect.create_hand_tracker();
        auto video_streamer = _kinect.create_video_streamer();

        _depth_view = new depth_view_t(this, video_streamer);
        ui->verticalLayout->insertWidget(1, _depth_view, 4);

        _kinect.start<simple_loop_controller_t>();
    }
    catch(std::exception const& excep)
    {
        log(excep.what());
    }

    log("Let's go!");
}

MainWindow::~MainWindow()
{
//    if(_is_track_started)
//    {
//        _hand_tracker.stop_tracking(true);
//    }
    delete ui;
}


void MainWindow::on_track_button_clicked()
{
//    if(_is_track_started)
//    {
//        _hand_tracker.stop_tracking(true);
//        _is_track_started = false;
//    }
//    else
//    {
//        _hand_tracker.start_tracking();
//        _is_track_started = true;
//    }
}
