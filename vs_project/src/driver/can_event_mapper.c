#include "can_event_mapper.h"

AppEvent CanEvent_ToAppEvent(CanState can_ev)
{
    switch (can_ev) {
    case READY: return APP_EVT_READY;
    case START: return APP_EVT_START;
    case STOP:  return APP_EVT_STOP;
    case RESET: return APP_EVT_RESET;
    case FAULT: return APP_EVT_FAULT;
    default:    return APP_EVT_FAULT;
    }
}
