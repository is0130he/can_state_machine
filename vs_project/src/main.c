#include <stdio.h>
#include <stdint.h>
#include <conio.h>

#include "driver/can.h"
#include "service/event_buffer.h"
#include "service/timeout.h"
#include "app/state_machine.h"

int main(void)
{
    int         ch;
    CanState    ev;
    EventSource src;

    /* 初期化 */
    EventBuffer_Init();
    Timeout_Init();
    StateMachine_Reset(STATE_INIT);
    PrintState();

    /* 簡易ループ (PC上) */
    while (1) {
        /* 現在状態を取得 */
        EcuState cur = GetState();

        /* ACTIVE状態のときだけタイマ監視を行う */
        if (cur == STATE_ACTIVE) {
            Timeout_Tick(10U);
        }

        /* キーが押された瞬間だけ処理(非ブロッキング) */
        if (_kbhit()) {
            ch = _getch();
            printf("Key='%c'\n", ch);  /* ← どれを押したか見えるようにする */
            Can_RxInterruptMock((char)ch);
        }

        /* キューからイベントを取り出して状態遷移 */
        while (EventBuffer_Pop(&ev, &src)) {
            printf("[%-6s] Event=%-6s → ",
                SrcToString(src),
                EventToString(ev));

            StateMachine_UpdateByEvent(ev);
            PrintState();
        }

        Sleep(1);
    }


    return 0;
}
