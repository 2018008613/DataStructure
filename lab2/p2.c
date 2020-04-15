#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct A *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

typedef struct
{
	int studentID;
	char* studentName;
} ElementType;

struct A
{
	ElementType element;
	PtrToNode next;
};
typedef struct A Node;

void Insert(ElementType X, List L)
{
	List n;
	n = (Node*)malloc(sizeof(Node));
	n->element.studentID = X.studentID;
	n->element.studentName = (char*)malloc(sizeof(char)*(strlen(X.studentName) + 1));
	strcpy(n->element.studentName, X.studentName);
	n->next = NULL;
	Position A = L;
	int chk = 0;
	while (chk != 1)
	{
		if (A->next == NULL)
		{
			A->next = n;
			chk = 1;
		}
		if (A->next->element.studentID > n->element.studentID)
		{
			n->next = A->next;
			A->next = n;
			chk = 1;
		}
		A = A->next;
	}
}
Position FindB(ElementType X, List L)
{
	Position P = L;
	while (P->next != NULL)
	{
		if (X.studentID == P->next->element.studentID)
			return P;
		P = P->next;
	}
	return P;
}
void Delete(ElementType X, List L)
{
	Position P = FindB(X, L);
	Position N = P->next;
	P->next = N->next;
	free(N->element.studentName);
	free(N);
}
Position Find(ElementType X, List L)
{
	Position P = L;
	while (P->next != NULL)
	{
		if (X.studentID == P->element.studentID)
			return P;
		P = P->next;
	}
	return P;
}

void PrintList(List L, FILE* f)
{
	Position A = L->next;
	fprintf(f, "Current List > ");
	while (A->next != NULL)
	{
		fprintf(f, "%d %s-", A->element.studentID, A->element.studentName);
		A = A->next;
	}
	fprintf(f, "%d %s\n", A->element.studentID, A->element.studentName);
}
void PrintListP(List L, FILE* f)
{
	Position A = L->next;
	fprintf(f, "-----LIST-----\n");
	while (A != NULL)
	{
		fprintf(f, "%d %s\n", A->element.studentID, A->element.studentName);
		A = A->next;
	}
	fprintf(f, "--------------\n");
}
List MakeEmpty(List L)
{
	L = (Node*)malloc(sizeof(Node));
	L->next = NULL;
	L->element.studentID = 0;
	return L;
}
int IsEmpty(List L)
{
	if (L->next == NULL)
		return 1;
	return 0;
}
int IsLast(Position P, List L)
{
	if (P->next == NULL)
		return 1;
	return 0;
}
void DeleteList(List L)
{
	Position A = L->next;
	Position N;
	L->next = NULL;
	while (A != NULL)
	{
		N = A->next;
		free(A->element.studentName);
		free(A);
		A = N;
	}
}

int main()
{
	char ch = ' ';
	List L;
	L = MakeEmpty(L);
	FILE* fp = fopen("input.txt", "r");
	FILE* fp1 = fopen("output.txt", "w");
	while (ch != 'p')
	{
		fscanf(fp, "%c", &ch);
		if (ch == 'i')
		{
			int num;
			char na[31], na1[31];
			fscanf(fp, "%d", &num);
			fscanf(fp, "%s", na);
			fscanf(fp, "%s", na1);
			strcat(na, " ");
			strcat(na, na1);
			ElementType e;
			e.studentID = num;
			e.studentName = (char*)malloc(sizeof(char) * 31);
			strcpy(e.studentName, na);
			Position P = Find(e, L);
			if (P->element.studentID == e.studentID)
				fprintf(fp1, "Insertion Failed. ID %d already exists.\n", e.studentID);
			else
			{
				Insert(e, L);
				fprintf(fp1, "Insertion Success : %d\n", e.studentID);
				PrintList(L, fp1);
			}
			free(e.studentName);
		}
		if (ch == 'd')
		{
			int num;
			fscanf(fp, "%d", &num);
			ElementType e;
			e.studentID = num;
			Position P = Find(e, L);
			if (P->element.studentID == e.studentID)
			{
				Delete(e, L);
				fprintf(fp1, "Deletion Success : %d\n", e.studentID);
				PrintList(L, fp1);
			}
			else
				fprintf(fp1, "Deletion Failed : Student ID %d is not in the list.\n", e.studentID);
		}
		if (ch == 'f')
		{
			int num;
			fscanf(fp, "%d", &num);
			ElementType e;
			e.studentID = num;
			Position P = Find(e, L);
			if (P->element.studentID == e.studentID)
				fprintf(fp1, "Find Success : %d %s\n", e.studentID,P->element.studentName);
			else
				fprintf(fp1, "Find %d Failed. There is no student ID\n", e.studentID);
		}
		if (ch == 'p')
			PrintListP(L, fp1);
	}
	MakeEmpty(L);
	free(L);
}
