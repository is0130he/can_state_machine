#include <stdio.h>
#include <stdint.h>
#include <conio.h>

#include "driver/can.h"
#include "service/event_buffer.h"
#include "service/timeout.h"
#include "app/state_machine.h"
#include "app/event_dispatch.h"
#include "app/app_event.h"


static int logged_ready_in_active = 0;

int main(void)
{
    int         ch;
    AppEvent    ev;
    EventSource src;
    EcuState    cur;

    /* 初期化 */
    EventBuffer_Init();
    Timeout_Init();
    StateMachine_Reset(STATE_INIT);
    PrintState();

    /* 簡易ループ (PC上) */
    while (1) {
        /* 現在状態を取得 */
        cur = GetState();

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
            EventDispatch_Process(ev, src);
        }

        Sleep(1);
    }


    return 0;
}
