# About
EventBuffer can be used by cooperating tasks that need to send events between 
them. The intended application is for embedded microcontrollers.

EventBuffer is not thread-safe and assumes that the tasks execute in an
interleaved fashion.

An "event" in this context is simply a 32 bit integer. The meaning of the 
event is application defined.

# Usage
See the example Arduino sketch in the examples folder.
