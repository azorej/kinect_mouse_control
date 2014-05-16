#ifndef KINECT_DEPTH_MAP_H
#define KINECT_DEPTH_MAP_H

#include "defs.h"

#include <memory>
#include <assert.h>

BEGIN_KINECT_NAMESPACE

typedef uint16_t depth_pixel_t;

class depth_map_t
{
public:
//    depth_map_t(const depth_map_t&) = delete;
//    depth_map_t& operator=(const depth_map_t&) = delete;

//    depth_map_t(depth_map_t&&) = default;
//    depth_map_t& operator=(depth_map_t&&) = default;
    depth_map_t()
        : _width(0), _height(0)
    { }

    depth_map_t(int width, int height)
    {
        _width = width;
        _height = height;
        _data.reset(new depth_pixel_t[width*height], [](depth_pixel_t* ptr) {delete[] ptr;});
    }

    void swap(depth_map_t& other)
    {
        std::swap(_data, other._data);
        std::swap(_histogram, other._histogram);
    }

    void set_data(const depth_pixel_t* data)
    {
        _histogram.clear();
        std::copy(data, data+_width*_height, _data.get());
    }

    inline depth_pixel_t const& get(int x, int y) const
    {
        assert((x < _width) && (y < _height));
        return _data.get()[x + y*_width];
    }

    inline int width() const
    {
        return _width;
    }

    inline int height() const
    {
        return _height;
    }

    std::vector<float> const& get_histogram()
    {
        if(_histogram.empty()) calculate_histogram();
        return _histogram;
    }

private:
    std::shared_ptr<depth_pixel_t> _data;
    int _width;
    int _height;
    std::vector<float> _histogram;

    void calculate_histogram();
};

END_KINECT_NAMESPACE

#endif // DEPTH_MAP_H
