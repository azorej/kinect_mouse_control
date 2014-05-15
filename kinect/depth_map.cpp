#include "depth_map.h"

#define MAX_DEPTH 10000

BEGIN_KINECT_NAMESPACE

void depth_map_t::calculate_histogram()
{
    // calculate the accumulative histogram (the yellow display...)
    auto points_number = _width*_height;
    if(points_number)
    {
        _histogram.resize(MAX_DEPTH);
        std::fill(_histogram.begin(), _histogram.end(), 0.f);

        for (int y = 0; y < _height; ++y)
        {
            for (int x = 0; x < _width; ++x)
            {
                size_t depth = get(x,y);
                if (depth/MAX_DEPTH > 0) depth = MAX_DEPTH-1;
                ++_histogram[depth];
            }
        }

        for (int idx=1; idx<MAX_DEPTH; idx++)
        {
            _histogram[idx] += _histogram[idx-1];
        }

        for (int idx=1; idx<MAX_DEPTH; idx++)
        {
            _histogram[idx] = (256 * (1.0f - (_histogram[idx] / points_number)));
        }
    }
}

END_KINECT_NAMESPACE
