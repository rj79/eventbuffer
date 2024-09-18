#include "EventBuffer.h"

#define MIN(x, y) (x < y ? x : y)

EventBuffer::EventBuffer(uint8_t size) :
    Count(0),
    ReadPos(0),
    WritePos(0),
    Events(nullptr),
    Overflow(false),
    Underflow(false)
{
    Size = MIN((int)size, 32);
    Events = new int32_t[Size];
}

EventBuffer::~EventBuffer()
{
    delete[] Events;
}

bool EventBuffer::is_empty() const
{
    return Count == 0;
}

bool EventBuffer::is_full() const
{
    return Count == Size;
}

bool EventBuffer::emit(int32_t event)
{
    if (!is_full()) {
        Events[WritePos] = event;
        ++WritePos;
        if (WritePos == Size) {
            WritePos = 0;
        }
        ++Count;
        return true;
    } 
    else {
        Overflow = true;
        return false;
    }
}

bool EventBuffer::has_event() const 
{
    return Count > 0;
}

int32_t EventBuffer::get()
{
    if (!is_empty()) {
        int32_t result = Events[ReadPos];
        ++ReadPos;
        if (ReadPos == Size) {
            ReadPos = 0;
        }
        --Count;
        return result;
    }
    else {
        Underflow = true;
        return __INT32_MAX__;
    }
}

void EventBuffer::reset()
{
    Count = 0;
    ReadPos = 0;
    WritePos = 0;
    Overflow = false;
    Underflow = false;
}

bool EventBuffer::underflow() const
{
    return Underflow;
}

bool EventBuffer::overflow() const
{
    return Overflow;
}

EventBuffer Events(32);
