/**	
 * |----------------------------------------------------------------------
 * | Copyright (C) Tilen Majerle, 2014
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |
 * | Edited  By : Didi Alfandi 22/09/2021 (Roof-inno)
 * |----------------------------------------------------------------------
 */
//#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "dwt_delay.h"
#include "LCD_Lib.h"
/* Private LCD structure */
typedef struct {
	uint8_t DisplayControl;
	uint8_t DisplayFunction;
	uint8_t DisplayMode;
	uint8_t Rows;
	uint8_t Cols;
	uint8_t currentX;
	uint8_t currentY;
} LCD_Options_t;

/* Private functions */
static void LCD_InitPins(void);
static void LCD_Cmd(uint8_t cmd);
static void LCD_Cmd4bit(uint8_t cmd);
static void LCD_Data(uint8_t data);
//static void LCD_CursorSet(uint8_t col, uint8_t row);

/* Private variable */
static LCD_Options_t LCD_Opts;

/* Pin definitions */
#define LCD_RS_LOW             GPIO_SetPinLow(LCD_RS_PORT, LCD_RS_PIN)
#define LCD_RS_HIGH            GPIO_SetPinHigh(LCD_RS_PORT, LCD_RS_PIN)
#define LCD_E_LOW              GPIO_SetPinLow(LCD_E_PORT, LCD_E_PIN)
#define LCD_E_HIGH             GPIO_SetPinHigh(LCD_E_PORT, LCD_E_PIN)

#define LCD_E_BLINK             LCD_E_HIGH; LCD_Delay(20); LCD_E_LOW; LCD_Delay(20)
#define LCD_Delay(x)            DWT_Delay(x)

/* Commands*/
#define LCD_CLEARDISPLAY        0x01
#define LCD_RETURNHOME          0x02
#define LCD_ENTRYMODESET        0x04
#define LCD_DISPLAYCONTROL      0x08
#define LCD_CURSORSHIFT         0x10
#define LCD_FUNCTIONSET         0x20
#define LCD_SETCGRAMADDR        0x40
#define LCD_SETDDRAMADDR        0x80

/* Flags for display entry mode */
#define LCD_ENTRYRIGHT          0x00
#define LCD_ENTRYLEFT           0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

/* Flags for display on/off control */
#define LCD_DISPLAYON           0x04
#define LCD_CURSORON            0x02
#define LCD_BLINKON             0x01

/* Flags for display/cursor shift */
#define LCD_DISPLAYMOVE         0x08
#define LCD_CURSORMOVE          0x00
#define LCD_MOVERIGHT           0x04
#define LCD_MOVELEFT            0x00

/* Flags for function set */
#define LCD_8BITMODE            0x10
#define LCD_4BITMODE            0x00
#define LCD_2LINE               0x08
#define LCD_1LINE               0x00
#define LCD_5x10DOTS            0x04
#define LCD_5x8DOTS             0x00

void LCD_Init(uint8_t cols, uint8_t rows) {
	/* Initialize delay */
	//TM_DELAY_Init();
	DWT_Init();
	
	/* Init pinout */
	LCD_InitPins();
	
	/* At least 40ms */
	LCD_Delay(45000);
	
	/* Set LCD width and height */
	LCD_Opts.Rows = rows;
	LCD_Opts.Cols = cols;
	
	/* Set cursor pointer to beginning for LCD */
	LCD_Opts.currentX = 0;
	LCD_Opts.currentY = 0;
	
	LCD_Opts.DisplayFunction = LCD_4BITMODE | LCD_5x8DOTS | LCD_1LINE;
	if (rows > 1) {
		LCD_Opts.DisplayFunction |= LCD_2LINE;
	}
	
	/* Try to set 4bit mode */
	LCD_Cmd4bit(0x03);
	LCD_Delay(4500);
	
	/* Second try */
	LCD_Cmd4bit(0x03);
	LCD_Delay(4500);
	
	/* Third goo! */
	LCD_Cmd4bit(0x03);
	LCD_Delay(4500);	
	
	/* Set 4-bit interface */
	LCD_Cmd4bit(0x02);
	LCD_Delay(100);
	
	/* Set # lines, font size, etc. */
	LCD_Cmd(LCD_FUNCTIONSET | LCD_Opts.DisplayFunction);

	/* Turn the display on with no cursor or blinking default */
	LCD_Opts.DisplayControl = LCD_DISPLAYON;
	LCD_DisplayOn();

	/* Clear lcd */
	LCD_Clear();

	/* Default font directions */
	LCD_Opts.DisplayMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	LCD_Cmd(LCD_ENTRYMODESET | LCD_Opts.DisplayMode);

	/* Delay */
	LCD_Delay(4500);
}

void LCD_Clear(void) {
	LCD_Cmd(LCD_CLEARDISPLAY);
	LCD_Delay(3000);
}

void LCD_Puts(bool mode, char* str){
	//const uint8_t *buffer = (const uint8_t *)str;
	//size_t size = strlen(str);
		while(mode == 0 && *str) {
		if (LCD_Opts.currentX >= LCD_Opts.Cols) {
			LCD_Opts.currentX = 0;
			LCD_Opts.currentY++;
			LCD_CursorSet(LCD_Opts.currentX, LCD_Opts.currentY);
		}
		if (*str == '\n') {
			LCD_Opts.currentY++;
			//LCD_CursorSet(LCD_Opts.currentX, LCD_Opts.currentY);
		} //else if (*str == '\r') {
			//LCD_CursorSet(0, LCD_Opts.currentY);
		//} 
		else {
			LCD_Data(*str);
			LCD_Opts.currentX++;
		}
		str++;
	}
		
		if(mode == 1 && *str) {
		if (LCD_Opts.currentX >= LCD_Opts.Cols) {
			LCD_Opts.currentX = 0;
			LCD_Opts.currentY++;
			LCD_CursorSet(LCD_Opts.currentX, LCD_Opts.currentY);
		}
		if (*str == '\n') {
			LCD_Opts.currentY++;
			//LCD_CursorSet(LCD_Opts.currentX, LCD_Opts.currentY);
		} //else if (*str == '\r') {
			//LCD_CursorSet(0, LCD_Opts.currentY);
		//} 
		else {
			LCD_Data(*str);
			LCD_Opts.currentX++;
		}
		str++;
	}
}

