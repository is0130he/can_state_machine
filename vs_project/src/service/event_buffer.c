#include "event_buffer.h"

/* 静的なキュー 1個だけ運用 */
static EventQueue s_queue;

/* 実機移植用フック（今は何もしない） */
static void EnterCritical(EventSource src)
{
    (void)src;
    /* 実機ではここで割り込み禁止などを行う
       例: if (src == EVENT_SRC_ISR) { DISABLE_IRQ(); } */
}

static void LeaveCritical(EventSource src)
{
    (void)src;
    /* 実機ではここで割り込み許可などを行う
       例: if (src == EVENT_SRC_ISR) { ENABLE_IRQ(); } */
}

void EventBuffer_Init(void)
{
    s_queue.head = 0;
    s_queue.tail = 0;
    s_queue.count = 0;
}

/* 返り値: 成功=1 / 失敗(満杯)=0 */
int EventBuffer_Push(CanState ev, EventSource src)
{
    int next;

    if (ev >= CAN_STATE_MAX) {
        return 0; /* 不正値ガード */
    }

    EnterCritical(src);

    if (s_queue.count >= EVENT_BUF_SIZE) {
        /* 満杯 → ロス検出 */
        LeaveCritical(src);
        return 0;
    }

    next = s_queue.head;

    s_queue.buf[next].ev = ev;
    s_queue.buf[next].src = src;

    s_queue.head = (next + 1) % EVENT_BUF_SIZE;
    s_queue.count++;

    LeaveCritical(src);
    return 1;
}

/* 返り値: 成功=1 / 失敗(空)=0 */
int EventBuffer_Pop(CanState* ev, EventSource* src)
{
    if ((ev == NULL) || (src == NULL)) {
        return 0;
    }

    EnterCritical(EVENT_SRC_TASK);

    if (s_queue.count <= 0) {
        LeaveCritical(EVENT_SRC_TASK);
        return 0;
    }

    *ev = s_queue.buf[s_queue.tail].ev;
    *src = s_queue.buf[s_queue.tail].src;

    s_queue.tail = (s_queue.tail + 1) % EVENT_BUF_SIZE;
    s_queue.count--;

    LeaveCritical(EVENT_SRC_TASK);
    return 1;
}

const char* SrcToString(EventSource src)
{
    switch (src) {
    case EVENT_SRC_ISR:   return "ISR";
    case EVENT_SRC_TASK:  return "TASK";
    case EVENT_SRC_TIMER: return "TIMER";
    default:              return "UNKNOWN";
    }
}
