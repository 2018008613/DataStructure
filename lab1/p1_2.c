#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *name;
	int studentID;
	char *major;
}studentT;


int main(int argc, char* argv[])
{
	int n;
	FILE* fp = fopen(argv[1], "r");
	fscanf(fp, "%d", &n);
	studentT* st = (studentT*)malloc(sizeof(studentT)*n);
	for (int i = 0;i < n;i++)
	{
		st[i].name = (char*)malloc(sizeof(char)*31);
		st[i].major = (char*)malloc(sizeof(char)*31);
		fscanf(fp, "%s", st[i].name);
		fscanf(fp, "%d", &st[i].studentID);
		fscanf(fp, "%s", st[i].major);
	}
	fclose(fp);
	FILE* fp1 = fopen(argv[2], "w");
	for (int i = 0;i < n;i++)
	{
		fprintf(fp1, "%s ", st[i].name);
		fprintf(fp1, "%d ", st[i].studentID);
		fprintf(fp1, "%s\n", st[i].major);
	}
	fclose(fp1);
	for (int i = 0;i < n;i++)
	{
		free(st[i].name);
		free(st[i].major);
	}
	free(st);
}
