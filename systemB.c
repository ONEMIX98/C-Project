/* 成绩管理系统 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "classStructure.h"
#include "loginSystem.h"
#include "coreFunction.h"

Num num = { 0, 0 }; /*全局变量，携带学生数和课程数*/

void main() {
	int choice; /*菜单选择变量*/
	char *which;
	char fail[10] = "-1";
	char id[MAX_USER];
	/* 若已经创建过info.txt，则从info.txt读取学生、课程数量和学号 */
	FILE *fp;
	errno_t err;
	char filename[20] = "info.txt";
	if ((err = fopen_s(&fp, filename, "r")) == 0) {
		/*读取数量*/
		fscanf_s(fp, "%d %d", &num.stu, &num.course);
		fclose(fp);
	}
	/*教师初次登录进行账户密码初始化*/
	char filename2[20] = "teacher.txt";
	char tch_pwd[N], tch_act[N];
	if ((err = fopen_s(&fp, filename2, "r")) != 0) {
		char nothing[20];
		printf("教师您好，系统监测到您是第一次登录，请初始化您的账户和密码\n");
		system("pause");
		printf("请设置您的账户（之后不可修改）：");
		gets(tch_act);
		printf("\n请设置您的密码（之后可修改）：");
		passwd(tch_pwd);
		printf("\n请输入您的邮箱便于找回密码：");
		gets(nothing);
		fopen_s(&fp, filename2, "w");
		fprintf(fp, "%s %s", tch_act, tch_pwd);
		fclose(fp);
		system("cls");
	}
	fclose(fp);
	fopen_s(&fp, filename2, "r");
	fscanf_s(fp, "%s", tch_act, N);
	fclose(fp);
	
	welcome(&choice);
	while (choice != 3) {
		while (choice != 1 && choice != 2) {
			printf("输入有误，请重新输入:");
			scanf_s("%d", &choice);
			getchar();
		}
		/*通过login()返回值判断用户身份，若验证通过，给出操作界面*/
		if (choice == 1 && strcmp((which = login(choice)), fail)) {
			printf("\n教师%s, 您已成功登录！\n\n", tch_act);
			system("pause");
			system("cls");
			teacher();
		}
		else if (choice == 2 && strcmp((which = login(choice)), fail)) {
			strcpy_s(id, MAX_USER, which);
			printf("\n学生%s, 您已成功登录！\n\n", id);
			system("pause");
			system("cls");
			student(id);
		}
		if (strcmp(which, fail) == 0) break;
		welcome(&choice);

	}
}

