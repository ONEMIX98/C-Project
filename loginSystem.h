#pragma once
#define MAX_PWD 50
#define MAX_USER 50
char *login(int choice); /*��¼ϵͳ����¼ʧ�ܷ���-1���ɹ�����ѧ����ţ���Ϊ��ʦ���طǸ�ֵ��*/
void welcome(int *ptchoice); /* ����ѡ���ں����иı�ѡ�� */
void passwd(char *pwd); /*��������Ǻ�*/
void teacher(); /*��ʦ��������*/
void student(char *id); /*ѧ���������棬���Բ�ѯ�Լ��ĳɼ����޸�����*/
