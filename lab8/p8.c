#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE* fp;
FILE* fp1;

typedef struct HeapStruct
{
	int capacity;
	int size;
	int* elements;
}heap;

//heap에 x를 insert한다. x가 이미 있으면, 오류 메세지를 출력, 그렇지 않으면 insert한 뒤 메세지를 출력한다.
void Insert(int x, heap* h)
{
	for (int i = 1;i <= h->size;i++)
	{
		if (h->elements[i] == x)
		{
			fprintf(fp1, "%d is already in the heap.\n", x);
			return;
		}
	}
	int t = h->size + 1;
	for (int i = ++(h->size);i != 1 && h->elements[i / 2] < x;i /= 2)
	{
		h->elements[i] = h->elements[i / 2];
		t = i / 2;
	}
	h->elements[t] = x;
	fprintf(fp1, "insert %d\n", x);
}

//heap에서 x를 찾아서 찾으면 찾았다는 메세지를 출력, 그렇지 않으면 오류 메세지를 출력
void find(int x, heap* h)
{
	for (int i = 1;i <= h->size;i++)
	{
		if (h->elements[i] == x)
		{
			fprintf(fp1, "%d is in the heap.\n", x);
			return;
		}
	}
	fprintf(fp1, "%d is not in the heap.\n", x);
}

//heap에 들어있는 모든 요소를 출력해준다.
void print(heap* h)
{
	for (int i = 1;i <= h->size;i++)
		fprintf(fp1, "%d ", h->elements[i]);
	fprintf(fp1, "\n");
}

int main()
{
	fp = fopen("input.txt", "r");
	fp1 = fopen("output.txt", "w");
	//heap의 capacity를 입력받은 뒤 h와 elements를 동적할당해준다.
	heap* h = (heap*)malloc(sizeof(heap));
	fscanf(fp, "%d", &(h->capacity));
	h->size = 0;
	h->elements = (int*)malloc(sizeof(int)*(h->capacity + 1));
	//while문을 돌면서 insert, find, print작업을 수행해준다.
	while (1)
	{
		char c;
		if (fscanf(fp, "%c", &c) == EOF)
			break;
		if (c == 'i')
		{
			int x;
			fscanf(fp, "%d", &x);
			Insert(x, h);
		}
		else if (c == 'f')
		{
			int x;
			fscanf(fp, "%d", &x);
			find(x, h);
		}
		else if (c == 'p')
			print(h);
	}
	//메모리 해제시켜준다.
	free(h->elements);
	free(h);
}
