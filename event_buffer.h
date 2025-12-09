#ifndef EVENT_BUFFER_H
#define EVENT_BUFFER_H

#include "can.h"

#define EVENT_BUF_SIZE 8

typedef struct {
    CanState buf[EVENT_BUF_SIZE];
    volatile int head;
    volatile int tail;
    volatile int count;
} EventQueue;


int  EventBuffer_Push(CanState ev);   // 成功:1 失敗:0
int  EventBuffer_Pop(CanState* ev);   // 成功:1 失敗:0

#endif

