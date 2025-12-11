/* ヘッダガード */
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include"can.h"

/* ECUの状態 */
typedef enum{
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

extern EcuState state;
extern StateTransition state_machine_table[8];

/* プロトタイプ宣言 */
EcuState  GetState(void);				/* 現在状態の取得		*/
void PrintState(void);					/* 状態出力			*/
void StateMachine_Reset(EcuState init);
void StateMachine_UpdateByEvent(CanState ev);

#define SM_TABLE_SIZE  (sizeof(state_machine_table)/sizeof(state_machine_table[0]))

/* ヘッダガード */
#endif
