#include "event_buffer.h"

static EventQueue queue = { .head = 0, .tail = 0, .count = 0 };

int EventBuffer_Push(CanState ev)
{
    if (queue.count >= EVENT_BUF_SIZE) {
        return 0;   // フル
    }

    queue.buf[queue.tail] = ev;
    queue.tail = (queue.tail + 1) % EVENT_BUF_SIZE;
    queue.count++;

    return 1;       // 成功
}

int EventBuffer_Pop(CanState* ev)
{
    if (queue.count == 0) {
        return 0;   // 空
    }

    *ev = queue.buf[queue.head];
    queue.head = (queue.head + 1) % EVENT_BUF_SIZE;
    queue.count--;

    return 1;       // 取得成功
}

