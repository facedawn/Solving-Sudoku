#include <stdio.h>
#include <string.h>
#include <math.h>
int a[10][10][15];
void flag(int i, int j)
{
	int n = 0;
	if (a[i][j][0] != 0)
	{
		for (n = 0; n < 9; n++)
		{
			if (a[n][j][a[i][j][0]] != 1)
			{
				a[n][j][11]++;
				a[n][j][a[i][j][0]] = 1;
			}
			if (a[i][n][a[i][j][0]] != 1)
			{
				a[i][n][11]++;
				a[i][n][a[i][j][0]] = 1;
			}
			if (a[i / 3 * 3 + n / 3][j / 3 * 3 + n % 3][a[i][j][0]] != 1)
			{
				a[i / 3 * 3 + n / 3][j / 3 * 3 + n % 3][11]++;
				a[i / 3 * 3 + n / 3][j / 3 * 3 + n % 3][a[i][j][0]] = 1;
			}
			if (a[i][j][n + 1] != 1)
			{
				a[i][j][n + 1] = 1;
				a[i][j][11]++;
			}
		}
	}
}
void find()
{
	int count = 0, i, j;
	while (count == 0)
	{
		count = 1;
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				if (a[i][j][11] == 8 && a[i][j][0] == 0)
				{
					int p;
					for (p = 1; p <= 9; p++)
					{
						if (a[i][j][p] != 1)
						{
							a[i][j][0] = p;
							flag(i, j);
							a[i][j][p] = 1;
							a[i][j][11]++;
							break;
						}
					}
					count = 0;
				}
				if (a[i][j][0] == 0)
				{
					int n;
					int p, cn1 = 0, cn2 = 0, cn3 = 0;
					for (p = 1; p <= 9; p++)
					{
						cn1 = 0, cn2 = 0, cn3 = 0;
						if (a[i][j][p] == 0)
						{
							for (n = 0; n < 9; n++)
							{

								if (a[n][j][p] == 0 && n != i)
								{
									cn1 = 1;
								}
								if (a[i][n][p] == 0 && n != j)
								{
									cn2 = 1;
								}
								if (a[i / 3 * 3 + n / 3][j / 3 * 3 + n % 3][p] == 0)
								{
									if (i / 3 * 3 + n / 3 == i && j / 3 * 3 + n % 3 == j);
									else
										cn3 = 1;
								}
								if (cn1 == 1 && cn2 == 1 && cn3 == 1)
								{
									continue;
								}
							}
							if (cn1 == 0 || cn2 == 0 || cn3 == 0)
							{
								a[i][j][0] = p;
								flag(i, j);
								count = 0;
								break;
							}
						}
					}
				}
			}
		}
	}
}
int max = 0;
void dfs()
{
	int i, j, count = 0, b[10][10];
	int maxn = -1, maxi = 0, maxj = 0;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			b[i][j] = a[i][j][0];
			if (b[i][j] == 0)
				count = 1;
			if (maxn < 7 && count == 1 && a[i][j][11]<9 && a[i][j][11]>maxn && a[i][j][0] == 0)
			{
				maxn = a[i][j][11];
				maxi = i;
				maxj = j;
			}
		}
	}
	int n, sum = 0, num = 0;
	if (count == 0)
	{
		printf("\n");
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				printf("%d ", a[i][j][0]);
			}
			printf("\n");
		}
		printf("\n");
		
	}
	else
	{
		int n;
		i = maxi;
		j = maxj;
		if (a[i][j][0] == 0)
		{
			for (n = 1; n <= 9; n++)
			{
				if (a[i][j][n] == 0)
				{
					a[i][j][0] = n;
					flag(i, j);
					find();
					dfs();
					int o1, o2;
					memset(a, 0, sizeof(a));
					for (o1 = 0; o1 < 9; o1++)
					{
						for (o2 = 0; o2 < 9; o2++)
						{
							a[o1][o2][0] = b[o1][o2];
							flag(o1, o2);
						}
					}
				}
			}
		}
	}
}
int main()
{
	int i, j;
	memset(a, 0, sizeof(a));
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			scanf("%d", &a[i][j][0]);
			flag(i, j);
		}
	}
	find();
	dfs();
	return 0;
}
