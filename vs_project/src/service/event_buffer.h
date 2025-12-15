#ifndef EVENT_BUFFER_H
#define EVENT_BUFFER_H

#include "../driver/can.h"

/* イベント発行元の種類 */
typedef enum {
    EVENT_SRC_ISR = 0,   /* 割り込み(ISR) からのイベント */
    EVENT_SRC_TASK,      /* 通常タスク/メインループから */
    EVENT_SRC_TIMER      /* ソフトタイマから */
} EventSource;

#define EVENT_BUF_SIZE 8

/* キューに積む1件分のエントリ */
typedef struct {
    CanState    ev;      /* どのイベントか（READY/START/STOP/...） */
    EventSource src;     /* どこから来たか（ISR/TASK/TIMER）      */
} EventEntry;

/* リングバッファ本体 */
typedef struct {
    EventEntry   buf[EVENT_BUF_SIZE];
    volatile int head;
    volatile int tail;
    volatile int count;
} EventQueue;

/* 初期化 */
void EventBuffer_Init(void);

/* 返り値: 成功=1 / 失敗(満杯など)=0 */
int  EventBuffer_Push(CanState ev, EventSource src);
/* 返り値: 成功=1 / 失敗(空)=0 */
int  EventBuffer_Pop(CanState* ev, EventSource* src);

#endif