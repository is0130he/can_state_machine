#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "app_event.h"

typedef enum {
	STATE_INIT,	/* 初期化 */
	STATE_STANDBY,	/* 待機	  */
	STATE_ACTIVE,	/* 稼働中 */
	STATE_ERROR,	/* エラー */
} EcuState;

typedef struct {
    EcuState  cur;
    AppEvent  ev;
    EcuState  next;
} StateTransition;

/* プロトタイプ宣言 */
void StateMachine_Init(void);
void StateMachine_UpdateByEvent(AppEvent ev);
EcuState GetState(void);
void PrintState(void);

#endif
