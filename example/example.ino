/**
 * The following somewhat silly example shows the basic usage of EventBuffer. 
 * In a simple use case like this where we just want to turn on and off the 
 * LED based on the button status, using the EventBuffer is a massive overkill
 * in terms of complexity. EventBuffer becomes more useful in more advanced
 * scenarios where it is desirable to have a loose coupling between the sender
 * and receiver task.
 */
#include <Arduino>
#include "EventBuffer.h"

#define BUTTON_PIN 2

const int32_t EVENT_BUTTON_PRESSED 1;
const int32_t EVENT_BUTTON_RELEASED 2;

class SenderTask
{
public:
    SenderTask() : LastState(false) {};

    void setup() {
        pinMode(BUTTON_PIN, INPUT);
    };

    void loop() {
        bool state = digitalRead(BUTTON_PIN);

        // Only trigger an event if the button state changed
        if (state != LastState) {            
            if (state == HIGH) {
                // The state is now high, so the button was pressed.
                // Send the pressed event to the receiver.
                Events.emit(EVENT_BUTTON_PRESSED);
            }
            else {
                // The state is not high, so the button was released.
                // Send the released event to the receiver.
                Events.emit(EVENT_BUTTON_RELEASED);
            }
            LastState = state;
        }
    };

private:
    // Variable to keep track of changes in the button press state.
    bool LastState;
};


class ReceiverTask
{
public:    
    void loop() {
        // In this example, where the tasks strictly take turns, there will 
        // at most only be one event waiting, wo the while loop is not really
        // needed. However it is good practice. In more advanced scenarios 
        // where the tasks may not take strict turns, the receiving end should
        // iterate through all available events.
        while (Events.has_event()) {
            int32_t e = Events.get();
            if (e == EVENT_BUTTON_PRESSED) {
                digitalWrite(LED_BUILTIN, true);
            }
            else if (e == EVENT_BUTTON_RELEASED) {
                digitalWrite(LED_BUILTIN, false);
            }
        }
    };
};

SenderTask task1;
ReceiverTask task2;

void setup()
{
    task1.setup()
}

void loop()
{
    task1.loop();
    task2.loop();
}
