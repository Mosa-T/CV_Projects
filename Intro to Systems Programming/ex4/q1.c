#include <stdio.h>
#include <stdlib.h>

int isCoverVerteces(int *Graph[], int graph_N, int Group[], int group_M)

{
	int *flagArr = (int *)malloc(graph_N*(sizeof(int)));
	int i = 0;
	int k;
	int j;
	for (k = 0; k < group_M; k++)
	{
		for ( j = 0; j < graph_N; j++){
			if (Graph[(Group[k])][j] != 0)
			{
				flagArr[j] = 1;
			}
		}
	}
	for (i = 0; i < graph_N; i++)
	{
		if (flagArr[i] != 1){
			free(flagArr);
			return 0;
		}
	}
	free(flagArr);
	return 1;
}


int main()
{
	int secarr[2] = { 1,0 };
	int *temp[4];
	int i;
	for (i = 0; i < 4; i++)
	{
		temp[i] = (int *)malloc(4 * sizeof(int));
	}
	temp[0][0] = 0;
	temp[0][1] = 1;
	temp[0][2] = 1;
	temp[0][3] = 1;
	temp[1][0] = 1;
	temp[1][1] = 0;
	temp[1][2] = 1;
	temp[1][3] = 0;
	temp[2][0] = 1;
	temp[2][1] = 1;
	temp[2][2] = 0;
	temp[2][3] = 0;
	temp[3][0] = 1;
	temp[3][1] = 0;
	temp[3][2] = 0; 
	temp[3][3] = 0;

	

	i = isCoverVerteces(temp, 4, secarr, 2);
	printf("%d\n", i);
	return 0;
}