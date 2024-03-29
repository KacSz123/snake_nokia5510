/*
 * snake.c
 *
 *  Created on: Oct 4, 2023
 *      Author: kacper
 */


#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include "lcd_nokia5510.h"
void SNAKE_GAME_addSnakeNode(node_Typedef *h, int x, int y)
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

	node_tmp->next->headFlag = false;
	node_tmp->next->prev = node_tmp;
	node_tmp->next->next = NULL;
}
void SNAKE_GAME_snakeHeadInit(int x, int y, node_Typedef *h)
{

	h->coords[0] = x;
	h->coords[1] = y;
	h->orientation = UP;
	// h->headFlag = true;
	h->next = NULL;
	h->prev = NULL;
}

void SNAKE_GAME_removeSnake(node_Typedef *h)
{

}
void SNAKE_GAME_moveSnakeNode(node_Typedef *h)
{
	switch (h->orientation) {
	case UP:{
		(h->coords[1])-=4;
		break;
	}
	case DOWN:{
		(h->coords[1])+=4;
		break;
	}
	case LEFT:{
		(h->coords[0])-=4;
		break;
	}
	case RIGHT:{
		(h->coords[0])+=4;
		break;
	}
		default:
			break;
	}

}
void SNAKE_GAME_moveSnake(node_Typedef *h/*, bool ifEaten, int orient*/)
{
	node_Typedef *node_tmp = h;
	SNAKE_GAME_moveSnakeNode(node_tmp);
	while(node_tmp->next!=NULL)
	{
		node_tmp = node_tmp->next;
		SNAKE_GAME_moveSnakeNode(node_tmp);
	};
	while(node_tmp!=NULL)
	{
		SNAKE_GAME_changeOrientation(node_tmp, node_tmp->prev->orientation);
		node_tmp = node_tmp->prev;
	}


}

void SNAKE_GAME_changeOrientation(node_Typedef *snake,SnakeOrientation_Typedef orient)
{
	switch(orient)
	{
	case UP:
	{
		snake->orientation = UP;
		break;
	}
	case DOWN:
	{
		snake->orientation = DOWN;
		break;
	}
	case LEFT:
	{
		snake->orientation = LEFT;
		break;
	}
	case RIGHT:
	{
		snake->orientation = RIGHT;
		break;
	}
	}
}


void SNAKE_GAME_drawSnakeNode(node_Typedef const  *snakeNode)
{
	for(int i=0; i<4; ++i)
	{
		LCD_NOKIA5510_drawPixel(snakeNode->coords[0]-1, snakeNode->coords[1]-1+i);
		LCD_NOKIA5510_drawPixel(snakeNode->coords[0]+2, snakeNode->coords[1]-1+i);
	}
	for(int i=0; i<2; ++i)
	{
		LCD_NOKIA5510_drawPixel(snakeNode->coords[0]+i, snakeNode->coords[1]-1);
		LCD_NOKIA5510_drawPixel(snakeNode->coords[0]+i, snakeNode->coords[1]+2);
	}
	if(snakeNode->headFlag)
		LCD_NOKIA5510_drawPixel(snakeNode->coords[0],snakeNode->coords[1]);
}

void SNAKE_GAME_drawSnake(node_Typedef *const snakeHead)
{
	const node_Typedef *tmp = snakeHead;
	while(tmp!=NULL)
	{
		SNAKE_GAME_drawSnakeNode(tmp);
		tmp = tmp->next;
	}
}

void SNAKE_GAME_drawFruit(fruit_Typedef *const fruit)
{

}
