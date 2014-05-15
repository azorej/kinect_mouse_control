#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#  include <QMainWindow>

#  include "kinect/kinect.h"

namespace Ui {
class MainWindow;
}

class depth_view_t;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    kinect::kinect_t _kinect;

    //hand_tracker_t _hand_tracker;
    //std::shared_ptr<hand_buffer_t> _remote_hand_buffer;
    //hand_buffer_t _hand_buffer;
    depth_view_t* _depth_view;

    bool _is_track_started;

    void add_log_message(QString const& msg);

private slots:
    void print_log();
    void on_pushButton_clicked();
    void on_track_button_clicked();
    void swap_hand_buffers();
};

#endif // MAINWINDOW_H
