/* �ɼ�����ϵͳ */

#include <stdio.h>
#include <stdlib.h>
#define M 4 /*�γ�����*/
#define N 50 /*ѧ����󳤶�, ѧ������*/
typedef struct {
	char id[N];
	float score[M];
}Student;
Student stu[N];
int record(Student *stu);
void report(Student *stu, int n);
void sort(Student *stu);
void search(Student *stu);

void main() {
	int n; /*¼��ɼ���ѧ������*/
	n = record(stu);
	report(stu, n);
	system("pause");
}

int record(Student *stu) {
	int i, j, n;
	FILE *fp;
	errno_t err;
	char filename[10] = "score.txt";

	printf("ѧ��������");
	scanf_s("%d", &n);
	for (i = 0; i < n; i++) {
		scanf_s("%s ",stu[i].id, N);
		for (j = 0; j < M; j++) {
			scanf_s("%f", &stu[i].score[j]);
		}
	}
	printf("����ȷ�ϣ�\n");
	for (i = 0; i < n; i++) {
		printf("%s ", stu[i].id);
		for (j = 0; j < M; j++) {
			printf("%.1f ", stu[i].score[j]);
		}
		printf("\n");
	}

	/*�����ļ�score.txt*/
	if ((err = fopen_s(&fp, filename, "w")) != 0) {
		printf("�޷��򿪴��ļ�\n");
		exit(0);
	}
	for (i = 0; i < n; i++) {
		fprintf(fp, "%s ", stu[i].id);
		for (j = 0; j < M; j++) {
			fprintf(fp, "%.1f ", stu[i].score[j]);
		}
		fprintf(fp, "\n");
	}
	printf("�������ļ�\"score.txt\"\n");
	fclose(fp);
	return n;
}

void report(Student *stu, int n) {
	int i, j;
	char course = 'A';
	float max[M], min[M], average[M], sum[N];
	FILE *fp;
	errno_t err;
	char filename[20] = "report.txt";
	/*���������Сƽ��ֵ*/
	for (j = 0; j < M; j++, course++) {
		average[j] = stu[0].score[j];
		max[j] = stu[0].score[j];
		min[j] = stu[0].score[j];
		printf("ͳ�����ݣ�\n");
		for (i = 1; i < n; i++) {
			average[j] += stu[i].score[j];
			if (max[j] < stu[i].score[j]) max[j] = stu[i].score[j];
			if (min[j] > stu[i].score[j]) min[j] = stu[i].score[j];
		}
		average[j] /= n;
		printf("�γ�%c����߷֣�%.2f, ��ͷ֣�%.2f, ƽ���֣�%.2f\n", course, max[j],min[j],average[j]);
	}
	/*ÿ���ܳɼ�*/
	for (i = 0; i < n; i++) {
		sum[i] = stu[i].score[0];
		for (j = 1; j < M; j++) {
			sum[i] += stu[i].score[j];
		}
		printf("%s ���ܳɼ�Ϊ: %.2f\n", stu[i].id, sum[i]);
	}

	/*�����ļ�report.txt*/
	if ((err = fopen_s(&fp, filename, "w")) != 0) {
		printf("�޷��򿪴��ļ�\n");
		exit(0);
	}
	fprintf(fp, "�γ����� \t��߷� ��ͷ� ƽ����\n");
	for (course = 'A', j = 0; j < M; j++,course++) {
		fprintf(fp, "    %c\t%7.2f%7.2f%7.2f\n", course, max[j], min[j], average[j]);
	}
	fprintf(fp, "    ѧ��\t\t�ܳɼ�\n");
	for (i = 0; i < n;i++) {
			fprintf(fp, "%s\t%8.2f\n",stu[i].id, sum[i]);
		}
	fclose(fp);
	printf("�������ļ�\"report.txt\"\n");
	}