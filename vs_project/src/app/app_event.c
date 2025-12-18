#include "app_event.h"

const char* AppEventToString(AppEvent ev)
{
    switch (ev) {
    case APP_EVT_READY: return "READY";
    case APP_EVT_START: return "START";
    case APP_EVT_STOP:  return "STOP";
    case APP_EVT_RESET: return "RESET";
    case APP_EVT_FAULT: return "FAULT";
    default:            return "UNKNOWN";
    }
}
