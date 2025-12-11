#ifndef EVENT_BUFFER_H
#define EVENT_BUFFER_H

#include "../driver/can.h"

#define EVENT_BUF_SIZE 8

typedef struct {
    CanState buf[EVENT_BUF_SIZE];
    volatile int head;
    volatile int tail;
    volatile int count;
} EventQueue;


int  EventBuffer_Push(CanState ev);   /* ê¨å˜:1 é∏îs:0 */
int  EventBuffer_Pop(CanState* ev);   /* ê¨å˜:1 é∏îs:0 */

#endif

