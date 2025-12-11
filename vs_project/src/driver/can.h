/* ヘッダガード */
#ifndef CAN_H
#define CAN_H

#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

/* Windows/Linux 差分は一旦無効化（ビルド確認優先） */
/* #include <windows.h> */
/* #include <unistd.h> */


/* CAN受信状態 */
typedef enum {
	READY,
	START,
	STOP,
	RESET,
	FAULT,
	STATE_INVALID,
	CAN_STATE_MAX = STATE_INVALID
}CanState;

/* CANメッセージ仕様 */
typedef struct {
	uint32_t id;        /* CAN ID			*/
	uint8_t  data[8];   /* 8バイトデータ	*/
	uint8_t  dlc;       /* Data Length		*/
} CanFrame;

/* テーブル */
extern CanFrame can_table[CAN_STATE_MAX];

/* プロトタイプ宣言 */
CanState	CheckCanFrame(const CanFrame* frame);		/* CANフレームチェック処理	*/
void		Can_RxInterruptMock(char in_ch);

/* ヘッダガード */
#endif
