#pragma once
#ifndef __BASE_H
#define __BASE_H

/*
#define     START_X                 30 //���ݿ�ʼ������
#define     START_Y                 30//���ݿ�ʼ������
#define     DRAW_WIDTH              965//����������
#define     DRAW_HEIGHT             535//��������߶�
#define     FOUR_BLOCK_COL_NUM      60//���ָ�����
#define     FOUR_BLOCK_ROW_NUM      30//���ָ�����
*/
//��ʼ���������λ�ã�������С����λ���ο��
#define BEGIN_X			10
#define	BEGIN_Y			10
#define SOURCE_SIZE_WIDTH	1024
#define SOURCE_SIZE_HEIGHT	600
#define CONTOURS_LEN	50

//��λ�������λ�ã����룬
#define CONTOURS_X		(BEGIN_X + (CONTOURS_LEN/2))
#define CONTOURS_Y		(BEGIN_Y + (CONTOURS_LEN/2))
#define CONTOURS_WIDTH		SOURCE_SIZE_WIDTH - (2 * (BEGIN_X + CONTOURS_LEN))
#define CONTOURS_HEIGHT		SOURCE_SIZE_HEIGHT - (2*(BEGIN_Y + CONTOURS_LEN))

//�����������λ�ú;����С
#define START_X		(BEGIN_X + CONTOURS_LEN + 10)
#define START_Y		(BEGIN_Y + CONTOURS_LEN + 10)
#define DRAW_WIDTH	(CONTOURS_WIDTH - 20)
#define DRAW_HEIGHT	(CONTOURS_HEIGHT - 20)
#define	FOUR_BLOCK_ROW_NUM	6
#define	FOUR_BLOCK_COL_NUM	10

//demoͼƬ����·��
//#define	DEMO_DIR	"demo_block\\"
//#define DEMO_DIR	"610_bmp\\"
#define DEMO_DIR	"610_bmp\\tmp-"

#define NET_SOCKET

#endif
