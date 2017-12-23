/* �ɼ�����ϵͳ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 10 /*���γ�����*/
#define N 50 /*ѧ�š�������󳤶�, ѧ������*/
#define USER "admin"
#define PWD "admin"
#define MAX_PWD 50
#define MAX_USER 50


typedef struct {
	char id[N];
	char pwd[N];
	float score[M];
	float sum;
}Student;
typedef struct {
	int course; /*�γ�����*/
	int stu; /*ѧ������*/
}Num;

char *login(int choice); /*��¼ϵͳ����¼ʧ�ܷ���-1���ɹ�����ѧ����ţ���Ϊ��ʦ���طǸ�ֵ��*/
Num score();
void report( Num num);
void sort( Num num);
void search( Num num);
void student_search(char *id);
void modify(char *id); /*�޸�����*/
void teacher(); /*��ʦ��������*/
void student(char *id); /*ѧ���������棬���Բ�ѯ�Լ��ĳɼ����޸�����*/

Num num = { 0, 0 };

void main() {
	int choice; /*�˵�ѡ�����*/
	char *which;
	/* ���Ѿ�������info.txt�����info.txt��ȡѧ�����γ�������ѧ�� */
	FILE *fp;
	errno_t err;
	char filename[20] = "info.txt";
	if ((err = fopen_s(&fp, filename, "r")) == 0) {
		/*��ȡ����*/
		fscanf_s(fp, "%d %d", &num.stu, &num.course);
		fclose(fp);
	}
	
	printf("\t-----------------��ӭʹ��ѧ���ɼ�����ϵͳ��----------------------\n");
	printf("\t| ��ʦ��¼                                            \t- ������1 |\n");
	printf("\t| ѧ����¼                                            \t- ������2 |\n");
	printf("\t| �˳�                                            \t- ������3 |\n");
	printf("\n��������ѡ��");
	scanf_s("%d", &choice);
	getchar();
	while (choice != 1 && choice != 2) {
		if (choice == 3) {
			printf("�ɹ��˳���\n");
			system("pause");
			return;
		}
		printf("������������������:");
		scanf_s("%d", &choice);
		getchar();
	}
	/*ͨ��login()����ֵ�ж��û���ݣ�����֤ͨ����������������*/
	if (choice == 1 && *(which=login(choice)) != '-1') {
		printf("\n��ʦ%s, ���ѳɹ���¼��\n\n", USER);
		system("pause");
		system("cls");
		teacher();
	}
	if (choice == 2 && *(which=login(choice)) != '-1') {
		printf("\nѧ��%s, ���ѳɹ���¼��\n\n", which);
		system("pause");
		system("cls");
		/* �����ص�ѧ�ű��浽�����У������ݸ�student����*/
		char id[MAX_USER];
		strcpy_s(id, MAX_USER, which);
		student(id);
	}
	
}

