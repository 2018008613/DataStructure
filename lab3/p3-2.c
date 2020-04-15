#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct A {
	int Capacity;
	int Front;
	int Rear;
	int Size;
	int* Array;
}Queue;

// 비어있는 새로운 queue 하나를 생성해서 리턴해주는 함수
Queue* CreateQueue()
{
	Queue* q;
	q = (Queue*)malloc(sizeof(Queue));
	q->Capacity = 100;
	q->Front = 1;
	q->Rear = 0;
	q->Size = 0;
	q->Array = (int*)malloc(sizeof(int) * 100);
	return q;
}

// queue가 꽉차있으면 Full을 f파일에 출력, 그렇지 않으면 queue에 n을 push해주는 함수
void enQ(Queue* q,int n,FILE* f)
{
	if (q->Size == 100)
		fprintf(f, "Full\n");
	else
	{
		q->Rear = (q->Rear + 1) % 100;
		q->Array[q->Rear] = n;
		(q->Size)++;
	}
}

// queue가 비어있으면 Empty를 f파일에 출력, 그렇지 않으면 queue에 pop을 해주는 함수
void deQ(Queue* q, FILE* f)
{
	if (q->Size == 0)
		fprintf(f, "Empty\n");
	else
	{
		fprintf(f, "%d\n", q->Array[q->Front]);
		q->Front = (q->Front + 1) % 100;
		(q->Size)--;
	}
}

int main()
{
	int k;
	FILE* fp = fopen("input.txt", "r");
	FILE* fp1 = fopen("output.txt", "w");
	Queue* q = CreateQueue();
	fscanf(fp, "%d", &k);
	while (k--)
	{
		char ch[10];
		fscanf(fp, "%s", ch);
		if (strcmp(ch, "enQ") == 0)
		{
			int n;
			fscanf(fp, "%d", &n);
			enQ(q, n, fp1);
		}
		if (strcmp(ch, "deQ") == 0)
			deQ(q, fp1);
	}
	free(q->Array);
	free(q);
}
