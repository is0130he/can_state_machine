#ifndef CAN_EVENT_MAPPER_H
#define CAN_EVENT_MAPPER_H

#include "can.h"
#include "../app/app_event.h"

AppEvent CanEvent_ToAppEvent(CanState can_ev);

#endif
