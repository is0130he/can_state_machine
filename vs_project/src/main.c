#include <stdio.h>
#include "app/state_machine.h"
#include "service/event_buffer.h"

int main(void)
{
    char in_ch;
    CanState ev;

    StateMachine_Reset(STATE_INIT);

    while (1)
    {
        /* --- ‹[— Š„‚è‚İ --- */
        in_ch = getchar();
        Can_RxInterruptMock(in_ch);

        /* --- ƒƒCƒ“ƒ‹[ƒvˆ— --- */
        if (EventBuffer_Pop(&ev)) {
            StateMachine_UpdateByEvent(ev);
            PrintState();
        }
    }
}

