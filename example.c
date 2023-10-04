
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "snake_ADT.h"
//#include <memory.h>

int main(void)
{


	node_Typedef *head = (node_Typedef *)malloc(sizeof(node_Typedef));
	snakeHeadInit(5, 5, head);

	moveSnake(head, 1, UP);
	moveSnake(head, 0, UP);
	moveSnake(head, 1, UP);
	moveSnake(head, 0, UP);
	moveSnake(head, 1, UP);
	moveSnake(head, 0, UP);
	moveSnake(head, 1, UP);
	moveSnake(head, 0, UP);
	moveSnake(head, 1, UP);

	return 0;
}
