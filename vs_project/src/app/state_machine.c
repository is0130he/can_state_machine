#include "state_machine.h"
#include <stdio.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

static EcuState current_state = STATE_INIT;

static const StateTransition transition_table[] = {
    /* INIT */
    { STATE_INIT,    APP_EVT_READY,  STATE_STANDBY },

    /* STANDBY */
    { STATE_STANDBY, APP_EVT_START,  STATE_ACTIVE  },
    { STATE_STANDBY, APP_EVT_RESET,  STATE_INIT    },

    /* ACTIVE */
    { STATE_ACTIVE,  APP_EVT_STOP,   STATE_STANDBY },
    { STATE_ACTIVE,  APP_EVT_FAULT,  STATE_ERROR   },
    /* RESET は定義しない */

    /* ERROR */
    { STATE_ERROR,   APP_EVT_RESET,  STATE_INIT    },
};


const int state_machine_table_size =
sizeof(transition_table) / sizeof(transition_table[0]);

/* 状態初期化処理 */
void StateMachine_Reset(EcuState init)
{
    current_state = init;
}

void StateMachine_Init(void)
{
    current_state = STATE_INIT;
}

EcuState GetState(void)
{
    return current_state;
}

void StateMachine_UpdateByEvent(AppEvent ev)
{
    for (size_t i = 0; i < ARRAY_SIZE(transition_table); i++) {
        if (transition_table[i].cur == current_state &&
            transition_table[i].ev == ev) {

            current_state = transition_table[i].next;
            return;
        }
    }
    /* 未定義遷移 → 状態維持 */
}

void PrintState(void)
{
    static const char* tbl[] = {
        "初期化",
        "待機",
        "稼働中",
        "エラー"
    };

    printf("状態 : %s\n", tbl[current_state]);
}
