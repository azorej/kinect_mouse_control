#ifndef KINECT_DEFS_H
#define KINECT_DEFS_H

#  include <functional>
#  include <string>

#define BEGIN_KINECT_NAMESPACE namespace kinect {
#define END_KINECT_NAMESPACE }

BEGIN_KINECT_NAMESPACE

typedef std::function<void()> command_t;
typedef std::queue<command_t> command_queue_t;

struct vector2_t
{
    vector2_t(float x, float y)
        : x(x)
        , y(y)
    { }

    void set(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    float x;
    float y;
};

struct vector3_t
{
    vector3_t(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z)
    { }

    void set(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    float x;
    float y;
    float z;
};

END_KINECT_NAMESPACE

#endif // DEFS_H
