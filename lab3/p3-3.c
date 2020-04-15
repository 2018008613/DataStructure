#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct A
{
	int Capacity;
	int TopOfStack;
	char* Array;
}Stack;

typedef struct B
{
	int Capacity;
	int TopOfStack;
	int* Array;
}IntStack;

//비어있지 않으면 top의 값을 반환해주는 함수
char Top(Stack* st)
{
	if (st->TopOfStack != -1)
		return st->Array[st->TopOfStack];
	return ' ';
}

//새로운 비어있는 int형 스택 하나를 생성하는 함수
IntStack* CreateIntStack()
{
	IntStack* st = (IntStack*)malloc(sizeof(IntStack));
	st->Capacity = 100;
	st->TopOfStack = -1;
	st->Array = (int*)malloc(sizeof(int) * 100);
	return st;
}

//top에 있던 숫자를 pop해주고 그 숫자를 리턴해주는 함수
int IntPop(IntStack* st)
{
	if ((st->TopOfStack) != -1)
		return st->Array[(st->TopOfStack)--];
}

//stack에 n을 push해주는 함수
void IntPush(IntStack* st, int n)
{
	if (st->TopOfStack != 99)
		st->Array[++(st->TopOfStack)] = n;
}

//비어있지 않으면 top의 값을 반환해주는 함수
int IntTop(IntStack* st)
{
	if (st->TopOfStack != -1)
		return st->Array[st->TopOfStack];
	return 0;
}

//새로운 비어있는 char 스택 하나를 생성하는 함수
Stack* CreateStack()
{
	Stack* st = (Stack*)malloc(sizeof(Stack));
	st->Capacity = 100;
	st->TopOfStack = -1;
	st->Array = (char*)malloc(sizeof(char) * 100);
	return st;
}

//'('면 출력은하지 않고 pop을 해주고 '('가 아니면 출력하고 pop해주고 IntStack의 맨 위 두 숫자를 pop한뒤 계산값을 push하는 함수
void Pop(IntStack* ist, Stack* st, FILE* f)
{
	if ((st->TopOfStack) != -1)
	{
		if (st->Array[(st->TopOfStack)] != '(')
		{
			char o = Top(st);
			int n1 = IntPop(ist);
			int n2 = IntPop(ist);
			int n3;
			if (o == '+')
				n3 = n2 + n1;
			else if (o == '-')
				n3 = n2 - n1;
			else if (o == '*')
				n3 = n2 * n1;
			else if (o == '/')
				n3 = n2 / n1;
			else if (o == '%')
				n3 = n2 % n1;
			IntPush(ist, n3);
			fprintf(f, "%c", st->Array[(st->TopOfStack)--]);
		}
		else
			(st->TopOfStack)--;
	}
}

//꽉차있지 않으면 n을 push해주는 함수
void Push(Stack* st, char n)
{
	if (st->TopOfStack != 99)
		st->Array[++(st->TopOfStack)] = n;
}

int main()
{
	Stack* st = CreateStack();
	IntStack* ist = CreateIntStack();
	FILE* fp = fopen("input.txt", "r");
	FILE* fp1 = fopen("output.txt", "w");
	char ch[101];
	char ch1[101];
	fscanf(fp, "%s", ch);
	strncpy(ch1, ch, strlen(ch) - 1);
	ch1[strlen(ch) - 1] = NULL;
	fprintf(fp1, "Infix Form : %s\nPostfix Form : ", ch1);
	int len = strlen(ch);
	for (int i = 0;i < len;i++)
	{
		if (ch[i] == '#')
			while (st->TopOfStack != -1)
				Pop(ist, st, fp1);
		if (ch[i] >= 49 && ch[i] <= 57)
		{
			int nu = ch[i] - 48;
			fprintf(fp1, "%d", nu);
			IntPush(ist, nu);
		}
		else
		{
			if (ch[i] == '(')
				Push(st, ch[i]);
			if (ch[i] == ')')
			{
				while (Top(st) != '(')
					Pop(ist, st, fp1);
				if (Top(st) == '(')
					Pop(ist, st, fp1);
			}
			if (ch[i] == '*' || ch[i] == '/' || ch[i] == '%')
			{
				while (st->TopOfStack != -1 && Top(st) != '(' && (Top(st) != '+' && Top(st) != '-'))
					Pop(ist, st, fp1);
				Push(st, ch[i]);
			}
			if (ch[i] == '+' || ch[i] == '-')
			{
				while (st->TopOfStack != -1 && Top(st) != '(')
					Pop(ist, st, fp1);
				Push(st, ch[i]);
			}
		}
	}
	fprintf(fp1, "\nEvaluation Result : %d", IntTop(ist));
	free(st->Array);
	free(st);
	free(ist->Array);
	free(ist);
}
