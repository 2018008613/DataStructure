#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

FILE* fp;
FILE* fp1;
int* S;
char** maze;

//S의 값을 모두 0으로 초기화해준다.
void init(int* S)
{
	for (int i = 1;i < (sizeof(S) / sizeof(int));i++)
		S[i] = 0;
}

//x의 root를 find해주는 함수
int find2(int x, int* S)
{
	if (S[x] <= 0)
		return x;
	return S[x] = find2(S[x], S);
}

//a와 b두 트리를 합쳐주는 함수
void Union(int* S, int a, int b)
{
	a = find2(a, S);
	b = find2(b, S);
	if (S[a] > S[b])
		S[a] = b;
	else
	{
		if (S[a] == S[b])
			S[a]--;
		S[b] = a;
	}
}

//maze를 print해주는 함수
void PrintMaze(char** m, int n)
{
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n;j++)
			fprintf(fp1, "%c", m[i][j]);
		fprintf(fp1, "\n");
	}
}

int main()
{
	fp = fopen("input.txt", "r");
	fp1 = fopen("output.txt", "w");
	srand((unsigned int)time(NULL));
	int n, cnt;
	//n을 입력 받는다
	fscanf(fp, "%d", &n);
	cnt = n * n;
	//S를 동적할당해준다.
	S = (int*)malloc(sizeof(int)*(n*n + 1));
	//maze를 동적할당해준다.
	maze = (char**)malloc(sizeof(char*)*(2 * n + 1));
	for (int i = 0;i < 2 * n + 1;i++)
		maze[i] = (char*)malloc(sizeof(char)*(2 * n + 1));
	//미로의 모든 벽을 이어준다
	for (int i = 0;i < 2 * n + 1;i++)
	{
		for (int j = 0;j < 2 * n + 1;j++)
		{
			if (i % 2 == 0 && j % 2 == 0)
				maze[i][j] = '+';
			else if (i % 2 == 0)
				maze[i][j] = '-';
			else if (j % 2 == 0)
				maze[i][j] = '|';
			else
				maze[i][j] = ' ';
		}
	}
	//입구와 출구를 뚫어준다.
	maze[1][0] = ' ';
	maze[2 * n - 1][2 * n] = ' ';
	while (cnt != 1)
	{
		//경계 이외의 값의 좌표를 가지도록 x와 y를 랜덤하게 받아준다.
		int x = rand() % (2 * n - 1) + 1;
		int y = rand() % (2 * n - 1) + 1;
		//그 칸이 -일 때 그 위아래 칸에 담겨있는 숫자의 index를 a와 b에 담아서 그 두 index가 이어져있지 않으면 벽을 없애고 union해준다
		if (maze[x][y] == '-')
		{
			int x1 = x - 1, x2 = x + 1;
			int a = n * (x1 - 1) / 2 + (y + 1) / 2, b = n * (x2 - 1) / 2 + (y + 1) / 2;
			if (find2(a, S) != find2(b, S))
			{
				maze[x][y] = ' ';
				Union(S, a, b);
				cnt--;
			}
		}
		//그 칸이 |일 때 그 양 옆 칸에 담겨있는 숫자의 index를 a와 b에 담아서 그 두 index가 이어져있지 않으면 벽을 없애고 union해준다
		else if (maze[x][y] == '|')
		{
			int y1 = y - 1, y2 = y + 1;
			int a = n * (x - 1) / 2 + (y1 + 1) / 2, b = n * (x - 1) / 2 + (y2 + 1) / 2;
			if (find2(a, S) != find2(b, S))
			{
				maze[x][y] = ' ';
				Union(S, a, b);
				cnt--;
			}
		}
		//union될 때마다 cnt를 1개씩 줄여가므로 cnt가 1이 되면, 즉 모든 트리가 하나로 합쳐지면 while문을 종료한다.
	}
	//미로를 출력해준다
	PrintMaze(maze, 2 * n + 1);
	//동적할당을 해제해준다.
	free(S);
	for (int i = 0;i < 2 * n + 1;i++)
		free(maze[i]);
	free(maze);
}
