#ifndef __SNAKE_ADT__
#define __SNAKE_ADT__


#include <stdint.h>
#include <stdbool.h>
typedef struct node
{
	bool headFlag;
	int coords[2];
	enum
	{
		LEFT = 20,
		RIGHT = 30,
		UP = 40,
		DOWN = 60
	} orientation;
	struct node *next;
	struct node *prev;

} node_Typedef;

typedef struct fruit
{
	int coords[2];
} fruit_Typedef;


void addSnakeNode(node_Typedef *h, int x, int y);

void snakeHeadInit(int x, int y, node_Typedef *h);

void removeSnake(node_Typedef *h);

void moveSnake(node_Typedef *h, bool ifEaten, int orient);
#endif // __SNAKE_ADT__
