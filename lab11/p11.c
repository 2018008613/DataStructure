#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE* fp;
FILE* fp1;
int d[101], p[101], w[101][101], arr[301], st, ed;

typedef struct A {
	int key;
	int weight;
}node;

typedef struct B {
	int capacity;
	int size;
	node** element;
}heap;

typedef struct C {
	int size;
	int capacity;
	int* arr;
}stack;

//비어있는 minheap 생성
heap* createMinHeap(int heapSize)
{
	heap* h = (heap*)malloc(sizeof(heap));
	h->capacity = heapSize;
	h->size = 0;
	h->element = (node**)malloc(sizeof(node*)*(heapSize + 1));
	h->element[0] = (node*)malloc(sizeof(node));
	h->element[0]->weight = 0;
	return h;
}

//heap이 꽉 차지 않았을 때, vertex, distance를 입력받은 뒤 heap에 insert해준다
void insert(heap* h, int ve, int di)
{
	if (h->size != h->capacity)
	{
		node* n = (node*)malloc(sizeof(node));
		n->key = ve;
		n->weight = di;
		int i;
		for (i = ++(h->size); h->element[i / 2]->weight > di; i /= 2)
			h->element[i] = h->element[i / 2];
		h->element[i] = n;
	}
}

//heap의 가장 작은 weight를 가진 node를 return해주고 heap을 다시 sorting해준다
node* deleteMin(heap* h)
{
	int i, Child;
	node* m = h->element[1];
	node* l = h->element[(h->size)--];
	for (i = 1; i * 2 <= h->size; i = Child)
	{
		Child = i * 2;
		if (Child != h->size && h->element[Child + 1]->weight < h->element[Child]->weight)
			Child++;
		if (l->weight > h->element[Child]->weight)
			h->element[i] = h->element[Child];
		else
			break;
	}
	h->element[i] = l;
	return m;
}

//stack에 x를 push해준다
void Push(stack* sta, int x)
{
	sta->arr[(sta->size)++] = x;
}

//stack의 맨 위 값을 pop하며 return해준다
int Pop(stack* sta)
{
	return sta->arr[--(sta->size)];
}

//end지점의 원소로부터 이전 경로를 따라가며 stack에 넣어준 뒤 st부터 차례로 pop하며 출력해준다
void printShortestPath(int* pred)
{
	stack* sta = (stack*)malloc(sizeof(stack));
	sta->capacity = 100;
	sta->size = 0;
	sta->arr = (int*)malloc(sizeof(int) * 101);
	Push(sta, arr[ed]);
	int x = ed;
	while (x != st)
	{
		x = p[x];
		Push(sta, arr[x]);
	}
	while (sta->size != 0)
		fprintf(fp1, "%d ", Pop(sta));
	free(sta->arr);
	free(sta);
}


int main()
{
	fp = fopen("input.txt", "r");
	fp1 = fopen("output.txt", "w");
	//arr에 첫 줄의 node들을 넣어준다
	int cnt = 0;
	char ch[1000];
	fgets(ch, 1000, fp);
	char* token = strtok(ch, " ");
	while (token != NULL)
	{
		arr[++cnt] = atoi(token);
		token = strtok(NULL, " ");
	}
	//각 edge의 값과 시작점으로부터 그 점까지의 거리 d를 99999로 초기화해준다.
	for (int i = 1;i <= cnt;i++)
	{
		d[i] = 99999;
		for (int j = 1;j <= cnt;j++)
			w[i][j] = 99999;
	}
	//edge를 입력받아 w에 입력해주고, start 지점의 index와 end 지점의 index를 st, ed에 저장해준다
	while (1)
	{
		int a, b, c1;
		char c;
		fscanf(fp, "%d%c", &a, &c);
		if (c == '-')
		{
			fscanf(fp, "%d%c%d", &b, &c, &c1);
			for (int i = 1;i <= cnt;i++)
			{
				if (a == arr[i])
					st = i;
				if (b == arr[i])
					ed = i;
			}
			w[st][ed] = c1;
		}
		else if (c == ' ')
		{
			fscanf(fp, "%d", &b);
			for (int i = 1;i <= cnt;i++)
			{
				if (a == arr[i])
					st = i;
				if (b == arr[i])
					ed = i;
			}
			break;
		}
	}
	//heap을 생성한다.
	heap* h = createMinHeap(100);
	//start지점을 heap에 넣어준다
	insert(h, arr[st], 0);
	d[st] = 0;
	//dijkstra 를 이용해 최단거리 및 최단경로를 저장해준다.
	while (h->size != 0)
	{
		node* n = deleteMin(h);
		int x;
		for (int i = 1;i <= cnt;i++)
			if (n->key == arr[i])
				x = i;
		for (int i = 1;i <= cnt;i++)
		{
			if (w[x][i] != 99999 && d[i] > n->weight + w[x][i])
			{
				d[i] = n->weight + w[x][i];
				p[i] = x;
				insert(h, arr[i], d[i]);
			}
		}
		free(n);
	}
	//최단경로를 출력해준다
	printShortestPath(p);
	free(h->element);
	free(h);
}
