#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n;
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &n);
	int* a = (int*)malloc(sizeof(int)*n);
	for (int i = 0;i < n;i++)
		fscanf(fp, "%d", a + i);
	for (int i = 0;i < n;i++)
	{
		int m = a[i], c = -1, s;
		for (int j = i;j < n;j++)
		{
			if (m > a[j])
			{
				c = j;
				m = a[j];
			}
		}
		if (c != -1)
		{
			s = a[i];
			a[i] = a[c];
			a[c] = s;
		}
	}
	fclose(fp);
	FILE* fp1 = fopen("output.txt", "w");
	for (int i = 0;i < n;i++)
		fprintf(fp1, "%d ", a[i]);
	fclose(fp1);
	free(a);
}
