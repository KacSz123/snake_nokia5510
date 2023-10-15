/*
 * lcd_nokia5510.c
 *
 *  Created on: Oct 4, 2023
 *      Author: kacper
 */


#include "lcd_nokia5510.h"
#include "gpio.h"
#include "stdlib.h"
#include "memory.h"
#include "math.h"

SPI_HandleTypeDef *spi;

static uint8_t LCD_NOKIA5510_dataBuffer[LCD_BUFFER_SIZE];
//spi = &

void LCD_NOKIA5510_resetInit(SPI_HandleTypeDef* sp)
{
	spi = sp;
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
	HAL_Delay(20);

	memset(LCD_NOKIA5510_dataBuffer, 0, LCD_BUFFER_SIZE);
}

void LCD_NOKIA5510_initDefault(SPI_HandleTypeDef *sp)
{

	LCD_NOKIA5510_resetInit(sp);
	LCD_NOKIA5510_cmd(0x21);
	LCD_NOKIA5510_cmd(0x14);
	LCD_NOKIA5510_cmd(0x80 | 0x2f); //Ustawienie kontrastu
	LCD_NOKIA5510_cmd(0x20);
	LCD_NOKIA5510_cmd(0x0c);

	LCD_NOKIA5510_cmd(0x40);
	LCD_NOKIA5510_cmd(0x80);
}


void LCD_NOKIA5510_reset()
{
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
}

void LCD_NOKIA5510_cmd(uint8_t cmd)
{
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(spi, &cmd, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}
void LCD_NOKIA5510_sendData(uint8_t *data, int size)
{
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(spi, data, size, HAL_MAX_DELAY);
//	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
}

void LCD_NOKIA5510_sendDataBuffer()
{
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(spi,LCD_NOKIA5510_dataBuffer , LCD_BUFFER_SIZE, 100);
//	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
}

void LCD_NOKIA5510_drawPixel(uint8_t x, uint8_t y)
{
	LCD_NOKIA5510_dataBuffer[x+(y>>3)*LCD_WIDTH] |= 1<<(y&7);
}


void LCD_NOKIA5510_erasePixel(uint8_t x, uint8_t y)
{
	LCD_NOKIA5510_dataBuffer[x+(y>>3)*LCD_WIDTH] &= ~(1<<(y&7));
}


void LCD_NOKIA5510_clearScreen()
{
	memset(LCD_NOKIA5510_dataBuffer, 0, LCD_BUFFER_SIZE);

	LCD_NOKIA5510_cmd(0x40);
	LCD_NOKIA5510_cmd(0x80);
}


void LCD_NOKIA5510_drawLine2Points(uint8_t x1, uint8_t y1,uint8_t x2, uint8_t y2)
{
	   int d, dx, dy, ai, bi, xi, yi;
	     int x = x1, y = y1;
	     // direction of drawing x
	     if (x1 < x2)
	     {
	         xi = 1;
	         dx = x2 - x1;
	     }
	     else
	     {
	         xi = -1;
	         dx = x1 - x2;
	     }
	     // direction of drawing y
	     if (y1 < y2)
	     {
	         yi = 1;
	         dy = y2 - y1;
	     }
	     else
	     {
	         yi = -1;
	         dy = y1 - y2;
	     }
	     // 1st pixel
	     LCD_NOKIA5510_drawPixel(x, y);
	     // axis OX
	     if (dx > dy)
	     {
	         ai = (dy - dx) * 2;
	         bi = dy * 2;
	         d = bi - dx;
	         // loop xi
	         while (x != x2)
	         {
	             // oaram test
	             if (d >= 0)
	             {
	                 x += xi;
	                 y += yi;
	                 d += ai;
	             }
	             else
	             {
	                 d += bi;
	                 x += xi;
	             }
	    	     LCD_NOKIA5510_drawPixel(x, y);
	         }
	     }
	     // axis OY
	     else
	     {
	         ai = ( dx - dy ) * 2;
	         bi = dx * 2;
	         d = bi - dy;
	         // loop yi
	         while (y != y2)
	         {
	             // param test
	             if (d >= 0)
	             {
	                 x += xi;
	                 y += yi;
	                 d += ai;
	             }
	             else
	             {
	                 d += bi;
	                 y += yi;
	             }
	    	     LCD_NOKIA5510_drawPixel(x, y);
	         }
	     }
}
void LCD_NOKIA5510_drawRectangle(int x1, int y1, int x2, int y2,
								int x3, int y3, int x4, int y4)
{
	LCD_NOKIA5510_drawLine2Points(x1, y1, x2, y2);
	LCD_NOKIA5510_drawLine2Points(x2, y2, x3, y3);
	LCD_NOKIA5510_drawLine2Points(x3, y3, x4, y4);
	LCD_NOKIA5510_drawLine2Points(x4, y4, x1, y1);

}
void LCD_NOKIA5510_drawLine2PointsStruct(LCD_POINT_TYPEDEF p1, LCD_POINT_TYPEDEF p2)
{
	LCD_NOKIA5510_drawLine2Points(p1.x, p1.y, p2.x,p2.y);
	}
void LCD_NOKIA5510_drawRectangleStruct(LCD_POINT_TYPEDEF p1, LCD_POINT_TYPEDEF p2,
									LCD_POINT_TYPEDEF p3, LCD_POINT_TYPEDEF p4)
{
	LCD_NOKIA5510_drawRectangle(p1.x, p1.y,p2.x, p2.y,p3.x, p3.y,p4.x, p4.y);
}

void LCD_NOKIA5510_drawCircle(int mx, int my, int rad)
{
	int x=0,y,p;
	y=rad;
	LCD_NOKIA5510_drawPixel(mx-x, my-y);

	p =(int)(3-(2*rad));
	for(x = 0; x<=y; ++x)
	{
		if(p<0)
		{
			p=(int)(p+(4*x)+(2*3));
		}
		else{
			y-=1;
			p+=((4*(x-y)+10));
			}

		LCD_NOKIA5510_drawPixel(mx+x,my-y);
		LCD_NOKIA5510_drawPixel(mx-x,my-y);
		LCD_NOKIA5510_drawPixel(mx+x,my+y);
		LCD_NOKIA5510_drawPixel(mx-x,my+y);
		LCD_NOKIA5510_drawPixel(mx+y,my-x);
		LCD_NOKIA5510_drawPixel(mx-y,my-x);
		LCD_NOKIA5510_drawPixel(mx+y,my+x);
		LCD_NOKIA5510_drawPixel(mx-y,my+x);
	}
}
