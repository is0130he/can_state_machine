#include "event_buffer.h"

static EventQueue queue = { 0, 0, 0 };

int EventBuffer_Push(CanState ev)
{
    if (queue.count >= EVENT_BUF_SIZE) {
        return 0;   /* ƒtƒ‹ */
    }

    queue.buf[queue.tail] = ev;
    queue.tail = (queue.tail + 1) % EVENT_BUF_SIZE;
    queue.count++;

    return 1;       /* ¬Œ÷ */
}

int EventBuffer_Pop(CanState* ev)
{
    if (queue.count == 0) {
        return 0;   /* ‹ó */
    }

    *ev = queue.buf[queue.head];
    queue.head = (queue.head + 1) % EVENT_BUF_SIZE;
    queue.count--;

    return 1;       /* æ“¾¬Œ÷ */
}