Num score() {
	Student stu[N];
	int i, j;
	FILE *fp;
	errno_t err;
	char filename1[10] = "score.txt";
	char filename2[10] = "info.txt"; /* 存放当前已记录学生人数，课程数；学生的账号（学号）和密码（初始值为学号）*/

	printf("请输入学生人数和课程数目：");
	scanf_s("%d%d", &num.stu, &num.course);
	printf("请输入学生的学号和成绩：\n");
	for (i = 0; i < num.stu; i++) {
		scanf_s("%s", stu[i].id, N);
		for (j = 0; j < num.course; j++) {
			scanf_s("%f", &stu[i].score[j]);
		}
	}
	getchar();
	printf("---------------------------------------\n");
	getchar();
	printf("数据确认：\n");
	for (i = 0; i < num.stu; i++) {
		printf("%s ", stu[i].id);
		for (j = 0; j < num.course; j++) {
			printf("%.1f ", stu[i].score[j]);
		}
		printf("\n");
	}
	printf("\n");

	/*生成文件score.txt*/
	if ((err = fopen_s(&fp, filename1, "w")) != 0) {
		printf("无法打开此文件\n");
		exit(0);
	}
	for (i = 0; i < num.stu; i++) {
		fprintf(fp, "%s ", stu[i].id);
		for (j = 0; j < num.course; j++) {
			fprintf(fp, "%.1f ", stu[i].score[j]);
		}
		fprintf(fp, "\n");
	}
	printf("已生成文件\"%s\"\n", filename1);
	fclose(fp);

	/*生成文件info.txt*/
	if ((err = fopen_s(&fp, filename2, "w")) != 0) {
		printf("无法打开此文件\n");
		exit(0);
	}
	fprintf(fp, "%d %d\n", num.stu, num.course);
	for (i = 0; i < num.stu; i++) {
		strcpy_s(stu[i].pwd, N, stu[i].id); /*初始密码为学号*/
		fprintf(fp, "%s %s", stu[i].id, stu[i].pwd);
		fprintf(fp, "\n");
	}
	printf("已生成文件\"%s\"\n", filename2);
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

	/*从score.txt读取数据*/
	if ((err = fopen_s(&in, filename_in, "r")) != 0) {
		printf("无法打开\"%s\"\n", filename_in);
		exit(0);
	}
	/*读取学号,分数*/
	for (i = 0; i < num.stu; i++) {
		fscanf_s(in, "%s", stu[i].id, N);
		for (j = 0; j < num.course; j++) {
			fscanf_s(in, "%f", &stu[i].score[j]);
		}
	}

	/*各科最大最小平均值*/
	for (j = 0; j < num.course; j++, course++) {
		average[j] = stu[0].score[j];
		max[j] = stu[0].score[j];
		min[j] = stu[0].score[j];
		printf("统计数据：\n");
		for (i = 1; i < num.stu; i++) {
			average[j] += stu[i].score[j];
			if (max[j] < stu[i].score[j]) max[j] = stu[i].score[j];
			if (min[j] > stu[i].score[j]) min[j] = stu[i].score[j];
		}
		average[j] /= num.stu;
		printf("课程%c的最高分：%.2f, 最低分：%.2f, 平均分：%.2f\n", course, max[j], min[j], average[j]);
	}
	/*每人总成绩*/
	for (i = 0; i < num.stu; i++) {
		stu[i].sum = stu[i].score[0];
		for (j = 1; j < num.course; j++) {
			stu[i].sum += stu[i].score[j];
		}
		printf("%s 的总成绩为: %.2f\n", stu[i].id, stu[i].sum);
	}

	/*生成文件report.txt*/
	if ((err = fopen_s(&out, filename_out, "w")) != 0) {
		printf("无法打开\"%s\"\n", filename_out);
		exit(0);
	}
	fprintf(out, "课程名称 \t最高分 最低分 平均分\n");
	for (course = 'A', j = 0; j < num.course; j++, course++) {
		fprintf(out, "    %c\t%7.2f%7.2f%7.2f\n", course, max[j], min[j], average[j]);
	}
	fprintf(out, "    学号\t\t总成绩\n");
	for (i = 0; i < num.stu; i++) {
		fprintf(out, "%s\t%8.2f\n", stu[i].id, stu[i].sum);
	}
	fclose(out);
	printf("已生成文件\"%s\"\n", filename_out);
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
	/*从score.txt读取数据*/
	if ((err = fopen_s(&in, filename_in, "r")) != 0) {
		printf("无法打开\"%s\"\n", filename_in);
		exit(0);
	}
	/*读取学号,分数*/
	for (i = 0; i < num.stu; i++) {
		fscanf_s(in, "%s", stu[i].id, N);
		for (j = 0; j < num.course; j++) {
			fscanf_s(in, "%f", &stu[i].score[j]);
		}
	}
	fclose(in);

	/*生成文件sort.txt*/
	if ((err = fopen_s(&out, filename_out, "w")) != 0) {
		printf("无法打开\"%s\"\n", filename_out);
		exit(0);
	}
	/*将读到的数据放入另外两个结构course_rank, final_rank中*/
	for (i = 0; i < num.stu; i++) {
		course_rank[i] = stu[i];
		final_rank[i] = stu[i];
	}

	/*将结果输出到屏幕和文件中*/
	for (j = 0; j < num.course; j++, course++) {
		sort_by_course(course_rank, num, j);
		printf("按课程%c排名：\n", course);
		fprintf(out, "按课程%c排名：\n", course);
		for (i = 0; i < num.stu; i++) {
			printf("%s %.2f\n", course_rank[i].id, course_rank[i].score[j]);
			fprintf(out, "%s %.2f\n", course_rank[i].id, course_rank[i].score[j]);
		}
	}

	sort_by_final(final_rank, num);
	printf("按总成绩排名：\n");
	fprintf(out, "按总成绩排名：\n");
	for (i = 0; i < num.stu; i++) {
		printf("%s %.2f\n", final_rank[i].id, final_rank[i].sum);
		fprintf(out, "%s %.2f\n", final_rank[i].id, final_rank[i].sum);
	}
	printf("已生成文件\"%s\"\n", filename_out);
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

	printf("输入您要查找的学号：");
	scanf_s("%s", id, N);
	/*从score.txt读取数据*/
	if ((err = fopen_s(&in, filename_in, "r")) != 0) {
		printf("无法打开\"%s\"\n", filename_in);
		exit(0);
	}
	/*读取学号,分数*/
	for (i = 0; i < num.stu; i++) {
		fscanf_s(in, "%s", stu[i].id, N);
		for (j = 0; j < num.course; j++) {
			fscanf_s(in, "%f", &stu[i].score[j]);
		}
	}
	fclose(in);

	/*生成文件search.txt*/
	if ((err = fopen_s(&out, filename_out, "w")) != 0) {
		printf("无法打开\"%s\"\n", filename_out);
		exit(0);
	}
	/*算出每个人的总成绩*/
	for (i = 0; i < num.stu; i++) {
		stu[i].sum = 0;
		for (j = 0; j < num.course; j++) {
			stu[i].sum += stu[i].score[j];
		}
	}
	/* 将成绩打印到屏幕+文件中 */
	for (i = 0; i < num.stu; i++) {
		if (strcmp(id, stu[i].id) == 0) {
			printf("学生%s的成绩单：\n", id);
			fprintf(out, "学生%s的成绩单：\n", id);
			for (j = 0; j < num.course; j++, course++) {
				fprintf(out, "课程%c\t", course);
				printf("课程%c\t", course);
			}
			fprintf(out, "总成绩\n");
			printf("总成绩\n");
			for (j = 0; j < num.course; j++) {
				printf("%.1f\t", stu[i].score[j]);
				fprintf(out, "%.1f\t", stu[i].score[j]);
			}
			printf("%.1f\n", stu[i].sum);
			fprintf(out, "%.1f\n", stu[i].sum);
			break;
		}
	}
	if (i == num.stu) {
		printf("没有找到该学生！\n");
	}
	printf("已生成文件\"%s\"\n", filename_out);
	fclose(out);
}

