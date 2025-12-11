#include <stdio.h>
#include "state_machine.h"
#include "event_buffer.h"

int main(void)
{
    char input;
    CanState ev;

    StateMachine_Reset(STATE_INIT);

    while(1)
    {
        /* --- 擬似 割り込み --- */
        input = getchar();                  
        Can_RxInterruptMock(input);

        /* --- メインループ処理 --- */
        if (EventBuffer_Pop(&ev)) {
            StateMachine_UpdateByEvent(ev);
            PrintState();
        }
    }
}

