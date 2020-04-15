#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE* fp;
FILE* fp1;

typedef struct _Graph {
	int size;
	int* node;
	int** matrix;
}g;

typedef struct _Queue {
	int* key;
	int front;
	int rear;
	int size;
	int max_size;
}q;

//n개의 node를 가지는 배열과 배열의 크기를 인자로 받아 그래프를 만든다
g* CreateGraph(int* nodes, int n)
{
	g* G = (g*)malloc(sizeof(g));
	G->size = n;
	G->node = (int*)malloc(sizeof(int)*(n + 1));
	for (int i = 1;i <= n;i++)
		G->node[i] = nodes[i - 1];
	G->matrix = (int**)malloc(sizeof(int*)*(n + 1));
	for (int i = 0;i <= n;i++)
		G->matrix[i] = (int*)malloc(sizeof(int)*(n + 1));
	for (int i = 0;i <= n;i++)
		for (int j = 0;j <= n;j++)
			G->matrix[i][j] = 0;
	return G;
}

//a에서 b로 가는 edge를 그래프의 matrix에 표시해준다.
void InsertEdge(g* G, int a, int b)
{
	int x, y, n;
	n = G->size;
	for (int i = 1;i <= n;i++)
	{
		if (G->node[i] == a)
			x = i;
		if (G->node[i] == b)
			y = i;
	}
	G->matrix[x][y] = 1;
}

//최대 크기가 X인 QUEUE를 생성해준다
q* MakeNewQueue(int X)
{
	q* Q = (q*)malloc(sizeof(q));
	Q->max_size = X;
	Q->size = 0;
	Q->front = 1;
	Q->rear = 0;
	Q->key = (int*)malloc(sizeof(int)*X);
	return Q;
}

//Q가 꽉 차있지 않으면, X를 PUSH해준다
void Enqueue(q* Q, int X)
{
	if (Q->size != Q->max_size)
	{
		Q->size++;
		Q->rear = (Q->rear + 1) % Q->max_size;
		Q->key[Q->rear] = X;
	}
}

//Q가 비어있지 않으면 front의 값을 return해준다.
int Dequeue(q* Q)
{
	if (Q->size != 0)
	{
		int x = Q->key[Q->front];
		Q->size--;
		Q->front = (Q->front + 1) % Q->max_size;
		return x;
	}
	return 0;
}

//크기가 n인 list배열을 오름차순으로 정렬해준다
void bubble_sort(int* list, int n) {
	int i, j, temp;

	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (list[j] > list[j + 1]) {
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}

//그래프를 Topological sort 순서대로 출력해준다
void Topsort(g* G)
{
	int n = G->size;
	//maxrix와 같은 2차원배열 m을 생성
	int** m = (int**)malloc(sizeof(int*)*(n + 1));
	for (int i = 0;i <= n;i++)
		m[i] = (int*)malloc(sizeof(int)*(n + 1));
	for (int i = 0;i <= n;i++)
		for (int j = 0;j <= n;j++)
			m[i][j] = G->matrix[i][j];
	//QUEUE 생성
	q* Q = MakeNewQueue(1000);
	int cnt = n;
	//방문한 NODE인지를 체크해주는 vis 생성
	int* vis = (int*)malloc(sizeof(int)*(n + 1));
	for (int i = 0;i <= n;i++)
		vis[i] = 0;
	//모든 node가 출력될때까지 반복
	while (cnt != 0)
	{
		for (int i = 1;i <= n;i++)
		{
			//indegree가 없는 node를 queue에 push해준다
			int sum = 0;
			for (int j = 1;j <= n;j++)
				sum += m[j][i];
			if (sum == 0 && vis[i] == 0)
			{
				vis[i] = 1;
				Enqueue(Q, G->node[i]);
				cnt--;
			}
		}
		//q의 크기가 0이 아니면 작업 수행
		int t = Q->size;
		if (t > 0)
		{
			//num 배열에 queue에 담겨 있는 원소들을 모두 받은 뒤 bubble sort를 이용해 오름차순으로 정렬한다
			int* num = (int*)malloc(sizeof(int)*t);
			for (int i = 0;i < t;i++)
				num[i] = Dequeue(Q);
			bubble_sort(num, t);
			//작은 순서대로 출력한 후 그 노드가 출발점인 edge를 모두 없애준다
			for (int i = 0;i < t;i++)
			{
				fprintf(fp1, "%d ", num[i]);
				int x;
				for (int j = 1;j <= n;j++)
					if (G->node[j] == num[i])
						x = j;
				for (int j = 1;j <= n;j++)
					m[x][j] = 0;
			}
		}
	}
}

//matrix를 출력해주는 함수
void PrintMatrix(g* G)
{
	fprintf(fp1, "  ");
	int n = G->size;
	for (int i = 1;i <= n;i++)
		fprintf(fp1, "%d ", G->node[i]);
	fprintf(fp1, "\n");
	for (int i = 1;i <= n;i++)
	{
		fprintf(fp1, "%d ", G->node[i]);
		for (int j = 1;j <= n;j++)
			fprintf(fp1, "%d ", G->matrix[i][j]);
		fprintf(fp1, "\n");
	}
}

int main()
{
	fp = fopen("input.txt", "r");
	fp1 = fopen("output.txt", "w");
	//첫 줄을 입력 받은 뒤 숫자단위로 쪼개서 arr배열에 담고, 그 노드의 개수를 cnt에 저장한다
	int cnt = 0;
	char ch[1000];
	fgets(ch, 1000, fp);
	char* token = strtok(ch, " ");
	int arr[500];
	while (token != NULL)
	{
		arr[cnt++] = atoi(token);
		token = strtok(NULL, " ");
	}
	//그래프 생성
	g* G = CreateGraph(arr, cnt);
	//edge를 입력받은 뒤 InsertEdge를 이용해서 그래프에서 이어준다
	while (1)
	{
		int a, b;
		char c;
		if (fscanf(fp, "%d", &a) == EOF)
			break;
		fscanf(fp, "%c%d", &c, &b);
		InsertEdge(G, a, b);
	}
	//그래프의 matrix를 출력해준다
	PrintMatrix(G);
	//Topological Sort의 결과를 출력해준다
	fprintf(fp1, "\n\nTopSort Result : ");
	Topsort(G);
}
