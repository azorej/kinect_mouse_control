#ifndef LOGGING_SYSTEM_H
#define LOGGING_SYSTEM_H

#  include <string>
#  include <vector>
#  include <mutex>

class logging_system_t
{
public:
    static logging_system_t& singleton()
    {
        static logging_system_t single;
        return single;
    }

    void record(const char* msg)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _messages.push_back(std::string(msg));
    }

    std::vector<std::string> get()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        std::vector<std::string> ret;
        ret.swap(_messages);
        return ret;
    }

private:
    std::vector<std::string> _messages;
    std::mutex _mutex;

    logging_system_t() { }
    logging_system_t(logging_system_t const&);
};

static inline void log(const char* msg)
{
    logging_system_t::singleton().record(msg);
}

#endif // LOGGING_SYSTEM_H
