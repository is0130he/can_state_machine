/* ヘッダガード */
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include"../driver/can.h"

/* ECUの状態 */
typedef enum {
	STATE_INIT,	/* 初期化 */
	STATE_STANDBY,	/* 待機	  */
	STATE_ACTIVE,	/* 稼働中 */
	STATE_ERROR,	/* エラー */
}EcuState;

typedef struct {
	EcuState current;
	CanState event;
	EcuState next;
} StateTransition;

#define SM_TABLE_SIZE  8

extern EcuState state;
extern StateTransition state_machine_table[SM_TABLE_SIZE];

/* プロトタイプ宣言 */
EcuState  GetState(void);				/* 現在状態の取得		*/
void PrintState(void);					/* 状態出力			*/
void StateMachine_Reset(EcuState init);
void StateMachine_UpdateByEvent(CanState ev);
const char* EventToString(CanState ev);


/* ヘッダガード */
#endif
