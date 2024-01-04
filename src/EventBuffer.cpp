#include "EventBuffer.h"
#include "Arduino.h"
#include <stdint.h>

EventBuffer::EventBuffer(uint8_t size) :
    Count(0),
    ReadPos(0),
    WritePos(0)
{
    Size = std::min((int)size, 32);
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

void EventBuffer::emit(int32_t event)
{
    if (!is_full()) {
        Events[WritePos] = event;
        ++WritePos;
        if (WritePos == Size) {
            WritePos = 0;
        }
        ++Count;
    } 
    else {
        /*char buffer[64];
        snprintf(buffer, sizeof(buffer), "Warning: Event buffer full. Could not store %d.", event);
        Serial.println(buffer);*/
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
        /*char buffer[64];
        snprintf(buffer, sizeof(buffer), "Warning: get() called when event buffer empty.");
        Serial.println(buffer);*/
        return __INT32_MAX__;
    }
}

void EventBuffer::reset()
{
    Count = 0;
    ReadPos = 0;
    WritePos = 0;
}

EventBuffer Events(32);
