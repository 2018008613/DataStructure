#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE* fp;
FILE* fp1;

typedef struct TreeNode tree;
struct TreeNode {
	int value;
	tree* left;
	tree* right;
};

//value가 이미 있으면 에러메세지를 출력, 아니면 그 값을 트리에 insert 해주는 함수
tree* InsertNode(int value, tree* root)
{
	if (root == NULL)
	{
		root = (tree*)malloc(sizeof(tree));
		root->value = value;
		root->left = NULL;
		root->right = NULL;
	}
	else if (value < root->value)
		root->left = InsertNode(value, root->left);
	else if (value > root->value)
		root->right = InsertNode(value, root->right);
	else
		fprintf(fp1, "%d already exists.\n", value);
	return root;
}

//tree에서 가장 큰 값을 가지고 있는 tree*를 리턴해주는 함수 root가 null이면 root를 return
tree* FindMax(tree* root)
{
	if (root == NULL)
		return root;
	while (root->right != NULL)
		root = root->right;
	return root;
}

//tree 안에서 value를 가지는 노드를 삭제해주는 함수 value가 tree 안에 없으면 에러메세지 출력
tree* DeleteNode(int value, tree *root)
{
	if (root == NULL)
		fprintf(fp1, "Deletion failed. %d does not exist.\n", value);
	else if (root->value > value)
		root->left = DeleteNode(value, root->left);
	else if (root->value < value)
		root->right = DeleteNode(value, root->right);
	else if (root->right != NULL && root->left != NULL)
	{
		tree* tmp = FindMax(root->left);
		root->value = tmp->value;
		root->left = DeleteNode(tmp->value, root->left);
	}
	else
	{
		tree* tmp = root;
		if (root->left == NULL)
			root = root->right;
		else if (root->right == NULL)
			root = root->left;
		free(tmp);
	}
	return root;
}

//value가 있으면 그 tree*를 return 해주고, 없으면 NULL을 return 해주는 함수
tree* FindNode(int value, tree *root)
{
	if (root == NULL)
		return root;
	else if (root->value == value)
		return root;
	else if (root->value > value)
		return FindNode(value, root->left);
	else
		return FindNode(value, root->right);
}

//tree를 inorder 순서로 출력
void PrintInorder(tree *root)
{
	if (root == NULL)
		return;
	else
	{
		PrintInorder(root->left);
		fprintf(fp1, "%d ", root->value);
		PrintInorder(root->right);
	}
}

//tree를 preorder 순서로 출력
void PrintPreorder(tree *root)
{
	if (root == NULL)
		return;
	else
	{
		fprintf(fp1, "%d ", root->value);
		PrintPreorder(root->left);
		PrintPreorder(root->right);
	}
}

//tree를 postorder 순서로 출력
void PrintPostorder(tree *root)
{
	if (root == NULL)
		return;
	else
	{
		PrintPostorder(root->left);
		PrintPostorder(root->right);
		fprintf(fp1, "%d ", root->value);
	}
}



int main()
{
	fp = fopen("input.txt", "r");
	fp1 = fopen("output.txt", "w");
	//tree 생성
	tree* tr = NULL;
	while (1)
	{
		char ch[3];
		if (fscanf(fp, "%s", ch) == EOF)
			break;
		else if (ch[0] == 'i')
		{
			//v를 insert
			int v;
			fscanf(fp, "%d", &v);
			tr = InsertNode(v, tr);
		}
		else if (ch[0] == 'd')
		{
			//v를 delete
			int v;
			fscanf(fp, "%d", &v);
			tr = DeleteNode(v, tr);
		}
		else if (ch[0] == 'f')
		{
			//v를 find
			int v;
			fscanf(fp, "%d", &v);
			tree* tmp = FindNode(v, tr);
			if (tmp == NULL)
				fprintf(fp1, "%d is not in the tree.\n", v);
			else
				fprintf(fp1, "%d is in the tree.\n", v);
		}
		else if (strcmp(ch, "pi") == 0)
		{
			//inorder 출력
			fprintf(fp1, "pi - ");
			PrintInorder(tr);
			fprintf(fp1, "\n");
		}
		else if (strcmp(ch, "pr") == 0)
		{
			//preorder 출력
			fprintf(fp1, "pr - ");
			PrintPreorder(tr);
			fprintf(fp1, "\n");
		}
		else if (strcmp(ch, "po") == 0)
		{
			//postorder 출력
			fprintf(fp1, "po - ");
			PrintPostorder(tr);
			fprintf(fp1, "\n");
		}
	}
	//tr의 모든 node들을 free해준다
	while (tr != NULL)
		tr = DeleteNode(tr->value, tr);
}
