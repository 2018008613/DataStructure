#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* fp;
FILE* fp1;

typedef struct A tree;
struct A {
	int lthread;
	tree* lchild;
	char data;
	tree* rchild;
	int rthread;
};

//Tree를 생성해주는 함수
tree* createTree()
{
	tree* t = (tree*)malloc(sizeof(tree));
	t->lthread = 1;
	t->lchild = NULL;
	t->rchild = NULL;
	t->rthread = 1;
	return t;
}

//inorder traversal에서 t의 다음 tree 를 리턴해주는 함수
tree* insucc(tree* t)
{
	tree* temp = t->rchild;
	if (!t->rthread)
		while (!temp->lthread)
			temp = temp->lchild;
	return temp;
}

//inorder traversal 과정대로 데이터를 file에 출력해주는 함수
void tinorder(tree* t)
{
	tree* temp = t;
	while (1)
	{
		temp = insucc(temp);
		if (temp == t)
			break;
		fprintf(fp1, "%c ", temp->data);
	}
}

int main()
{
	fp = fopen("input.txt", "r");
	fp1 = fopen("output.txt", "w");
	//root 생성
	tree* t = createTree();
	t->rthread = 0;
	t->rchild = t;
	//n 받음
	int n;
	fscanf(fp, "%d", &n);
	//A부터 I까지의 값을 가지고 있는 9개의 tree를 갖는 배열 생성
	tree** tr = (tree**)malloc(sizeof(tree*) * (n + 1));
	char ch[101];
	for (int i = 1;i <= n;i++)
	{
		tr[i] = createTree();
		fscanf(fp, "%s", ch);
		tr[i]->data = ch[0];
	}
	//root의 왼쪽 child에 A를 연결
	t->lchild = tr[1];
	t->lthread = 0;
	//thread child가 아닌 것들을 연결
	for (int i = 1;i <= n / 2;i++)
	{
		tr[i]->lchild = tr[i * 2];
		tr[i]->lthread = 0;
		if (i * 2 + 1 <= n)
		{
			tr[i]->rchild = tr[i * 2 + 1];
			tr[i]->rthread = 0;
		}
	}
	//thread child 연결
	tr[5]->lchild = tr[2];
	tr[5]->rchild = tr[1];
	tr[6]->lchild = tr[1];
	tr[6]->rchild = tr[3];
	tr[7]->lchild = tr[3];
	tr[7]->rchild = t;
	tr[8]->lchild = t;
	tr[8]->rchild = tr[4];
	tr[9]->lchild = tr[4];
	tr[9]->rchild = tr[2];
	tinorder(t);
	for (int i = 1;i <= n;i++)
		free(tr[i]);
	free(tr);
	free(t);
}