void sort_by_course(Student *course_rank, Num num, int cour) {
	int i, j, k;
	Student temp;
	/*选择法排序*/
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
	int i, j, k;
	Student temp;
	/*算出每个人的总成绩*/
	for (i = 0; i < num.stu; i++) {
		final_rank[i].sum = 0;
		for (j = 0; j < num.course; j++) {
			final_rank[i].sum += final_rank[i].score[j];
		}
	}
	/*选择法排序*/
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
	int choice;
	while (1) { 
		printf("\t\t--------------------欢迎使用学生成绩管理系统！---------------------\n");
		printf("\t\t| 成绩初始化录入                                   \t- 请输入1 |\n");
		printf("\t\t| 计算各科成绩的最高分最低分平均分及每人的总成绩 \t- 请输入2 |\n");
		printf("\t\t| 按照单科成绩和个人总成绩进行降序排序                  - 请输入3 |\n");
		printf("\t\t| 按学号查询学生的各科成绩                         \t- 请输入4 |\n");
		printf("\t\t| 教师密码修改功能                               \t- 请输入5 |\n");
		printf("\t\t|                                                \t          |\n");
		printf("\t\t|                                                \t          |\n");
		printf("\t\t| 退出                                            \t- 请输入6 |\n");
		printf("\t\t-------------------------------------------------------------------\n");
		printf("\n\n");
		printf("你的选择是：  ");
		scanf_s("%d", &choice);
		
		switch (choice)
		{
		case 1: printf("-----------------正在录入---------------\n");
			num = score(score);
			printf("-----------------录入完成---------------\n");
			break;
		case 2: printf("-----------------成绩计算--------------\n");
			report(num);
			printf("-----------------计算完成--------------\n");
			break;
		case 3: printf("-----------------成绩排序--------------\n");
			sort(num);
			printf("-----------------排序完成--------------\n");
			break;
		case 4: printf("-----------------成绩查询--------------\n");
			search(num);
			printf("-----------------查询完成--------------\n");
			break;
		case 5:printf("-----------------修改密码--------------\n");
			modtch();
			printf("-----------------修改完成--------------\n");
			break;
		case 6: printf("-----------------退出系统--------------\n");
			return;
		}
		system("pause");
		system("cls");
	}
}

