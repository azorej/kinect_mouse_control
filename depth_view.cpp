#include "depth_view.h"

#include "logging_system.h"

#include "GL/glu.h"
#include <sstream>

#define TEXTURE_SIZE	512

#define MIN_NUM_CHUNKS(data_size, chunk_size)	((((data_size)-1) / (chunk_size) + 1))
#define MIN_CHUNKS_SIZE(data_size, chunk_size)	(MIN_NUM_CHUNKS(data_size, chunk_size) * (chunk_size))

float Colors[][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 1}};

#define CHECK_OPENGL_ERROR() \
    { \
        auto err = glGetError(); \
        if(err != GL_NO_ERROR) \
        { \
            std::ostringstream ss; \
            ss<<(const char*)gluErrorString(err)<<" Line "<<__LINE__; \
            log(ss.str().c_str()); \
        }\
    }


depth_view_t::depth_view_t(QWidget* parent, kinect::video_streamer_t* video_streamer)
    : QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer));
    glDepthFunc(GL_LEQUAL);

    video_streamer->set_depth_callback(std::bind(&depth_view_t::update_depth_map, this, std::placeholders::_1));

    auto resolution = video_streamer->get_window_size();

    _tex_map_width = MIN_CHUNKS_SIZE(resolution.x, TEXTURE_SIZE);
    _tex_map_height = MIN_CHUNKS_SIZE(resolution.y, TEXTURE_SIZE);
    _tex_map.resize(_tex_map_width * _tex_map_height);
}

void depth_view_t::initializeGL()
{
    qglClearColor(Qt::black);

    glMatrixMode(GL_PROJECTION);
}

void depth_view_t::resizeGL(int width, int height)
{
    glLoadIdentity();
    glViewport(0, 0, (GLint)width, (GLint)height);
    _width=width;
    _height=height;
    glOrtho(0,_width,_height,0,-1.0, 1.0);
}

void depth_view_t::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    qglColor(Qt::white);

    auto histogram = _depth_map.get_histogram();
    if(histogram.size() > 0)
    {
        float factor[3] = {1, 1, 1};

        for (int y = 0; y < _depth_map.height(); ++y)
        {
            for (int x = 0; x < _depth_map.width(); ++x)
            {
                factor[0] = Colors[3][0];
                factor[1] = Colors[3][1];
                factor[2] = Colors[3][2];

                int hist_value = histogram[_depth_map.get(x,y)];
                auto& pix = _tex_map[x + _tex_map_width*y];
                pix.r = hist_value*factor[0];
                pix.g = hist_value*factor[1];
                pix.b = hist_value*factor[2];

                factor[0] = factor[1] = factor[2] = 1;
            }
        }

        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _tex_map_width, _tex_map_height, 0, GL_RGB, GL_UNSIGNED_BYTE, _tex_map.data());

        // Display the OpenGL texture map
        glColor4f(1,1,1,1);

        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);

        // upper left
        glTexCoord2f(0, 0);
        glVertex2f(0, 0);
        // upper right
        glTexCoord2f((float)_depth_map.width()/(float)_tex_map_width, 0);
        glVertex2f(_width, 0);
        // bottom right
        glTexCoord2f((float)_depth_map.width()/(float)_tex_map_width, (float)_depth_map.height()/(float)_tex_map_height);
        glVertex2f(_width, _height);
        // bottom left
        glTexCoord2f(0, (float)_depth_map.height()/(float)_tex_map_height);
        glVertex2f(0, _height);

        glEnd();
        glDisable(GL_TEXTURE_2D);

        //paintTrack();
    }

    CHECK_OPENGL_ERROR();

    glPopMatrix();

    swapBuffers();
}

//void depth_view_t::paintTrack()
//{
//    glColor3f((float)1, (float)0, (float)0);
//    float coordinates[3] = {0};
//    float factorX = wax / (float)_hand_buffer.depth_map().width();
//    float factorY = way / (float)_hand_buffer.depth_map().height();

//    coordinates[0] = _hand_buffer.hand_depth_coordinates().x * factorX;
//    coordinates[1] = _hand_buffer.hand_depth_coordinates().y * factorY;

//    glEnableClientState(GL_VERTEX_ARRAY);
//    glPointSize(16);
//    glVertexPointer(3, GL_FLOAT, 0, coordinates);
//    glDrawArrays(GL_POINTS, 0, 1);
//    glDisableClientState(GL_VERTEX_ARRAY);
//}

void depth_view_t::update_depth_map(kinect::depth_map_t& depth_map)
{
    _depth_map.swap(depth_map);
}
