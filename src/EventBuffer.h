#ifndef EVENT_BUFFER_H
#define EVENT_BUFFER_H

#include <stdint.h>

/**
 * The EventBuffer can be used by cooperating tasks to exchange events.
 * Events are queued in a FIFO manner.
 * EventBuffer is not thread-safe and assumes that the tasks execute in an 
 * interleaved fashion.
 */
class EventBuffer
{
public:
    EventBuffer(uint8_t size);
    ~EventBuffer();

    /**
     * Emits an event.
     * If emit() is called when the EventBuffer is full, the overflow flag will
     * be set and the function will retun false.
     * @param event The event to be emitted.
     * @return True if there was enough space in the buffer, false otherwise.
     */    
    bool emit(int32_t event);

    /**
     * Checks if one or more events are available.
     * @return True if there is at least one available event, false otherwise.
     */
    bool has_event() const;

    /**
     * Returns the first event in the queue.
     * If get() is called when the EventBuffer is empty, the returned event will
     * be equal to __INT32_MAX__ and the underflow flag will be set.
     * @return The event.
     */
    int32_t get();

    /**
     * Clears the EventBuffer and resets overflow and underflow status.
    */
    void reset();

    /**
     * Checks if the overflow flag has been set.
     * @return True if overflow has occured since the last reset, false 
     * otherwise.
     */
    bool overflow() const;

    /**
     * Checks if the underflow flag has been set.
     * @return True if underflow has occured since the last reset, false 
     * otherwise.
     */
    bool underflow() const;

private:
    uint8_t Count;
    uint8_t ReadPos;
    uint8_t WritePos;
    uint8_t Size;
    int32_t* Events;
    bool Overflow;
    bool Underflow;

    bool is_empty() const;
    bool is_full() const;
};

extern EventBuffer Events;

#endif
