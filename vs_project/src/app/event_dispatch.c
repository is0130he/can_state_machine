#include <stdio.h>
#include "event_dispatch.h"
#include "../app/app_event.h"

static int logged_ready_in_active = 0;

void EventDispatch_Process(AppEvent ev, EventSource src)
{
    EcuState cur = GetState();

    /* ERRORíÜÇÕ RESET à»äOÇñ≥éã */
    if (cur == STATE_ERROR && ev != RESET) {
        printf("[%-6s] Event=%-6s IGNORED (STATE_ERROR)\n",
            SrcToString(src),
            AppEventToString(ev));
        return;
    }

    /* ACTIVEíÜÇÃ READY ÇÕèââÒÇÃÇ›ÉçÉO */
    if (cur == STATE_ACTIVE && ev == READY) {
        if (!logged_ready_in_active) {
            printf("[%-6s] Event=%-6s IGNORED (STATE_ACTIVE, first)\n",
                SrcToString(src),
                AppEventToString(ev));
            logged_ready_in_active = 1;
        }
        return;
    }

    printf("[%-6s] Event=%-6s Å® ",
        SrcToString(src),
        AppEventToString(ev));

    EcuState prev = cur;
    StateMachine_UpdateByEvent(ev);
    EcuState next = GetState();

    if (prev != next) {
        logged_ready_in_active = 0;
    }

    PrintState();
}
