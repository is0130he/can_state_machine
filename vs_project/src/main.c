#include <stdio.h>
#include <stdint.h>

#include "driver/can.h"
#include "service/event_buffer.h"
#include "service/timeout.h"
#include "app/state_machine.h"

int main(void)
{
    /* 初期化 */
    EventBuffer_Init();
    Timeout_Init();
    StateMachine_Reset(STATE_INIT);
    PrintState();

    /* 簡易ループ (PC上) */
    while (1) {
        /* ① ここで擬似的に割り込みを発生させる (キー入力など) */
        int ch = getchar();       /* 本当は非ブロッキングが理想 */
        Can_RxInterruptMock((char)ch);

        /* ② タイマを進める (10ms経過した想定など) */
        Timeout_Tick(10U);

        /* ③ キューからイベントを取り出して状態遷移 */
        CanState    ev;
        EventSource src;

        while (EventBuffer_Pop(&ev, &src)) {
            /* 今回は src はログ用・将来の拡張用に持っておく */
            StateMachine_UpdateByEvent(ev);
            PrintState();
        }

        /* 実機ならここで TaskDelay(10ms) やスリープなど */
    }

    return 0;
}
