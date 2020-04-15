#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct A
{
	int Capacity;
	int TopOfStack;
	int* Array;
}Stack;

//새로운 비어있는 스택 하나를 생성하는 함수
Stack* CreateStack()
{
	Stack* st = (Stack*)malloc(sizeof(Stack));
	st->Capacity = 100;
	st->TopOfStack = -1;
	st->Array = (int*)malloc(sizeof(int) * 100);
	return st;
}

//비어있으면 파일 f에 Empty를 출력, 아니면 pop을 해주고 top에 있던 숫자를 파일 f에 출력해주는 함수
void Pop(Stack* st,FILE* f)
{
	if ((st->TopOfStack) == -1)
		fprintf(f, "Empty\n");
	else
		fprintf(f, "%d\n", st->Array[(st->TopOfStack)--]);
}

//꽉차있으면 파일 f에 Full을 출력, 아니면 n을 push해주는 함수
void Push(Stack* st, int n, FILE* f)
{
	if (st->TopOfStack == 99)
		fprintf(f, "Full\n");
	else
		st->Array[++(st->TopOfStack)] = n;
}

int main()
{
	int k;
	Stack* st = CreateStack();
	FILE* fp = fopen("input.txt", "r");
	FILE* fp1 = fopen("output.txt", "w");
	fscanf(fp, "%d", &k);
	while (k--)
	{
		char ch[10];
		fscanf(fp, "%s", ch);
		if (strcmp(ch, "push") == 0)
		{
			int n;
			fscanf(fp, "%d", &n);
			Push(st, n, fp1);
		}
		if (strcmp(ch, "pop") == 0)
			Pop(st, fp1);
	}
	fclose(fp);
	fclose(fp1);
	free(st->Array);
	free(st);
}
