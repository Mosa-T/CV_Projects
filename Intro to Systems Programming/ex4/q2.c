/*
* hw4q2.c
*
*  Created on: Jun 5, 2018
*  
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>




struct AdjListNode {
	int dest;
	struct AdjListNode* next;
};

struct AdjList {
	struct AdjListNode *head;  
};

struct Graph {
	int V;
	struct AdjList* array;
};

int isCoverVerteces(struct Graph *graph, int Group[], int group_M)

{
	int i;
	int flag;
	int j;
	struct AdjList *temp;
	struct AdjListNode *tempHead;
	temp = graph->array;
	if (graph == NULL)
		return -1;
	
		for (i = 0; i < graph->V; i++) {
			tempHead = (temp + i)->head;
			flag = 0;
			while (tempHead != NULL) {
				for (j = 0; j < group_M; j++)
				{
					if (tempHead->dest == Group[j])
						flag = 1;
				}
				tempHead = tempHead->next;
			}
			if (flag == 0)
				return 0;
		}
	return 1;
}


int main()
{
	int secarr[2] = { 1, 2};
	int i;
	struct Graph *temp = (struct Graph *)malloc(sizeof(struct Graph));
	temp->V = 4;
	temp->array = (struct AdjList *)malloc(4 * sizeof(struct AdjList));

	for (i = 0; i < 4; i++)
	{
		((temp->array) + i)->head = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
	}

	temp->array->head->dest = 0;
	temp->array->head->next = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
	temp->array->head->next->dest = 1;
	temp->array->head->next->next = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
	temp->array->head->next->next->dest = 2;
	temp->array->head->next->next->next = NULL;


	(temp->array + 1)->head->dest = 1;
	(temp->array + 1)->head->next = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
	(temp->array + 1)->head->next->dest = 2;
	(temp->array + 1)->head->next->next = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
	(temp->array + 1)->head->next->next->dest = 0;
	(temp->array + 1)->head->next->next->next = NULL;


	(temp->array + 2)->head->dest = 2;
	(temp->array + 2)->head->next = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
	(temp->array + 2)->head->next->dest = 0;
	(temp->array + 2)->head->next->next = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
	(temp->array + 2)->head->next->next->dest = 1;
	(temp->array + 2)->head->next->next->next = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
	(temp->array + 2)->head->next->next->next->dest = 3;
	(temp->array + 2)->head->next->next->next->next = NULL;

	(temp->array + 3)->head->dest = 3;
	(temp->array + 3)->head->next = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
	(temp->array + 3)->head->next->dest = 2;
	(temp->array + 3)->head->next->next = NULL;

	i = isCoverVerteces(temp, secarr, 2);
	printf("%d\n", i);
	return 0;
}