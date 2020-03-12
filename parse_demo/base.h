#pragma once
#ifndef __BASE_H
#define __BASE_H

/*
#define     START_X                 30 //数据开始横坐标
#define     START_Y                 30//数据开始纵坐标
#define     DRAW_WIDTH              965//数据区域宽度
#define     DRAW_HEIGHT             535//数据区域高度
#define     FOUR_BLOCK_COL_NUM      60//田字格列数
#define     FOUR_BLOCK_ROW_NUM      30//田字格行数
*/
//初始参数，起点位置，画布大小，定位矩形宽度
#define BEGIN_X			10
#define	BEGIN_Y			10
#define SOURCE_SIZE_WIDTH	1024
#define SOURCE_SIZE_HEIGHT	600
#define CONTOURS_LEN	50

//定位矩形起点位置，距离，
#define CONTOURS_X		(BEGIN_X + (CONTOURS_LEN/2))
#define CONTOURS_Y		(BEGIN_Y + (CONTOURS_LEN/2))
#define CONTOURS_WIDTH		SOURCE_SIZE_WIDTH - (2 * (BEGIN_X + CONTOURS_LEN))
#define CONTOURS_HEIGHT		SOURCE_SIZE_HEIGHT - (2*(BEGIN_Y + CONTOURS_LEN))

//数据区域起点位置和距离大小
#define START_X		(BEGIN_X + CONTOURS_LEN + 10)
#define START_Y		(BEGIN_Y + CONTOURS_LEN + 10)
#define DRAW_WIDTH	(CONTOURS_WIDTH - 20)
#define DRAW_HEIGHT	(CONTOURS_HEIGHT - 20)
#define	FOUR_BLOCK_ROW_NUM	6
#define	FOUR_BLOCK_COL_NUM	10

//demo图片保存路径
//#define	DEMO_DIR	"demo_block\\"
//#define DEMO_DIR	"610_bmp\\"
#define DEMO_DIR	"610_bmp\\tmp-"

#define NET_SOCKET

#endif
