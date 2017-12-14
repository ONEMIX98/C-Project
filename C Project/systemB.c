/* �ɼ�����ϵͳ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 10 /*���γ�����*/
#define N 50 /*ѧ����󳤶�, ѧ������*/
typedef struct {
	char id[N];
	float score[M];
	float sum;
}Student;
typedef struct {
	int course; /*�γ�����*/
	int stu; /*ѧ������*/
}Num;
Num score(Student *stu);
void report(Student *stu, Num num);
void sort(Student *stu, Num num);
void search(Student *stu, Num num);

void main() {
	
	Num num;
	Student stu_score[N];
	Student stu_report[N];
	Student stu_sort[N];
	Student stu_search[N];
	num = score(stu_score);
	report(stu_report, num);
	sort(stu_sort, num);
	search(stu_search, num);
	system("pause");
}

Num score(Student *stu) {
	int i, j;
	Num num = { 0,0 };
	FILE *fp;
	errno_t err;
	char filename[10] = "score.txt";

	printf("����ѧ�������Ϳγ���Ŀ��");
	scanf_s("%d%d", &num.stu, &num.course);
	for (i = 0; i < num.stu; i++) {
		scanf_s("%s",stu[i].id, N);
		for (j = 0; j < num.course; j++) {
			scanf_s("%f", &stu[i].score[j]);
		}
	}
	getchar();
	printf("����ȷ�ϣ�\n");
	for (i = 0; i < num.stu; i++) {
		printf("%s ", stu[i].id);
		for (j = 0; j < num.course; j++) {
			printf("%.1f ", stu[i].score[j]);
		}
		printf("\n");
	}

	/*�����ļ�score.txt*/
	if ((err = fopen_s(&fp, filename, "w")) != 0) {
		printf("�޷��򿪴��ļ�\n");
		exit(0);
	}
	for (i = 0; i < num.stu; i++) {
		fprintf(fp, "%s ", stu[i].id);
		for (j = 0; j < num.course; j++) {
			fprintf(fp, "%.1f ", stu[i].score[j]);
		}
		fprintf(fp, "\n");
	}
	printf("�������ļ�\"%s\"\n",filename);
	fclose(fp);
	return num;
}

void report(Student *stu, Num num) {
	int i, j;
	char course = 'A';
	float max[M], min[M], average[M];
	FILE *in, *out;
	errno_t err;
	char filename_in[20] = "score.txt";
	char filename_out[20] = "report.txt";
	
	/*��score.txt��ȡ����*/
	if ((err = fopen_s(&in, filename_in, "r")) != 0) {
		printf("�޷���\"%s\"\n", filename_in);
		exit(0);
	}
	/*��ȡѧ��,����*/
	for (i = 0; i < num.stu; i++) {
		fscanf_s(in, "%s", stu[i].id, N);
		for (j = 0; j < num.course; j++) {
			fscanf_s(in, "%f", &stu[i].score[j]);
		}
	}

	/*���������Сƽ��ֵ*/
	for (j = 0; j < num.course; j++, course++) {
		average[j] = stu[0].score[j];
		max[j] = stu[0].score[j];
		min[j] = stu[0].score[j];
		printf("ͳ�����ݣ�\n");
		for (i = 1; i < num.stu; i++) {
			average[j] += stu[i].score[j];
			if (max[j] < stu[i].score[j]) max[j] = stu[i].score[j];
			if (min[j] > stu[i].score[j]) min[j] = stu[i].score[j];
		}
		average[j] /= num.stu;
		printf("�γ�%c����߷֣�%.2f, ��ͷ֣�%.2f, ƽ���֣�%.2f\n", course, max[j],min[j],average[j]);
	}
	/*ÿ���ܳɼ�*/
	for (i = 0; i < num.stu; i++) {
		stu[i].sum = stu[i].score[0];
		for (j = 1; j < num.course; j++) {
			stu[i].sum += stu[i].score[j];
		}
		printf("%s ���ܳɼ�Ϊ: %.2f\n", stu[i].id, stu[i].sum);
	}

	/*�����ļ�report.txt*/
	if ((err = fopen_s(&out, filename_out, "w")) != 0) {
		printf("�޷���\"%s\"\n", filename_out);
		exit(0);
	}
	fprintf(out, "�γ����� \t��߷� ��ͷ� ƽ����\n");
	for (course = 'A', j = 0; j < num.course; j++,course++) {
		fprintf(out, "    %c\t%7.2f%7.2f%7.2f\n", course, max[j], min[j], average[j]);
	}
	fprintf(out, "    ѧ��\t\t�ܳɼ�\n");
	for (i = 0; i < num.stu;i++) {
			fprintf(out, "%s\t%8.2f\n",stu[i].id, stu[i].sum);
		}
	fclose(out);
	printf("�������ļ�\"%s\"\n", filename_out);
	}

