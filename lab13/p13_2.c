#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* fp;
FILE* fp1;

//pivot 값을 return한다
int pivot(int* a, int l, int r,int s)
{
	if (s == 0)
		return a[l];
	//if (s == 1)
		return a[r];
	//return a[(l + r) / 2];
}

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//partition해준다
int pa(int* a, int l, int r, int s)
{
	
	int p = pivot(a, l, r, s);
	int i, j;
	if (s == 0)
	{
		i = l, j = r + 1;
		while (1)
		{
			while (a[--j] > p);
			while (a[++i] < p);
			if (i < j)
				swap(&a[i], &a[j]);
			else
			{
				swap(&a[j], &a[l]);
				fprintf(fp1, "<");
				for (int k = l; k < j;k++)
					fprintf(fp1, "%d ", a[k]);
				fprintf(fp1, ">");
				fprintf(fp1, "<");
				fprintf(fp1, "%d ", a[j]);
				fprintf(fp1, ">");
				fprintf(fp1, "<");
				for (int k = j + 1; k <= r;k++)
					fprintf(fp1, "%d ", a[k]);
				fprintf(fp1, ">\n");
				return j;
			}
		}
	}
	//else if (s == 1)
	//{
		i = l - 1, j = r;
		while (1)
		{
			while (a[--j] > p);
			while (a[++i] < p);
			if (i < j)
				swap(&a[i], &a[j]);
			else
			{
				swap(&a[i], &a[r]);
				fprintf(fp1, "<");
				for (int k = l; k < i;k++)
					fprintf(fp1, "%d ", a[k]);
				fprintf(fp1, ">");
				fprintf(fp1, "<");
				fprintf(fp1, "%d ", a[i]);
				fprintf(fp1, ">");
				fprintf(fp1, "<");
				for (int k = i + 1; k <= r;k++)
					fprintf(fp1, "%d ", a[k]);
				fprintf(fp1, ">\n");
				return i;
			}
		}
	//}
	/*int pivotIndex = (r + l) / 2;
	int pivotValue = a[pivotIndex];
	swap(&a[pivotIndex], &a[r]);
	int pos = l;
	for (int i = l; i < r; i++) {
		if (a[i] < pivotValue) {
			swap(&a[i], &a[pos]);
			pos++;
		}
	}
	swap(&a[pos], &a[r]);
	fprintf(fp1, "<");
	for (int k = l; k < pos;k++)
		fprintf(fp1, "%d ", a[k]);
	fprintf(fp1, ">");
	fprintf(fp1, "<");
	fprintf(fp1, "%d ", a[pos]);
	fprintf(fp1, ">");
	fprintf(fp1, "<");
	for (int k = pos + 1; k <= r;k++)
		fprintf(fp1, "%d ", a[k]);
	fprintf(fp1, ">\n");
	return pos;
	*/
}

//quick sort 해준다
void sort(int* a, int l, int r, int s)
{
	if (l >= r)
		return;
	int p = pa(a, l, r, s);
	sort(a, l, p - 1, s);
	sort(a, p + 1, r, s);
}

int main()
{
	fp = fopen("input.txt", "r");
	fp1 = fopen("output.txt", "w");
	char ch[20];
	while (fscanf(fp, "%s", ch) != EOF)
	{
		int n;
		fscanf(fp, "%d", &n);
		int* arr = (int*)malloc(sizeof(int)*(n + 1));
		for (int i = 0;i < n;i++)
			fscanf(fp, "%d", arr + i);
		//leftmost일때
		if (strcmp(ch, "leftmost") == 0)
		{
			fprintf(fp1, "leftmost:\n");
			sort(arr, 0, n - 1, 0);
		}
		//rightmost일때
		else if (strcmp(ch, "rightmost") == 0)
		{
			fprintf(fp1, "rightmost:\n");
			sort(arr, 0, n - 1, 1);
		}
		//else if (strcmp(ch, "middle") == 0)
		//{
		//	fprintf(fp1, "middle:\n");
		//	sort(arr, 0, n - 1, 2);
		//}
		fprintf(fp1, "\nresult:\n");
		for (int i = 0;i < n;i++)
			fprintf(fp1, "%d ", arr[i]);
		fprintf(fp1, "\n\n");
		free(arr);
	}
}
