
#include "snake_ADT.h"
#include <stdio.h>
#include <stdlib.h>
void addSnakeNode(node_Typedef *h, int x, int y)
{
	node_Typedef *node_tmp = h;

	while (node_tmp->next != NULL)
	{
		node_tmp = node_tmp->next;
	}
	node_tmp->next = (node_Typedef *)malloc(sizeof(node_Typedef));

	node_tmp->next->coords[0] = x;
	node_tmp->next->coords[1] = y;
	node_tmp->next->orientation = node_tmp->orientation;

	// node_tmp->next->headFlag = false;
	node_tmp->next->prev = node_tmp;
	node_tmp->next->next = NULL;
}
void snakeHeadInit(int x, int y, node_Typedef *h)
{

	h->coords[0] = x;
	h->coords[1] = y;
	h->orientation = UP;
	// h->headFlag = true;
	h->next = NULL;
	h->prev = NULL;
}

void removeSnake(node_Typedef *h)
{
}

void moveSnake(node_Typedef *h, bool ifEaten, int orient)
{
	node_Typedef *node_tmp = h;
	int tmp[2];
	tmp[0] = node_tmp->coords[0];
	tmp[1] = node_tmp->coords[1];

	while (node_tmp->next != NULL)
	{
		node_tmp = node_tmp->next;

		tmp[0] = node_tmp->coords[0];
		tmp[1] = node_tmp->coords[1];

	}
	while(node_tmp->prev!=NULL)
	{
		node_tmp->coords[0] = node_tmp->prev->coords[0];
		node_tmp->coords[1] = node_tmp->prev->coords[1];
		node_tmp->orientation = node_tmp->prev->orientation;
		node_tmp = node_tmp->prev;
	}
	
	if (ifEaten)
	{
		addSnakeNode(h, tmp[0], tmp[1]);

	}
	h->coords[0]+=1;
	switch (orient)
	{
	case LEFT:
		/* code */
		break;
	case RIGHT:
		/* code */
		break;
	case UP:
		/* code */
		break;
	case DOWN:
		/* code */
		break;
	
	default:
		break;
	}
}