void sort(Student *stu, Num num) {
	void sort_by_final(Student *final_rank, Num num);
	void sort_by_course(Student *course_rank, Num num, int cour);
	int i, j;
	char course = 'A';
	Student course_rank[N];
	Student final_rank[N];
	FILE *in, *out;
	errno_t err;
	char filename_in[20] = "score.txt";
	char filename_out[20] = "sort.txt";
	/*��score.txt��ȡ����*/
	if ((err = fopen_s(&in, filename_in, "r")) != 0) {
		printf("�޷���\"%s\"\n", filename_in);
		exit(0);
	}
	/*��ȡѧ��,����*/
	for (i = 0; i < num.stu; i++) {
		fscanf_s(in, "%s", stu[i].id, N);
		for (j = 0; j < num.course; j++) {
			fscanf_s(in, "%f", &stu[i].score[j]);
		}
	}
	fclose(in);

	/*�����ļ�sort.txt*/
	if ((err = fopen_s(&out, filename_out, "w")) != 0) {
		printf("�޷���\"%s\"\n", filename_out);
		exit(0);
	}
	/*�����������ݷ������������ṹcourse_rank, final_rank��*/
	for (i = 0; i < num.stu; i++) {
		course_rank[i] = stu[i];
		final_rank[i] = stu[i];
	}

	/*������������Ļ���ļ���*/
	for (j = 0; j < num.course; j++, course++) {
		sort_by_course(course_rank, num, j);
		printf("���γ�%c������\n", course);
		fprintf(out, "���γ�%c������\n", course);
		for (i = 0; i < num.stu; i++) {
			printf("%s %.2f\n", course_rank[i].id, course_rank[i].score[j]);
			fprintf(out, "%s %.2f\n", course_rank[i].id, course_rank[i].score[j]);
		}
	}

	sort_by_final(final_rank, num);
	printf("���ܳɼ�������\n");
	fprintf(out, "���ܳɼ�������\n");
	for (i = 0; i < num.stu; i++) {
		printf("%s %.2f\n", final_rank[i].id, final_rank[i].sum);
		fprintf(out, "%s %.2f\n", final_rank[i].id, final_rank[i].sum);
	}
	printf("�������ļ�\"%s\"\n", filename_out);
	fclose(out);
}

void search(Student *stu, Num num) {
	char id[N];
	char course = 'A';
	int i, j;
	FILE *in, *out;
	errno_t err;
	char filename_in[20] = "score.txt";
	char filename_out[20] = "search.txt";

	printf("������Ҫ���ҵ�ѧ�ţ�");
	gets(id);
	/*��score.txt��ȡ����*/
	if ((err = fopen_s(&in, filename_in, "r")) != 0) {
		printf("�޷���\"%s\"\n", filename_in);
		exit(0);
	}
	/*��ȡѧ��,����*/
	for (i = 0; i < num.stu; i++) {
		fscanf_s(in, "%s", stu[i].id, N);
		for (j = 0; j < num.course; j++) {
			fscanf_s(in, "%f", &stu[i].score[j]);
		}
	}
	fclose(in);

	/*�����ļ�search.txt*/
	if ((err = fopen_s(&out, filename_out, "w")) != 0) {
		printf("�޷���\"%s\"\n", filename_out);
		exit(0);
	}
	/*���ÿ���˵��ܳɼ�*/
	for (i = 0; i < num.stu; i++) {
		stu[i].sum = 0;
		for (j = 0; j < num.course; j++) {
			stu[i].sum += stu[i].score[j];
		}
	}
	for (i = 0; i < num.stu; i++) {
		if (strcmp(id, stu[i].id) == 0) {
			printf("%s�ĳɼ�����\n", id);
			fprintf(out, "%s�ĳɼ�����\n", id);
			for (j = 0; j < num.course; j++,course++) {
				fprintf(out, "�γ�%c ", course);
				printf("�γ�%c ", course);
			}
			fprintf(out, "�ܳɼ�\n");
			printf("�ܳɼ�\n");
			for (j = 0; j < num.course; j++) {
				printf("%6.2f", stu[i].score[j]);
				fprintf(out, "%6.2f", stu[i].score[j]);
			}
			printf("%6.2f\n", stu[i].sum);
			fprintf(out, "%6.2f\n", stu[i].sum);
			break;
		}
	}
	if (i == num.stu) {
		printf("û���ҵ���ѧ����\n");
	}
	printf("�������ļ�\"%s\"\n", filename_out);
	fclose(out);
}

void sort_by_course(Student *course_rank, Num num, int cour) {
	int i, j, k;
	Student temp;
	/*ѡ������*/
	for (i = 0; i < num.stu-1; i++) {
		k = i;
		for (j = i + 1; j < num.stu; j++) {
			if (course_rank[i].score[cour] < course_rank[j].score[cour]) {
				k = j;
			}
		}
		if (k != i) {
			temp = course_rank[i];
			course_rank[i] = course_rank[k];
			course_rank[k] = temp;
		}
	}

}

void sort_by_final(Student *final_rank, Num num) {
	int i, j, k;
	Student temp;
	/*���ÿ���˵��ܳɼ�*/
	for (i = 0; i < num.stu; i++) {
		final_rank[i].sum = 0;
		for (j = 0; j < num.course; j++) {
			final_rank[i].sum += final_rank[i].score[j];
		}
	}
	/*ѡ������*/
	for (i = 0; i < num.stu - 1; i++) {
		k = i;
		for (j = i + 1; j < num.stu; j++) {
			if (final_rank[i].sum < final_rank[j].sum) {
				k = j;
			}
		}
		if (k != i) {
			temp = final_rank[i];
			final_rank[i] = final_rank[k];
			final_rank[k] = temp;
		}
	}

}
