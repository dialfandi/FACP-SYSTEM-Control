#include "stm32f4xx_hal.h"
#include "stdbool.h"
#ifndef _Header_
#define _Header_

/*Variabel Global*/
#ifndef Global_Variable
extern uint32_t adcBuffer[16];
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart6;

/* GUI DATA	*/
extern unsigned int timerCount;
//extern int count; 
extern bool flagSucces;
extern bool flag;
extern int selectedSensingMode;
extern unsigned int valueSetInterval;
extern uint8_t hour;
extern uint8_t minute;
extern uint8_t second;
extern uint8_t day;
extern uint8_t month;
extern uint8_t year;
extern bool flagSensorActive[17];
extern char temp1[40],temp2[40],temp2[40],temp3[40],temp4[40],temp5[40],temp6[40],temp7[40],
	temp8[40],temp9[40],temp10[40],temp11[40],temp12[40],temp13[40],temp14[40],temp15[40],temp16[40];
/* SENSOR GLOBAL VARIABLE */
extern float currentSegment[16];
extern uint8_t dataSeg[16];
/* COMMUNICATION GLOBAL VARIABLE */
extern char tx[128];
extern bool flagRx;
extern char dateTime[128];
extern char dataF1[128];

extern int flag_send_data;
///*TIMER DATA PACKAGE*/
//static uint16_t time_c = 0;
//bool tx_busy = 0;
//static int MAX_DATA_COUNT = 8;
////static uint8_t s_data[3];
//static uint8_t s_data1[8] = {1,1,1,1,0,0,0,1};
//static uint8_t s_data2[8] = {0,1,0,0,0,1,1,1};

//uint8_t data_packet[5]={0};
//uint8_t header = 255;
//uint8_t footer = 254;
//extern char buffer[25];

//DISPLAY-SIZE
#endif

/* Button Initialization */
//GPIOD GPIO_PIN_0
#ifndef BUTTON
#define BUTTON_TEST_PORT			GPIOD 			//BT9
#define	BUTTON_TEST_PIN				GPIO_PIN_0

#define BUTTON_MUTE_PORT			GPIOD//GPIOB //GPIOD				//BT1
#define BUTTON_MUTE_PIN				GPIO_PIN_7 //GPIO_PIN_3 //GPIO_PIN_7

#define BUTTON_RESET_PORT			GPIOC //GPIOB				//BT2
#define BUTTON_RESET_PIN			GPIO_PIN_9//GPIO_PIN_3

#define BUTTON_SILENT_PORT		GPIOD				//BT8
#define BUTTON_SILENT_PIN			GPIO_PIN_2

#define BUTTON_UP_PORT				GPIOD				
#define BUTTON_UP_PIN					GPIO_PIN_6	//BT4

#define BUTTON_DOWN_PORT			GPIOD
#define BUTTON_DOWN_PIN				GPIO_PIN_4	//BT6

#define BUTTON_LEFT_PORT			GPIOD
#define BUTTON_LEFT_PIN				GPIO_PIN_1	//BT7

#define BUTTON_RIGHT_PORT			GPIOD
#define BUTTON_RIGHT_PIN			GPIO_PIN_5	//BT3

#define BUTTON_OK_PORT				GPIOD
#define BUTTON_OK_PIN					GPIO_PIN_3	//BT5

#define BUTTON_UNUSE_PORT			GPIOD //GPIOB //GPIOC
#define BUTTON_UNUSE_PIN			GPIO_PIN_7 //GPIO_PIN_3 //GPIO_PIN_3//GPIO_PIN_9	//BT10
#endif

#define BUTTON_PROG_PORT			GPIOB
#define BUTTON_PROG_PIN				GPIO_PIN_5	//BT0

#define BUTTON_High(GPIOx, GPIO_Pin)		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
#define BUTTON_Low(GPIOx, GPIO_Pin)			HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_LOW);
#define BUTTON_Read(GPIOx, GPIO_Pin)		HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);

#define HIGH	GPIO_PIN_SET 		
#define LOW		GPIO_PIN_RESET	
/* GUI */
extern void checkButton();
extern int buttonPress(GPIO_TypeDef *port, uint16_t pin, int delay);
extern void interface(void);
int menuSensingMode(void);
int menuScanSensor(void);
int menuSetThreshold(void);
int menuSetNameZone(void);
int menuSetDateTime(void);
int selectMenu(void);
/* IO */
extern void buzzerOn(int delay);
extern void buzzerOff(int delay);
extern void relayOn(int number);
extern void relayOff(int number);
extern void limitOn(int number);
extern void limitOff(int number);
extern void buzzerBlink(int delay);
/* SENSOR */
extern void getSensor(void);
extern int scanSensor(void);
extern void modeSingleWire(void);
extern void modeCrossWire(void);
extern void checkSortAndOpenCircuit(void);
extern void checkOverCurrentSensor(void);
extern void resetLimitSensor(void);
void checkSupply(void);
/* COMMUNICATION */
extern void parsingDataF1(void);
extern void sendDateTime(void);
extern void sendDataSegment(void);
extern void sendDataSegment2(void);
extern void sendDataSegment3(void);

extern void sendPacket(void);
extern void sendDataPacket(void);

extern unsigned char s_dat[16];

extern unsigned char data_packet[19];
extern unsigned char data_length;
extern uint8_t header;
extern uint8_t footer;
extern uint16_t time_c;
extern bool tx_busy;
extern int MAX_DATA_COUNT;

extern volatile uint8_t sensor_ready;
#endif












