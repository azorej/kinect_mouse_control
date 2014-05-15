#ifndef MOUSE_CONTROL_H
#define MOUSE_CONTROL_H

#include <QObject>

#  include "hand_buffer.h"

#  include <list>

#  include "X11/Xlib.h"

class mouse_control_t : public QObject
{
    Q_OBJECT
public:
    explicit mouse_control_t(QObject *parent, hand_buffer_t& hand_buffer);

    ~mouse_control_t();

signals:
    
public slots:

private slots:
    void handle_mouse();
    
private:
    hand_buffer_t& _hand_buffer;
    Display* _display;

    struct coordinates_t
    {
        coordinates_t operator-(coordinates_t& other)
        {
            coordinates_t res = {this->x - other.x, this->y - other.y};
            return res;
        }

        float x;
        float y;
    };

    std::list<coordinates_t> _coordinates;
};

#endif // MOUSE_CONTROL_H
