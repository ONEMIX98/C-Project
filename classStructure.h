#pragma once
#define M 10 /*���γ�����*/
#define N 50 /*ѧ�š�������󳤶�, ѧ������*/
typedef struct {
	char id[N]; /* ѧ��ѧ�� ����¼�˺� */
	char pwd[N]; /* ѧ������ */
	float score[M]; /* ���Ʒ��� */
	float sum; /* �ܷ� */
}Student;

typedef struct {
	int course; /*�γ�����*/
	int stu; /*ѧ������*/
}Num;