Num score() {
	Student stu[N];
	int i, j;
	FILE *fp;
	errno_t err;
	char filename1[10] = "score.txt";
	char filename2[10] = "info.txt"; /* ��ŵ�ǰ�Ѽ�¼ѧ���������γ�����ѧ�����˺ţ�ѧ�ţ������루��ʼֵΪѧ�ţ�*/

	printf("������ѧ�������Ϳγ���Ŀ��");
	scanf_s("%d%d", &num.stu, &num.course);
	printf("������ѧ����ѧ�źͳɼ���\n");
	for (i = 0; i < num.stu; i++) {
		scanf_s("%s", stu[i].id, N);
		for (j = 0; j < num.course; j++) {
			scanf_s("%f", &stu[i].score[j]);
		}
	}
	getchar();
	printf("---------------------------------------\n");
	getchar();
	printf("����ȷ�ϣ�\n");
	for (i = 0; i < num.stu; i++) {
		printf("%s ", stu[i].id);
		for (j = 0; j < num.course; j++) {
			printf("%.1f ", stu[i].score[j]);
		}
		printf("\n");
	}
	printf("\n");

	/*�����ļ�score.txt*/
	if ((err = fopen_s(&fp, filename1, "w")) != 0) {
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
	printf("�������ļ�\"%s\"\n", filename1);
	fclose(fp);

	/*�����ļ�info.txt*/
	if ((err = fopen_s(&fp, filename2, "w")) != 0) {
		printf("�޷��򿪴��ļ�\n");
		exit(0);
	}
	fprintf(fp, "%d %d\n", num.stu, num.course);
	for (i = 0; i < num.stu; i++) {
		strcpy_s(stu[i].pwd, N, stu[i].id); /*��ʼ����Ϊѧ��*/
		fprintf(fp, "%s %s", stu[i].id, stu[i].pwd);
		fprintf(fp, "\n");
	}
	printf("�������ļ�\"%s\"\n", filename2);
	fclose(fp);

	return num;
}

void report( Num num) {
	Student stu[N];
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
		printf("�γ�%c����߷֣�%.2f, ��ͷ֣�%.2f, ƽ���֣�%.2f\n", course, max[j], min[j], average[j]);
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
	for (course = 'A', j = 0; j < num.course; j++, course++) {
		fprintf(out, "    %c\t%7.2f%7.2f%7.2f\n", course, max[j], min[j], average[j]);
	}
	fprintf(out, "    ѧ��\t\t�ܳɼ�\n");
	for (i = 0; i < num.stu; i++) {
		fprintf(out, "%s\t%8.2f\n", stu[i].id, stu[i].sum);
	}
	fclose(out);
	printf("�������ļ�\"%s\"\n", filename_out);
}

void sort( Num num) {
	Student stu[N];
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

void search( Num num) {
	Student stu[N];
	char id[N];
	char course = 'A';
	int i, j;
	FILE *in, *out;
	errno_t err;
	char filename_in[20] = "score.txt";
	char filename_out[20] = "search.txt";

	printf("������Ҫ���ҵ�ѧ�ţ�");
	scanf_s("%s", id, N);
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
	/* ���ɼ���ӡ����Ļ+�ļ��� */
	for (i = 0; i < num.stu; i++) {
		if (strcmp(id, stu[i].id) == 0) {
			printf("ѧ��%s�ĳɼ�����\n", id);
			fprintf(out, "ѧ��%s�ĳɼ�����\n", id);
			for (j = 0; j < num.course; j++, course++) {
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
	Student stu[N];
	int i, j, k;
	Student temp;
	/*ѡ������*/
	for (i = 0; i < num.stu - 1; i++) {
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
	Student stu[N];
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

void teacher() {
	Student stu[N];
	int choice;
	while (1) { 
		printf("\t-----------------��ӭʹ��ѧ���ɼ�����ϵͳ��----------------------\n");
		printf("\t| �ɼ���ʼ��¼��                                   \t- ������1 |\n");
		printf("\t| ������Ƴɼ�����߷���ͷ�ƽ���ּ�ÿ�˵��ܳɼ� \t- ������2 |\n");
		printf("\t| ���յ��Ƴɼ��͸����ܳɼ����н�������                  - ������3 |\n");
		printf("\t| ��ѧ�Ų�ѯѧ���ĸ��Ƴɼ�                         \t- ������4 |\n");
		printf("\t| �������ܾ����ڴ�...                             \t          |\n");
		printf("\t|                                                \t          |\n");
		printf("\t|                                                \t          |\n");
		printf("\t| �˳�                                            \t- ������5 |\n");
		printf("\t-----------------------------------------------------------------\n");
		printf("���ѡ���ǣ�  ");
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 1: printf("-----------------����¼��---------------\n");
			num = score(score);
			printf("-----------------¼�����---------------\n");
			break;
		case 2: printf("-----------------�ɼ�����--------------\n");
			report(num);
			printf("-----------------�������--------------\n");
			break;
		case 3: printf("-----------------�ɼ�����--------------\n");
			sort(num);
			printf("-----------------�������--------------\n");
			break;
		case 4: printf("-----------------�ɼ���ѯ--------------\n");
			search(num);
			printf("-----------------��ѯ���--------------\n");
			break;
		case 5: printf("-----------------�˳�ϵͳ--------------\n");
			return;
		}
		system("pause");
		system("cls");
		printf("\n\n");
	}
}

void student(char *id){
	Student stu[N];
	int choice;
	while (1) {
		printf("\t-----------------��ӭʹ��ѧ���ɼ�����ϵͳ��----------------------\n");
		printf("\t| �ɼ���ѯ                                            \t- ������1 |\n");
		printf("\t| �޸�����                                            \t- ������2 |\n");
		printf("\t| �˳�                                            \t- ������3 |\n");
		printf("\t-----------------------------------------------------------------\n");
		printf("���ѡ���ǣ�  ");
		scanf_s("%d", &choice);
		

		switch (choice)
		{
		case 1: printf("-----------------�ɼ���ѯ--------------\n");
			student_search(id);
			printf("-----------------��ѯ���--------------\n");
			break;
		case 2: printf("-----------------�޸�����--------------\n");
			modify(id);
			printf("-----------------�޸ĳɹ�--------------\n");
			break;
		case 3: printf("-----------------�˳�ϵͳ--------------\n");
			return;
		}
		system("pause");
		system("cls");
		printf("\n\n");
	}
}

char* login(int choice) {
	char user[MAX_USER], teacher_user[MAX_USER] = USER;
	char pwd[MAX_PWD], teacher_pwd[MAX_PWD] = PWD;
	char *which = "0"; /*��¼�ɹ�����ֵ��ѧ��ѧ��*/
	char *fail = "-1";/*��¼ʧ�ܷ���ֵ*/
	int count = 0;
	int i=0;
	Student stu[N];

	/*��ʦ���û���Ϊadmin*/
	if (choice == 1) {
		do
		{
			if (count == 3) {
				printf("\t��������������룬ϵͳ���رգ�\n");
				return fail;
			}
			else if (count > 0)
				printf("\t�������������%d�λ��ᣡ\n", (3 - count));

			printf("\n�û�����");
			gets(user);
			printf("\n���룺");
			gets(pwd);
			count++;

		} while ((strcmp(user, teacher_user)) || (strcmp(pwd, teacher_pwd))); /*ѭ��������������˺Ų�ƥ��*/
	}
	
	if (choice == 2) {
		int i;
		FILE *in;
		errno_t err;
		char filename_in[20] = "info.txt";
		int success = 0; /*�ɹ���¼�ı��*/

		/*��info.txt��ȡ����*/
		if ((err = fopen_s(&in, filename_in, "r")) != 0) {
			printf("�޷���\"%s\"\n", filename_in);
			exit(0);
		}
		/*��ȡѧ����ѧ��,����*/
		int temp1=0, temp2=0;
		fscanf_s(in, "%d %d", &temp1, &temp2);
		for (i = 0; i < num.stu; i++) {
			fscanf_s(in, "%s %s", stu[i].id, N, stu[i].pwd, N);
		}
		fclose(in);
		
		/*���û������˺�����*/
		do
		{
			if (count == 3) {
				printf("\t��������������룬ϵͳ���رգ�\n");
				return fail;
			}
			else if (count > 0)
				printf("\n�������������%d�λ���!", (3 - count));

			printf("\n�û�����");
			gets(user);
			printf("\n���룺");
			gets(pwd);
			count++;

			for (i = 0; i < num.stu; i++) {
				if (strcmp(user, stu[i].id) == 0 && strcmp(pwd, stu[i].pwd) == 0) {
					which = stu[i].id;
					success = 1;
					break;
					}
				}
			if (success) break;
		} while (1);
	}
	return which;
}

void modify(char *id) {
	int i;
	FILE *fp;
	errno_t err;
	char filename[20] = "info.txt";
	int success = 0; /*�ɹ���¼�ı��*/
	Student stu[N];

	 /*��info.txt��ȡ����*/
	if ((err = fopen_s(&fp, filename, "r")) != 0) {
		printf("�޷���\"%s\"\n", filename);
		exit(0);
	}
	/*��ȡѧ����ѧ��,����*/
	int temp1 = 0, temp2 = 0;
	fscanf_s(fp, "%d %d", &temp1, &temp2);
	for (i = 0; i < num.stu; i++) {
		fscanf_s(fp, "%s %s", stu[i].id, N, stu[i].pwd, N);
	}
	fclose(fp);

	for (i = 0; i < num.stu; i++) {
		if (strcmp(id, stu[i].id) == 0) {
			char confirm_pwd[MAX_PWD];
			char new_pwd[MAX_PWD];
			printf("�����������룺");
			scanf_s("%s", new_pwd, MAX_PWD);
			printf("��ȷ�������룺");
			scanf_s("%s", confirm_pwd, MAX_PWD);
			if (strcmp(new_pwd, confirm_pwd) == 0) {
				strcpy_s(stu[i].pwd, N, new_pwd);
				printf("�޸ĳɹ���\n");
			}
		}
		/* �޸�info.txt �ļ� */
		if ((err = fopen_s(&fp, filename, "w")) != 0) {
			printf("�޷���\"%s\"\n", filename);
			exit(0);
		}
		fprintf(fp, "%d %d", num.stu, num.course);
		fprintf(fp, "\n");
		for (i = 0; i < num.stu; i++) {
			fprintf(fp, "%s %s\n", stu[i].id, stu[i].pwd);
		}
		fclose(fp);


	}

}

void student_search(char *id) {
	int i, j;
	FILE *in;
	errno_t err;
	char filename_in[20] = "info.txt";
	int success = 0; /*�ɹ���¼�ı��*/
	Student stu[N];
	char course = 'A';

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
	/*���ÿ���˵��ܳɼ�*/
	for (i = 0; i < num.stu; i++) {
		stu[i].sum = 0;
		for (j = 0; j < num.course; j++) {
			stu[i].sum += stu[i].score[j];
		}
	}
	/* ���ɼ���ӡ����Ļ�� */
	for (i = 0; i < num.stu; i++) {
		if (strcmp(id, stu[i].id) == 0) {
			printf("ѧ��%s�ĳɼ�����\n", id);
			for (j = 0; j < num.course; j++, course++) {
				printf("�γ�%c ", course);
			}
			printf("�ܳɼ�\n");
			for (j = 0; j < num.course; j++) {
				printf("%6.2f", stu[i].score[j]);
			}
			printf("%6.2f\n", stu[i].sum);
			break;
		}
	}
}