void LCD_Putsxy(uint8_t x, uint8_t y, char* str) {
	LCD_CursorSet(x, y);
	while (*str) {
		if (LCD_Opts.currentX >= LCD_Opts.Cols) {
			LCD_Opts.currentX = 0;
			LCD_Opts.currentY++;
			LCD_CursorSet(LCD_Opts.currentX, LCD_Opts.currentY);
		}
		if (*str == '\n') {
			LCD_Opts.currentY++;
			LCD_CursorSet(LCD_Opts.currentX, LCD_Opts.currentY);
		} else if (*str == '\r') {
			LCD_CursorSet(0, LCD_Opts.currentY);
		} 
		else {
			LCD_Data(*str);
			LCD_Opts.currentX++;
		}
		str++;
	}
}

void LCD_DisplayOn(void) {
	LCD_Opts.DisplayControl |= LCD_DISPLAYON;
	LCD_Cmd(LCD_DISPLAYCONTROL | LCD_Opts.DisplayControl);
}

void LCD_DisplayOff(void) {
	LCD_Opts.DisplayControl &= ~LCD_DISPLAYON;
	LCD_Cmd(LCD_DISPLAYCONTROL | LCD_Opts.DisplayControl);
}

void LCD_BlinkOn(void) {
	LCD_Opts.DisplayControl |= LCD_BLINKON;
	LCD_Cmd(LCD_DISPLAYCONTROL | LCD_Opts.DisplayControl);
}

void LCD_BlinkOff(void) {
	LCD_Opts.DisplayControl &= ~LCD_BLINKON;
	LCD_Cmd(LCD_DISPLAYCONTROL | LCD_Opts.DisplayControl);
}

void LCD_CursorOn(void) {
	LCD_Opts.DisplayControl |= LCD_CURSORON;
	LCD_Cmd(LCD_DISPLAYCONTROL | LCD_Opts.DisplayControl);
}

void LCD_CursorOff(void) {
	LCD_Opts.DisplayControl &= ~LCD_CURSORON;
	LCD_Cmd(LCD_DISPLAYCONTROL | LCD_Opts.DisplayControl);
}

void LCD_ScrollLeft(void) {
	LCD_Cmd(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void LCD_ScrollRight(void) {
	LCD_Cmd(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void LCD_CreateChar(uint8_t location, uint8_t *data) {
	uint8_t i;
	/* We have 8 locations available for custom characters */
	location &= 0x07;
	LCD_Cmd(LCD_SETCGRAMADDR | (location << 3));
	
	for (i = 0; i < 8; i++) {
		LCD_Data(data[i]);
	}
}

void LCD_PutCustom(uint8_t x, uint8_t y, uint8_t location) {
	LCD_CursorSet(x, y);
	LCD_Data(location);
}

/* Private functions */
static void LCD_Cmd(uint8_t cmd) {
	/* Command mode */
	LCD_RS_LOW;
	
	/* High nibble */
	LCD_Cmd4bit(cmd >> 4);
	/* Low nibble */
	LCD_Cmd4bit(cmd & 0x0F);
}

static void LCD_Data(uint8_t data) {
	/* Data mode */
	LCD_RS_HIGH;
	
	/* High nibble */
	LCD_Cmd4bit(data >> 4);
	/* Low nibble */
	LCD_Cmd4bit(data & 0x0F);
}

static void LCD_Cmd4bit(uint8_t cmd) {
	/* Set output port */
	GPIO_SetPinValue(LCD_D7_PORT, LCD_D7_PIN, (cmd & 0x08));
	GPIO_SetPinValue(LCD_D6_PORT, LCD_D6_PIN, (cmd & 0x04));
	GPIO_SetPinValue(LCD_D5_PORT, LCD_D5_PIN, (cmd & 0x02));
	GPIO_SetPinValue(LCD_D4_PORT, LCD_D4_PIN, (cmd & 0x01));
	LCD_E_BLINK;
}

void LCD_CursorSet(uint8_t col, uint8_t row) {
	uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
	
	/* Go to beginning */
	if (row >= LCD_Opts.Rows) {
		row = 0;
	}
	
	/* Set current column and row */
	LCD_Opts.currentX = col;
	LCD_Opts.currentY = row;
	
	/* Set location address */
	LCD_Cmd(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void LCD_InitPins(void) {
	/* Init all pins */
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	GPIO_InitStruct.Pin = LCD_RS_PIN|LCD_E_PIN|LCD_D6_PIN|LCD_D7_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = LCD_D4_PIN|LCD_D5_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	/* Set pins low */
	GPIO_SetPinLow(LCD_RS_PORT, LCD_RS_PIN);
	GPIO_SetPinLow(LCD_E_PORT, LCD_E_PIN);
	GPIO_SetPinLow(LCD_D4_PORT, LCD_D4_PIN);
	GPIO_SetPinLow(LCD_D5_PORT, LCD_D5_PIN);
	GPIO_SetPinLow(LCD_D6_PORT, LCD_D6_PIN);
	GPIO_SetPinLow(LCD_D7_PORT, LCD_D7_PIN);
}

