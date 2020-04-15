#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE* fp;
FILE* fp1;
typedef struct A tree;
struct A
{
	int e;
	tree* L;
	tree* R;
	int h;
};

// a,b중 큰 값을 return
int Max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

//tree의 height를 return 만약 tree가 null이면, -1을 return
int Height(tree* t)
{
	if (t == NULL)
		return -1;
	else
		return t->h;
}

//SingleLeft를 실행
tree* SL(tree* t)
{
	tree* t1 = t->L;
	t->L = t1->R;
	t1->R = t;
	t->h = Max(Height(t->L), Height(t->R)) + 1;
	t1->h = Max(t->h, Height(t1->L)) + 1;
	return t1;
}

//SingleRight를 실행
tree* SR(tree* t)
{
	tree* t1 = t->R;
	t->R = t1->L;
	t1->L = t;
	t->h = Max(Height(t->L), Height(t->R)) + 1;
	t1->h = Max(t->h, Height(t1->R)) + 1;
	return t1;
}

//DoubleLeft를 실행
tree* DL(tree* t)
{
	t->L = SR(t->L);
	return SL(t);
}

//DoubleRight를 실행
tree* DR(tree* t)
{
	t->R = SL(t->R);
	return SR(t);
}

//tree에서 n을 찾으면 그 tree를 return, 찾지 못하면 null을 리턴
tree* Find(int n, tree* t)
{
	if (t == NULL)
		return t;
	else if (n < t->e)
		return Find(n, t->L);
	else if (n > t->e)
		return Find(n, t->R);
	return t;
}

//tree에서 가장 큰 값을 갖는 tree를 return
tree* FindMax(tree* t)
{
	if (t == NULL)
		return t;
	tree* tmp = t;
	while (tmp->R != NULL)
		tmp = tmp->R;
	return tmp;
}

//tree에서 가장 작은 값을 갖는 tree 리턴
tree* FindMin(tree* t)
{
	if (t == NULL)
		return t;
	tree* tmp = t;
	while (tmp->L != NULL)
		tmp = tmp->L;
	return tmp;
}

//tree에서 insert를 실행해주며 AVL tree로 만들어준다
tree* insert(int n, tree* t)
{
	if (t == NULL)
	{
		t = (tree*)malloc(sizeof(tree));
		t->e = n;
		t->h = 0;
		t->L = NULL;
		t->R = NULL;
	}
	else if (n < t->e)
	{
		t->L = insert(n, t->L);
		if (Height(t->L) - Height(t->R) == 2)
		{
			if (n < t->L->e)
				t = SL(t);
			else
				t = DL(t);
		}
	}
	else if (n > t->e)
	{
		t->R = insert(n, t->R);
		if (Height(t->R) - Height(t->L) == 2)
		{
			if (n > t->R->e)
				t = SR(t);
			else
				t = DR(t);
		}
	}
	t->h = Max(Height(t->L), Height(t->R)) + 1;
	return t;
}

//tree 안에서 n을 원소로 갖는 tree를 제거
tree* Delete(int n, tree* t)
{
	if (n > t->e)
		t = Delete(n, t->R);
	else if (n < t->e)
		t = Delete(n, t->L);
	else if (t->L && t->R)
	{
		tree* tmp = FindMax(t->L);
		t->e = tmp->e;
		t->L = Delete(tmp->e, t->L);
	}
	else
	{
		tree* tmp = t;
		if (t->L == NULL)
			t = t->R;
		else if (t->R == NULL)
			t = t->L;
		free(tmp);
	}
	return t;
}

//inorder 순으로 tree의 요소값과 높이를 출력
void printInorder(tree* t)
{
	if (t)
	{
		printInorder(t->L);
		fprintf(fp1, "%d(%d) ", t->e, t->h);
		printInorder(t->R);
	}
}

int main()
{
	fp = fopen("input.txt", "r");
	fp1 = fopen("output.txt", "w");
	tree* t = NULL;
	while (1)
	{
		int n;
		if (fscanf(fp, "%d", &n) == EOF)
			break;
		//n을 tree 안에서 찾아서 있으면 오류 메세지를 출력, 없으면 insert를 해준다
		if (Find(n, t) != NULL)
			fprintf(fp1, "%d already in the tree!\n", n);
		else
		{
			t = insert(n, t);
			printInorder(t);
			fprintf(fp1, "\n");
		}
	}
	//t 안의 모든 트리들을 메모리 해제 시켜준다.
	while (t != NULL)
		t = Delete(t->e, t);
}
