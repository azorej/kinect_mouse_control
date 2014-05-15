#ifndef KINECT_DEPTH_MAP_H
#define KINECT_DEPTH_MAP_H

#  include "defs.h"

#  include "OpenNI.h"

#  include <memory>

BEGIN_KINECT_NAMESPACE

class depth_map_t
{
public:
    depth_map_t(depth_map_t &&) = default;
    depth_map_t& operator=(depth_map_t &&) = default;

    depth_map_t(int width, int height)
    {
        _width = width;
        _height = height;
        _data.reset(new openni::DepthPixel[width*height]);
    }

    void swap(depth_map_t& other)
    {
        std::swap(_data, other._data);
        std::swap(_histogram, other._histogram);
    }

    void set_data(const openni::DepthPixel* data)
    {
        _histogram.clear();
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

    std::vector<float> const& get_histogram()
    {
        if(_histogram.empty()) calculate_histogram();
        return _histogram;
    }

private:
    std::unique_ptr<openni::DepthPixel> _data;
    int _width;
    int _height;
    std::vector<float> _histogram;

    void calculate_histogram();
};

END_KINECT_NAMESPACE

#endif // DEPTH_MAP_H
