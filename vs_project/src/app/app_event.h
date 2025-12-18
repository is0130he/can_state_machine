#ifndef APP_EVENT_H
#define APP_EVENT_H

/* アプリケーションイベント */
typedef enum {
    APP_EVT_READY,
    APP_EVT_START,
    APP_EVT_STOP,
    APP_EVT_RESET,
    APP_EVT_FAULT
} AppEvent;

const char* AppEventToString(AppEvent ev);

#endif
