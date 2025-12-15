#ifndef TIMEOUT_H
#define TIMEOUT_H

#include <stdint.h>
#include "event_buffer.h"

/* 初期化 */
void Timeout_Init(void);

/* 周期的に呼び出す（経過msを渡す） */
void Timeout_Tick(uint32_t elapsed_ms);

/* CANイベント受信時に呼ぶ：タイマをリセット */
void Timeout_OnCanEvent(void);

#endif
