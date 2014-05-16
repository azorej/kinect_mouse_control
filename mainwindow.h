#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "kinect/kinect.h"

#include "depth_view.h"

#include <QMainWindow>

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

    depth_view_t* _depth_view;

    kinect::kinect_t _kinect;


    //bool _is_track_started;

private slots:
    void on_track_button_clicked();
};

#endif // MAINWINDOW_H
