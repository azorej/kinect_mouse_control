#ifndef DEPTH_VIEW_H
#define DEPTH_VIEW_H

#  include "kinect/viewer.h"

#  include <QGLWidget>

#  include <vector>

#define MAX_DEPTH 10000

class depth_view_t : public QGLWidget
{
public:
    depth_view_t(QWidget* parent, kinect::viewer_t* viewer);

private:
    int _width ,_height;

    std::vector<openni::RGB888Pixel> _tex_map;
    int _tex_map_width;
    int _tex_map_height;

    kinect::depth_map_t _depth_map;

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void paintTrack();

    void update_view(kinect::depth_map_t&& depth_map);
};

#endif // DEPTH_VIEW_H
