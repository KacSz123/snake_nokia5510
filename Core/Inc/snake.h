/*
 * snake.h
 *
 *  Created on: Oct 4, 2023
 *      Author: kacper
 */

#ifndef INC_SNAKE_H_
#define INC_SNAKE_H_




#include <stdint.h>
#include <stdbool.h>

typedef	enum
	orient{
		LEFT = 20,
		RIGHT = 30,
		UP = 40,
		DOWN = 60
	} SnakeOrientation_Typedef;
typedef struct node
{
	bool headFlag;
	int coords[2];
	SnakeOrientation_Typedef orientation;
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

void changeOrientation(node_Typedef *snake,SnakeOrientation_Typedef orient);

void drawSnakeNode(const node_Typedef *snake);

void drawSnake(const node_Typedef *snakeHead);

#endif /* INC_SNAKE_H_ */
