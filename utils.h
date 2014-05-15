#ifndef UTILS_H
#define UTILS_H

#  include <time.h>
#  include <functional>
#  include <sstream>

class LoopPerSecondCounter
{
public:
    LoopPerSecondCounter(const char* msg, std::function<void(const char*)> log_func, size_t count_to_log)
        : _msg(msg)
        , _count(0)
        , _count_to_log(count_to_log)
        , _log_func(log_func)
    {

    }

    void init()
    {
        clock_gettime(CLOCK_MONOTONIC, &_begin);
    }

    LoopPerSecondCounter& operator++()
    {
        ++_count;
        if(_count % _count_to_log == 0)
        {
            timespec cur_time;
            clock_gettime(CLOCK_MONOTONIC, &cur_time);
            time_t time_spent = cur_time.tv_sec - _begin.tv_sec;
            std::stringstream ss;
            ss<<_msg<<_count/time_spent;
            _log_func(ss.str().c_str());
        }
        return *this;
    }


private:
    const char* _msg;
    unsigned long _count;
    const size_t _count_to_log;
    timespec _begin;
    std::function<void(const char*)> _log_func;
};

class TimeMeter
{
public:
    TimeMeter(const char* msg, std::function<void(const char*)> log_func, size_t count_to_log)
        : _msg(msg)
        , _count(0)
        , _count_to_log(count_to_log)
        , _time_spent(0)
        , _log_func(log_func)
    {

    }

    void start()
    {
        clock_gettime(CLOCK_MONOTONIC, &_time_begin);
    }

    void stop()
    {
        timespec time_end;
        clock_gettime(CLOCK_MONOTONIC, &time_end);
        ++_count;
        _time_spent += time_end.tv_sec - _time_begin.tv_sec;
        if(_count % _count_to_log == 0)
        {
            std::stringstream ss;
            ss<<_msg<<"Count="<<_count<<" Time spent= "<<_time_spent;
            _log_func(ss.str().c_str());
        }
    }

private:
    const char* _msg;
    unsigned long _count;
    const size_t _count_to_log;
    timespec _time_begin;
    time_t _time_spent;
    std::function<void(const char*)> _log_func;
};

#endif // UTILS_H
