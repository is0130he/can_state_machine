#include<stdio.h>
#include<string.h>
#include"can.h"
#include "event_buffer.h"

/* テーブル */
CanFrame can_table[CAN_STATE_MAX] = {
/*              CAN ID          data[0]の値                                                     Data length */
        {       .id = 0x100,    .data = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},       .dlc = 0x01  },       /* READY */
        {       .id = 0x101,    .data = {0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},       .dlc = 0x02  },       /* START */
        {       .id = 0x102,    .data = {0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00},       .dlc = 0x03  },	      /* STOP  */
	{	.id = 0x103,	.data = {0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	.dlc = 0x01  },       /* RESET */
	{	.id = 0x104,	.data = {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	.dlc = 0x01  }	      /* FAULT */
};

/* CANフレームチェック処理 */
CanState  CheckCanFrame(const CanFrame* frame){
	int i;				/* カウンタ変数 */

	/* NULLチェック*/
	if(frame == NULL){
    		return STATE_INVALID;
	}

    	/* DLC 異常値ガード */
    	if((0 == frame->dlc) || 
	   (frame->dlc > 8)){
        	return STATE_INVALID;
    	}

        /* 受信状態チェック */
        /* 各テーブルごとに比較 */
        for(i=0;i < CAN_STATE_MAX;i++){
                /* CAN ID一致確認 */
                if(can_table[i].id == frame->id){
                        /* 8バイトデータ比較 */
                        if(0 == memcmp((can_table[i].data),(frame->data) ,frame->dlc)){
				if(can_table[i].dlc == frame->dlc){
                                	/* すべて一致した場合、受信データが0xFF⇒ 0~2に更新される*/
                                	return i;
				}
                        }
                }
        }

	return STATE_INVALID;
}

/* 受信フレーム */
void Can_RxInterruptMock(char input)
{
    CanFrame frame;

    memset(&frame, 0, sizeof(frame));

    if('r'==input){
        frame.id = 0x100; frame.dlc = 1; frame.data[0] = 0x01;
    }
    else if('s'==input){
        frame.id = 0x101; frame.dlc = 2; frame.data[0] = 0x02; frame.data[1]=0x02;
    }
    else if('t'==input){
        frame.id = 0x102; frame.dlc = 3;
        frame.data[0]=0x03; frame.data[1]=0x03; frame.data[2]=0x03;
    }
    else if (input == 'e') { // FAULT
        frame.id = 0x104; frame.dlc = 1; frame.data[0] = 0xFF;
    }
    else if (input == 'x') { // RESET
        frame.id = 0x103; frame.dlc = 1; frame.data[0] = 0x04;
    }
    else {
        return;
    }

    CanState ev = CheckCanFrame(&frame);
    EventBuffer_Push(ev);
}

