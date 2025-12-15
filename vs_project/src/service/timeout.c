#include "timeout.h"

/* タイムアウト時間(ms) 例: 1000ms = 1秒 */
#define CAN_TIMEOUT_MS   1000U

static uint32_t s_can_elapsed_ms = 0U;

void Timeout_Init(void)
{
    s_can_elapsed_ms = 0U;
}

void Timeout_OnCanEvent(void)
{
    /* 正常なCANイベントを受信したらタイマをリセット */
    s_can_elapsed_ms = 0U;
}

void Timeout_Tick(uint32_t elapsed_ms)
{
    if (s_can_elapsed_ms < CAN_TIMEOUT_MS) {
        s_can_elapsed_ms += elapsed_ms;

        if (s_can_elapsed_ms >= CAN_TIMEOUT_MS) {
            /* ★ タイムアウト発生 → FAULTイベントを TIMER 由来として発行 */
            (void)EventBuffer_Push(FAULT, EVENT_SRC_TIMER);
        }
    }
}