void student(char *id){
	int choice;
	while (1) {
		printf("\t--------------------欢迎使用学生成绩管理系统！----------------------\n");
		printf("\t| 成绩查询                                            \t- 请输入1 |\n");
		printf("\t| 修改密码                                            \t- 请输入2 |\n");
		printf("\t| 退出                                            \t- 请输入3 |\n");
		printf("\t-----------------------------------------------------------------\n");
		printf("你的选择是：  ");
		scanf_s("%d", &choice);
		

		switch (choice)
		{
		case 1: printf("-----------------成绩查询--------------\n");
			student_search(id);
			printf("-----------------查询完成--------------\n");
			break;
		case 2: printf("-----------------修改密码--------------\n");
			modify(id);
			printf("-----------------修改成功--------------\n");
			break;
		case 3: printf("-----------------退出系统--------------\n");
			return;
		default: printf("输入错误，重新输入！\n");
		}
		system("pause");
		system("cls");
		//printf("\n\n");
	}
}

char* login(int choice) {
	char user[MAX_USER], teacher_user[MAX_USER];
	char pwd[MAX_PWD], teacher_pwd[MAX_PWD];
	char *which = "0"; /*登录成功返回值：学生学号*/
	char *fail = "-1";/*登录失败返回值*/
	int count = 0;
	FILE *fp;
	char filename[20] = "teacher.txt";
	int i=0;
	Student stu[N];

	if (choice == 1) {
		fopen_s(&fp, filename, "r");
		fscanf_s(fp, "%s %s", teacher_user, MAX_USER, teacher_pwd, MAX_PWD);
		fclose(fp);
		do
		{
			if (count == 3) {
				printf("您已三次输错密码，系统将关闭！\n");
				system("pause");
				return fail;
			}
			else if (count > 0)
				printf("账号或密码错误！您还有%d次机会！\n", (3 - count));

			printf("\n用户名：");
			gets(user);
			printf("\n密码：");
		
			passwd(pwd);
			count++;

		} while ((strcmp(user, teacher_user)) || (strcmp(pwd, teacher_pwd))); /*循环条件：密码或账号不匹配*/
	}
	
	if (choice == 2) {
		int i;
		FILE *in;
		errno_t err;
		char filename_in[20] = "info.txt";
		int success = 0; /*成功登录的标记*/

		/*从info.txt读取数据*/
		if ((err = fopen_s(&in, filename_in, "r")) != 0) {
			printf("无法打开\"%s\"\n", filename_in);
			exit(0);
		}
		/*读取学生的学号,密码*/
		int temp1=0, temp2=0;
		fscanf_s(in, "%d %d", &temp1, &temp2);
		for (i = 0; i < num.stu; i++) {
			fscanf_s(in, "%s %s", stu[i].id, N, stu[i].pwd, N);
		}
		fclose(in);
		
		/*请用户输入账号密码*/
		do
		{
			if (count == 3) {
				printf("您已三次输错密码，系统将关闭！\n");
				system("pause");
				return fail;
			}
			else if (count > 0)
				printf("\n密码错误！您还有%d次机会!", (3 - count));

			printf("\n用户名：");
			gets(user);
			printf("\n密码：");
			passwd(pwd);
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
	int success = 0; /*成功登录的标记*/
	Student stu[N];
	char confirm_pwd[MAX_PWD];
	char new_pwd[MAX_PWD];

	 /*从info.txt读取数据*/
	if ((err = fopen_s(&fp, filename, "r")) != 0) {
		printf("无法打开\"%s\"\n", filename);
		exit(0);
	}
	/*读取学生的学号,密码*/
	int temp1 = 0, temp2 = 0;
	fscanf_s(fp, "%d %d", &temp1, &temp2);
	for (i = 0; i < num.stu; i++) {
		fscanf_s(fp, "%s %s", stu[i].id, N, stu[i].pwd, N);
	}
	fclose(fp);

	for (i = 0; i < num.stu; i++) {
		if (strcmp(id, stu[i].id) == 0) {
			printf("请输入新密码：");
			passwd(new_pwd);
			printf("请确认新密码：");
			passwd(confirm_pwd);
			if (strcmp(new_pwd, confirm_pwd) == 0) {
				strcpy_s(stu[i].pwd, N, new_pwd);
				printf("修改成功！\n");
			}
		}
	}
	/* 修改info.txt 文件 */
	if ((err = fopen_s(&fp, filename, "w")) != 0) {
		printf("无法打开\"%s\"\n", filename);
		exit(0);
	}
	fprintf(fp, "%d %d", num.stu, num.course);
	fprintf(fp, "\n");
	for (i = 0; i < num.stu; i++) {
		fprintf(fp, "%s %s\n", stu[i].id, stu[i].pwd);
	}
	fclose(fp);


}

void modtch() {
	FILE *fp;
	FILE *fp1;
	errno_t err;
	errno_t err1;
	//char filename[20] = "inftch.txt";
	int success = 0; /*成功登录的标记*/
	char tch_act[N], tch_pwd[N];
	char confirm_pwd[MAX_PWD];
	char new_pwd[MAX_PWD];
	char filename[20] = "teacher.txt";

	/*从teacher.txt读取数据*/
	if ((err = fopen_s(&fp, filename, "r")) != 0) {
		printf("无法打开\"%s\"\n", filename);
		system("pause");
		exit(0);
	}
	
	/*读取老师的账户、密码*/
 	fscanf_s(fp, "%s %s", tch_act, N, tch_pwd, N);
	for (;; printf("请重新输入\n"))
	{
		printf("请输入新密码：");
		passwd(new_pwd);
		printf("请确认新密码：");
		passwd(confirm_pwd);
		if (strcmp(new_pwd, confirm_pwd) == 0) {
			strcpy_s(tch_pwd,N,new_pwd);
			printf("修改成功！\n");
			break;
		}
	}
	fclose(fp);
	
	/* 修改teacher.txt 文件 */
	if ((err1 = fopen_s(&fp1, filename, "w")) != 0) {
		printf("无法打开(w)\"%s\"\n", filename);
		system("pause");
		exit(0);
		
	}
	fprintf(fp1, "%s %s", tch_act, tch_pwd);
	fclose(fp1);
}

void student_search(char *id) {
	int i, j;
	FILE *in;
	errno_t err;
	char filename_in[20] = "score.txt";
	int success = 0; /*成功登录的标记*/
	Student stu[N];
	char course = 'A';

	/*从score.txt读取数据*/
	if ((err = fopen_s(&in, filename_in, "r")) != 0) {
		printf("无法打开\"%s\"\n", filename_in);
		exit(0);
	}
	/*读取学号,分数*/
	for (i = 0; i < num.stu; i++) {
		fscanf_s(in, "%s", stu[i].id, N);
		for (j = 0; j < num.course; j++) {
			fscanf_s(in, "%f", &stu[i].score[j]);
		}
	}
	fclose(in);
	/*算出每个人的总成绩*/
	for (i = 0; i < num.stu; i++) {
		stu[i].sum = 0;
		for (j = 0; j < num.course; j++) {
			stu[i].sum += stu[i].score[j];
		}
	}
	/* 将成绩打印到屏幕上 */
	for (i = 0; i < num.stu; i++) {
		if (strcmp(id, stu[i].id) == 0) {
			
			printf("学生%s的成绩单：\n", id);
			for (j = 0; j < num.course; j++, course++) {
				printf("课程%c\t", course);
			}
			printf("总成绩\n");
			for (j = 0; j < num.course; j++) {
				printf(" %.1f\t", stu[i].score[j]);
			}
			printf(" %.1f\n", stu[i].sum);
			break;
		}
	}
}

void passwd(char *pwd) {
	int i = 0;
	char ch; /* 读取密码 */
	while ((ch = _getch()) != '\r')
	{
		if (i<MAX_PWD && isprint(ch))
		{
			pwd[i++] = ch;
			putchar('*');
		}
		else if (i>0 && ch == '\b')
		{
			--i;
			putchar('\b');
			putchar(' ');
			putchar('\b');
		}
	}
	putchar('\n');
	pwd[i] = '\0';
}

void welcome(int *ptchoice) {
	system("cls");
	printf("\t\t-----------------欢迎使用学生成绩管理系统！----------------------\n");
	printf("\t\t| 教师登录                                            \t- 请输入1 |\n");
	printf("\t\t| 学生登录                                            \t- 请输入2 |\n");
	printf("\t\t| 退出                                            \t- 请输入3 |\n");
	printf("\n\n输入您的选择：");
	scanf_s("%d", ptchoice);
	getchar();
}

