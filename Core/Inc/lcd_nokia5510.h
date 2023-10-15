/*
 * lcd_nokia5510.h
 *
 *  Created on: Oct 4, 2023
 *      Author: kacper
 */

#ifndef INC_LCD_NOKIA5510_H_
#define INC_LCD_NOKIA5510_H_
//#include <stdint.h>
#include "spi.h"

#define LCD_WIDTH 84
#define LCD_HEIGHT 48
#define PIXEL_SIZE 8

#define LCD_BUFFER_SIZE			(LCD_WIDTH * LCD_HEIGHT/PIXEL_SIZE)

#ifndef LCD_BUFFER
#define LCD_BUFFER
#endif

#define LCD_ACT_MODE 0<<2
#define LCD_POW_D_MODE 1<<2

#define LCD_VAL_HOR 0<<1
#define LCD_VAL_VER 1<<1

#define LCD_BASIC_CMD 0
#define LCD_ADD_CMD 1

#define LCD_N5110_FUNSET (0x20|(LCD_ACT_MODE|LCD_VAL_HOR|LCD_ADD_CMD))

#define LCD_Y 5
#define LCD_N5110_Y_POSE 0x40|LCD_Y


//SPI_HandleTypeDef spi = hspi2;
typedef enum LCD
{
	 LCD_NOKIA5510_OK=0,
	 LCD_NOKIA5510_ERROR=1,
	 LCD_NOKIA5510_UNKNOWN=2,
	 LCD_NOKIA5510_BADPARAM=3
} LCD_NOKIA5510_TypedefEnum;

typedef struct point
{
	int x;
	int y;
}LCD_POINT_TYPEDEF;
/**
 * @brief Reset of lcd with longer sleep time for initialization.
 * @param[in] - SPI_HandleTypeDef *sp: SPI handler object
 */
void LCD_NOKIA5510_resetInit(SPI_HandleTypeDef *sp);

void LCD_NOKIA5510_initDefault(SPI_HandleTypeDef *sp);

/**
 * @brief Reset of lcd..
 */
void LCD_NOKIA5510__reset();

/*!
 * @brief Send command to LCD.
 * @param[in] - cmd: command to send-> look in datasheet
 */
void LCD_NOKIA5510_cmd(uint8_t cmd);


/*!
 * @brief Send
 */


//void LCD_NOKIA5510_data(uint8_t*data, int size);
void LCD_NOKIA5510_drawBitmap();

void LCD_NOKIA5510_drawPixel(uint8_t x, uint8_t y);

void LCD_NOKIA5510_sendData(uint8_t *data, int size);
void LCD_NOKIA5510_sendDataBuffer();

void LCD_NOKIA5510_erasePixel(uint8_t x, uint8_t y);
void LCD_NOKIA5510_clearScreen();
void LCD_NOKIA5510_drawLine2Points(uint8_t x1, uint8_t y1,uint8_t x2, uint8_t y2);
void LCD_NOKIA5510_drawLine2PointsStruct(LCD_POINT_TYPEDEF p1, LCD_POINT_TYPEDEF p2);

void LCD_NOKIA5510_drawRectangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void LCD_NOKIA5510_drawRectangleStruct(LCD_POINT_TYPEDEF p1, LCD_POINT_TYPEDEF p2,
									LCD_POINT_TYPEDEF p3, LCD_POINT_TYPEDEF p4);

void LCD_NOKIA5510_drawCircle(int mx, int my, int rad);

#endif /* INC_LCD_NOKIA5510_H_ */
