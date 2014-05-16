#ifndef LOGGING_SYSTEM_H
#define LOGGING_SYSTEM_H

#include <QTextBrowser>

#include <assert.h>

class logging_system_t
{
public:
    logging_system_t(logging_system_t const&) = delete;

    static logging_system_t& singleton()
    {
        static logging_system_t instance;
        return instance;
    }

    void do_log(const char* msg)
    {
        assert(_is_init);
        _dest->append(QString(msg));
    }

    void set_destination(QTextBrowser* dest)
    {
        _dest = dest;
        _is_init = true;
    }


private:
    QTextBrowser* _dest;
    bool _is_init;

    logging_system_t()
        : _is_init(false)
    {

    }
};

static inline void log(const char* msg)
{
    logging_system_t::singleton().do_log(msg);
}

#endif // LOGGING_SYSTEM_H
