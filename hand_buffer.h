#ifndef HAND_BUFFER_H
#define HAND_BUFFER_H

#  include "NiTE.h"

#  include <mutex>
#  include <algorithm>

class depth_map_t
{
public:
    depth_map_t()
        : _data(nullptr)
        , _is_init(false)
    {

    }

    ~depth_map_t()
    {
        delete[] _data;
    }

    void init(int width, int height)
    {
        _is_init = true;
        _width = width;
        _height = height;
        _data = new openni::DepthPixel[width*height];
    }

    bool is_init() const
    {
        return _is_init;
    }

//    bool is_valid() const
//    {
//        return ( _is_valid && is_init() );
//    }

    void swap(depth_map_t& other)
    {
        std::swap(_data, other._data);
    }

    void set_data(const openni::DepthPixel* data)
    {
        std::copy(data, data+_width*_height, _data);
    }

    inline openni::DepthPixel const& get(int x, int y) const
    {
        return _data[x + y*_width];
    }

    inline int width() const
    {
        return _width;
    }

    inline int height() const
    {
        return _height;
    }

private:
    openni::DepthPixel* _data;
    int _width;
    int _height;
    bool _is_init;

    depth_map_t(depth_map_t const&);
};

struct vector3_t
{
    vector3_t(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z)
    { }

    float x;
    float y;
    float z;
};

class hand_info_t
{
public:

private:
    vector3_t _depth_coordinates;
    vector3_t _global_coordinates;
};

class hands_array_t
{
public:

private:

};

class hand_buffer_t
{
public:
    hand_buffer_t()
        : _hand_depth_coordinates(0,0,0)
        , _hand_global_coordinates(0,0,0)
        , _is_init(false)
    {

    }

    hand_buffer_t(hand_buffer_t const&) = delete;
    hand_buffer_t& operator=(hand_buffer_t) = delete;

    void init(hand_buffer_t const& other)
    {
        _depth_map.init(other._depth_map.width(), other._depth_map.height());
        _is_init = true;
    }

    inline std::unique_lock<std::mutex> lock()
    {
        return std::unique_lock<std::mutex>(_m);
    }

    bool is_init() const
    {
        return _is_init;
    }

//    bool is_valid() const
//    {
//        return ( _is_init && _depth_map.is_valid() );
//    }

    void swap(hand_buffer_t* other)
    {
        _depth_map.swap(other->_depth_map);
        std::swap(_hand_depth_coordinates, other->_hand_depth_coordinates);
        std::swap(_hand_global_coordinates, other->_hand_global_coordinates);
    }

    depth_map_t& depth_map()
    {
        return _depth_map;
    }

    vector3_t& hand_depth_coordinates()
    {
        return _hand_depth_coordinates;
    }

    vector3_t& hand_global_coordinates()
    {
        return _hand_global_coordinates;
    }



private:
    depth_map_t _depth_map;
    vector3_t _hand_depth_coordinates;
    vector3_t _hand_global_coordinates;

    bool _is_init;

    std::mutex _m;

    friend class hand_tracker_t;
};

#endif // HAND_BUFFER_H
