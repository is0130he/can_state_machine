#ifndef EVENT_DISPATCH_H
#define EVENT_DISPATCH_H

#include "../driver/can.h"           // ← イベント型の定義元
#include "../service/event_buffer.h" // ← EventSource など
#include "state_machine.h"
#include "../app/app_event.h"


void EventDispatch_Process(AppEvent ev, EventSource src);

#endif
