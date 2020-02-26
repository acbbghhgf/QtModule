#pragma once
#ifndef __USER_H__
#define __USER_H__

#include <stdio.h>
#include <stdlib.h>
#include "sqlite/sqlite3.h"
#include <string.h>

#define DB_FILE     "mdata.db"

typedef struct mdata{
    int id;
    int x1;//���ָ�top_left_x
    int y1;//���ָ�top_left_y
    int x2;//���ָ�tail_right_x
    int y2;//���ָ�tail_right_y
    float white_counter;//��ɫ��Сֵ
    float black_counter;//��ɫ���ֵ
    float threshold;//������ֵ
}mdata_t;

// ʹ�ýṹ�����������ݿ��е�����
typedef struct USER {
    mdata_t data;
    struct USER* next;// ���ݴ����ݿ�����ȡ��������������
} User;

// ��ѯuser��Demo
void userDemo(void);
// ��ѯ����ʱ�Ļص�����
static int select_callback(void* data, int col_count, char** col_values, char** col_name);
// ��ӡUserLinked����
void printUserLinked(User* userLinked);
// ��ȡUserLinked����
User* getUserLinked(char* sql);
// �ͷ������е�����
void freeUserLinked(User* userLinked);
// �������ݿ�



//�������ݿ�
int my_table_create(void);
//ɾ�����ݿ�
int my_table_drop(void);
//������ݿ�
int my_table_clear(void);

int execUserDB(char* sql);

int my_table_replace(int id_value, int x1_value, int y1_value, int x2_value, int y2_value, int white_counter, int black_counter, int threshold);
int my_table_replace_withmdata(mdata_t* d);

int my_table_query_print(void);

//��ѯ���ݿⷵ������������ʹ�õ�ʱ����ҪfreeUserLinked�ͷ�
User* my_table_query(void);

#endif
