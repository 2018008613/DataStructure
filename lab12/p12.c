#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* fp;
FILE* fp1;

typedef struct A hash;
struct A {
	int ts;
	int* list;
};

//각각의 solution의 경우에 따라 hash 값을 return 해준다
int Hash(int v, int s, int i, int solution)
{
	if (solution == 1)
		return (v + i) % s;
	else if (solution == 2)
		return (v + i * i) % s;
	return (v + i * (7 - v % 7)) % s;
}

//만약 hash안에 v가 있으면 그 위치의 index를, 없으면 -1을 return해준다.
int find(hash* H, int v, int solution)
{
	int i;
	for (i = 0;i < H->ts;i++)
	{
		//그 위치의 값이 0이면 더이상 탐색을 하지 않고 종료해도 된다.
		if (H->list[Hash(v, H->ts, i, solution)] == 0)
			break;
		if (H->list[Hash(v, H->ts, i, solution)] == v)
			return Hash(v, H->ts, i, solution);
	}
	return -1;
}

//v가 이미 있으면 Already exists메세지를 출력, 없다면 Hash해 나가며 들어가야 할 위치에 v를 넣은 뒤 Inserted v 메세지를 출력한다
void Insert(hash* H, int v, int solution)
{
	int f = find(H, v, solution);
	if (f != -1)
		fprintf(fp1, "Already exists\n");
	else
	{
		for (int i = 0;i < H->ts;i++)
			if (H->list[Hash(v, H->ts, i, solution)] <= 0)
			{
				H->list[Hash(v, H->ts, i, solution)] = v;
				fprintf(fp1, "Inserted %d\n", v);
				break;
			}
	}
}

//v가 없으면 v not exists 메세지를 출력하고, 있다면 hash안에서 v가 원래 있던 위치에 -1을 넣어주고 Deleted v 메세지를 출력한다
void Delete(hash* H, int v, int solution)
{
	int f = find(H, v, solution);
	if (f == -1)
		fprintf(fp1, "%d not exists\n", v);
	else
	{
		H->list[f] = -1;
		fprintf(fp1, "Deleted %d\n", v);
	}
}

//hash의 모든 값을 순서대로 출력해주는데, -1이 들어가 있는 경우에만 0을 출력해준다
void print(hash* H)
{
	for (int i = 0;i < H->ts;i++)
	{
		if (H->list[i] == -1)
			fprintf(fp1, "0 ");
		else
			fprintf(fp1, "%d ", H->list[i]);
	}
	fprintf(fp1, "\n");
}

int main()
{
	fp = fopen("input.txt", "r");
	fp1 = fopen("output.txt", "w");
	int t;
	fscanf(fp, "%d", &t);
	//t번의 test case만큼 실행
	while (t--)
	{
		char ch[10];
		fscanf(fp, "%s", ch);
		//각각의 case가 Linear, Quadratic, Double일 때에 맞게 solution 값을 넣어준다
		int solution;
		if (strcmp(ch, "Linear") == 0)
			solution = 1;
		else if (strcmp(ch, "Quadratic") == 0)
			solution = 2;
		else if (strcmp(ch, "Double") == 0)
			solution = 3;
		// Linear, Quadratic, Double에 맞게 출력
		fprintf(fp1, "%s\n", ch);
		//hash의 size를 받고 Hash 생성
		int size;
		fscanf(fp, "%d", &size);
		hash* H = (hash*)malloc(sizeof(hash));
		H->ts = size;
		H->list = (int*)malloc(sizeof(int)*size);
		//hash의 list의 값들을 0으로 초기화
		for (int i = 0;i < size;i++)
			H->list[i] = 0;
		while (1)
		{
			char cha[3];
			fscanf(fp, "%s", cha);
			//insert
			if (cha[0] == 'i')
			{
				int v;
				fscanf(fp, "%d", &v);
				Insert(H, v, solution);
			}
			//delete
			else if (cha[0] == 'd')
			{
				int v;
				fscanf(fp, "%d", &v);
				Delete(H, v, solution);
			}
			//find할 때 그 값이 발견되지 않을 경우에만 Not found 출력
			else if (cha[0] == 'f')
			{
				int v;
				fscanf(fp, "%d", &v);
				int f = find(H, v, solution);
				if (f == -1)
					fprintf(fp1, "Not found\n");
			}
			//hash의 모든 원소들 출력
			else if (cha[0] == 'p')
				print(H);
			//이번 test 종료
			else if (cha[0] == 'q')
			{
				fprintf(fp1, "\n");
				break;
			}
		}
		//메모리 해제
		free(H->list);
		free(H);
	}
}
