#ifndef KINECT_DEFS_H
#define KINECT_DEFS_H

#include <functional>
#include <queue>
#include <string>

#define BEGIN_KINECT_NAMESPACE namespace kinect {
#define END_KINECT_NAMESPACE }

BEGIN_KINECT_NAMESPACE

typedef std::function<void()> command_t;
typedef std::queue<command_t> command_queue_t;

END_KINECT_NAMESPACE

#endif // DEFS_H
