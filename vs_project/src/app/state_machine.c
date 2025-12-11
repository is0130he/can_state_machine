#include<stdio.h>
#include"state_machine.h"

StateTransition state_machine_table[8] = {
	/*              現在状態        受信イベント    遷移後状態*/
			{       STATE_INIT,     READY,          STATE_STANDBY   },
			{       STATE_STANDBY,  START,          STATE_ACTIVE    },
			{       STATE_ACTIVE,   STOP,           STATE_STANDBY   },
			{ 		STATE_STANDBY,  FAULT,  		STATE_ERROR		},
			{ 		STATE_ACTIVE,   FAULT,  		STATE_ERROR		},
			{ 		STATE_ERROR,    RESET,  		STATE_INIT		},
			{ 		STATE_STANDBY,  RESET,  		STATE_INIT		},
			{ 		STATE_ACTIVE,   RESET,  		STATE_INIT		}
};

const int state_machine_table_size =
sizeof(state_machine_table) / sizeof(state_machine_table[0]);

EcuState state = STATE_INIT;

/* 状態初期化処理 */
void StateMachine_Reset(EcuState init)
{
	state = init;
}

/* 現在状態の取得 */
EcuState GetState(void) {
	return state;
}

/* 状態出力 */
void PrintState(void) {
	/* 初期化状態 */
	if (STATE_INIT == state) {
		printf("状態 : 初期化\n");
	}
	/* 待機状態 */
	else if (STATE_STANDBY == state) {
		printf("状態 : 待機\n");
	}
	/* 稼働中 */
	else if (STATE_ACTIVE == state) {
		printf("状態 : 稼働中\n");
	}
	/* エラー */
	else if (STATE_ERROR == state) {
		printf("状態 : エラー\n");
	}
	/* 不正状態 */
	else {
		printf("状態 : 不正\n");
	}
}

/* 状態遷移処理 */
void StateMachine_UpdateByEvent(CanState ev)
{
	int i;

	for (i = 0; i < SM_TABLE_SIZE; i++) {
		if (state_machine_table[i].current == state &&
			state_machine_table[i].event == ev) {

			state = state_machine_table[i].next;
			return;
		}
	}

	printf("Illegal transition cur=%d ev=%d\n", state, ev);
}

