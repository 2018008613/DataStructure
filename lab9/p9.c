#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define order 3

FILE* fp;
FILE* fp1;

typedef struct A node;

struct A
{
	int nkeys; /*number of keys*/
	node* child[order + 1];
	int key[order];
};

node* root;

//int배열 a를 오름차순으로 정렬해주는 함수
void Sort(int* a, int n)
{
	for (int i = 0;i < n - 1;i++)
	{
		for (int j = i + 1;j < n;j++)
		{
			if (a[i] > a[j])
			{
				int temp = a[j];
				a[j] = a[i];
				a[i] = temp;
			}
		}
	}
}

void insert(int k, node* n)
{
	//root가 NULL일 때 동적할당 해 준 뒤, 원소를 하나 추가
	if (root == NULL)
	{
		root = (node*)malloc(sizeof(node));
		root->nkeys = 1;
		root->child[0] = NULL;
		root->child[1] = NULL;
		root->child[2] = NULL;
		root->child[3] = NULL;
		root->key[0] = k;
	}
	//추가하려는 node* n이 leaf노드인 경우, key 값을 추가해준다.
	else if (n->child[0] == NULL)
	{
		n->key[(n->nkeys)++] = k;
		Sort(n->key, n->nkeys);
	}
	//추가해주려는 node* n이 leaf노드가 아닌 경우
	else if (n->child[0] != NULL)
	{
		//key 값을 추가해야하는 child의 index값을 next에 담는다
		int next;
		for (int i = 0;i <= n->nkeys;i++)
		{
			if (i == 0)
			{
				if (k < n->key[i])
					next = i;
			}
			else if (i == n->nkeys)
			{
				if (k > n->key[i - 1])
					next = i;
			}
			else
			{
				if (k > n->key[i - 1] && k < n->key[i])
					next = i;
			}
		}
		//n->child[next]에 key 값을 insert한다
		insert(k, n->child[next]);
		//->child[next]에 key 값을 insert했을 때 overflow가 일어난 경우
		if (n->child[next]->nkeys == 3)
		{
			//child[0]에서 overflow가 일어났을 때
			if (next == 0)
			{
				//key-rotation이 가능하면, rotate해준다
				if (n->child[1]->nkeys == 1)
				{
					n->child[1]->key[(n->child[1]->nkeys)++] = n->key[0];
					Sort(n->child[1]->key, n->child[1]->nkeys);
					n->key[0] == n->child[0]->key[2];
					(n->child[0]->nkeys)--;
					for (int i = n->child[1]->nkeys - 1;i >= 0;i--)
						n->child[1]->child[i + 1] = n->child[1]->child[i];
					n->child[1]->child[0] = n->child[0]->child[3];
				}
				//Node split해준다
				else
				{
					n->key[(n->nkeys)++] = n->child[0]->key[1];
					Sort(n->key, n->nkeys);
					for (int i = n->nkeys - 1;i > 0;i--)
						n->child[i + 1] = n->child[i];
					node* n1 = (node*)malloc(sizeof(node));
					node* n2 = (node*)malloc(sizeof(node));
					n1->nkeys = 1;
					n2->nkeys = 1;
					n1->key[0] = n->child[0]->key[0];
					n2->key[0] = n->child[0]->key[2];
					n1->child[0] = n->child[0]->child[0];
					n1->child[1] = n->child[0]->child[1];
					n1->child[2] = NULL;
					n1->child[3] = NULL;
					n2->child[0] = n->child[0]->child[2];
					n2->child[1] = n->child[0]->child[3];
					n2->child[2] = NULL;
					n2->child[3] = NULL;
					free(n->child[0]);
					n->child[0] = n1;
					n->child[1] = n2;
					
				}
			}
			//child[2]에서 overflow가 일어났을 때
			else if (next == 2)
			{
				//key-rotation이 가능하면, rotation해준다
				if (n->child[1]->nkeys == 1)
				{
					n->child[1]->key[(n->child[1]->nkeys)++] = n->key[1];
					n->key[1] = n->child[2]->key[0];
					(n->child[2]->nkeys)--;
					n->child[2]->key[0] = n->child[2]->key[2];
					Sort(n->child[2]->key, n->child[2]->nkeys);
					n->child[1]->child[2] = n->child[2]->child[0];
					for (int i = 0;i <= 2;i++)
						n->child[2]->child[i] = n->child[2]->child[i + 1];
					n->child[3] == NULL;
				}
				//Node split해준다
				else
				{
					n->key[(n->nkeys)++] = n->child[2]->key[1];
					node* n1 = (node*)malloc(sizeof(node));
					node* n2 = (node*)malloc(sizeof(node));
					n1->nkeys = 1;
					n2->nkeys = 1;
					n1->key[0] = n->child[2]->key[0];
					n2->key[0] = n->child[2]->key[2];
					n1->child[0] = n->child[2]->child[0];
					n1->child[1] = n->child[2]->child[1];
					n1->child[2] = NULL;
					n1->child[3] = NULL;
					n2->child[0] = n->child[2]->child[2];
					n2->child[1] = n->child[2]->child[3];
					n2->child[2] = NULL;
					n2->child[3] = NULL;
					free(n->child[2]);
					n->child[2] = n1;
					n->child[3] = n2;
					
				}
			}
			//child[2]에서 overflow가 일어났을 때
			else if(next == 1)
			{
				//child[0]과 key-rotation이 가능하면, rotation해준다
				if (n->child[0]->nkeys == 1)
				{
					n->child[0]->key[(n->child[0]->nkeys)++] = n->key[0];
					n->key[0] = n->child[1]->key[0];
					(n->child[1]->nkeys)--;
					n->child[1]->key[0] = n->child[1]->key[2];
					Sort(n->child[1]->key, n->child[1]->nkeys);
					n->child[0]->child[2] = n->child[1]->child[0];
					for (int i = 0;i <= 2;i++)
						n->child[1]->child[i] = n->child[0]->child[i + 1];
					n->child[0]->child[3] = NULL;
				}
				//child[2]와 key-rotation이 가능하면, rotation해준다
				else if (n->nkeys == 2 && n->child[2]->nkeys == 1)
				{
					n->child[2]->key[(n->child[2]->nkeys)++] = n->key[1];
					Sort(n->child[2]->key, n->child[2]->nkeys);
					n->key[1] = n->child[1]->key[2];
					(n->child[1]->nkeys)--;
					for (int i = n->child[2]->nkeys - 1;i >= 0;i--)
						n->child[2]->child[i + 1] = n->child[2]->child[i];
					n->child[2]->child[0] = n->child[1]->child[3];
					n->child[1]->child[3] = NULL;
				}
				//Node split해준다
				else
				{
					n->key[(n->nkeys)++] = n->child[1]->key[1];
					Sort(n->key, n->nkeys);
					node* n1 = (node*)malloc(sizeof(node));
					node* n2 = (node*)malloc(sizeof(node));
					n1->nkeys = 1;
					n2->nkeys = 1;
					n1->key[0] = n->child[1]->key[0];
					n2->key[0] = n->child[1]->key[2];
					n1->child[0] = n->child[1]->child[0];
					n1->child[1] = n->child[1]->child[1];
					n1->child[2] = NULL;
					n1->child[3] = NULL;
					n2->child[0] = n->child[1]->child[2];
					n2->child[1] = n->child[1]->child[3];
					n2->child[2] = NULL;
					n2->child[3] = NULL;
					if (n->nkeys == 1)
					{
						node* temp = n->child[1];
						n->child[1] = n1;
						n->child[2] = n2;
						free(temp);
					}
					else
					{
						node* temp = n->child[1];
						n->child[3] = n->child[2];
						n->child[1] = n1;
						n->child[2] = n2;
						free(temp);
					}
				}
			}
		}
	}
	//node* n이 root이고, overflow되었을 때, Node split해준다
	if (n == root && n->nkeys == 3)
	{
		node* n1 = (node*)malloc(sizeof(node));
		node* n2 = (node*)malloc(sizeof(node));
		n1->nkeys = 1;
		n2->nkeys = 1;
		n1->key[0] = n->key[0];
		n2->key[0] = n->key[2];
		n1->child[0] = n->child[0];
		n1->child[1] = n->child[1];
		n1->child[2] = NULL;
		n1->child[3] = NULL;
		n2->child[0] = n->child[2];
		n2->child[1] = n->child[3];
		n2->child[2] = NULL;
		n2->child[3] = NULL;
		n->nkeys = 1;
		n->key[0] = n->key[1];
		n->child[0] = n1;
		n->child[1] = n2;
		n->child[2] = NULL;
		n->child[3] = NULL;
	}
}

//node* n의 값을 정렬된 순서로 출력해준다
void inorder(node* n)
{
	if (n)
	{
		for (int i = 0;i <= n->nkeys;i++)
		{
			inorder(n->child[i]);
			if (i != n->nkeys)
				fprintf(fp1, "%d ", n->key[i]);
		}
	}
}

int main()
{
	fp = fopen("input.txt", "r");
	fp1 = fopen("output.txt", "w");
	//root를 NULL로 초기화시켜준다
	root = NULL;
	//i가 들어오면 insert해주고, p가 들어오면 모든 값들을 print해준다
	while (1)
	{
		char ch[2];
		if (fscanf(fp, "%s", ch) == EOF)
			break;
		else if (ch[0] == 'i')
		{
			int num;
			fscanf(fp, "%d", &num);
			insert(num, root);
		}
		else if (ch[0] == 'p')
		{
			inorder(root);
			fprintf(fp1, "\n");
		}
	}
}
