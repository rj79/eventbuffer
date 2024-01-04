#ifndef EVENT_BUFFER_H
#define EVENT_BUFFER_H

#include <stdint.h>

class EventBuffer
{
public:
    EventBuffer(uint8_t size);
    ~EventBuffer();
    void emit(int32_t event);
    bool has_event() const;
    int32_t get();

private:
    uint8_t Count;
    uint8_t ReadPos;
    uint8_t WritePos;
    uint8_t Size;
    int32_t* Events;

    bool is_empty() const;
    bool is_full() const;
};

extern EventBuffer Events;

#endif
