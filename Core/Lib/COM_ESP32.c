#include "main.h"
#include "Header.h"
#include <string.h>

#define MAX_ID_CHANNEL 8
#define MAX_CHANNEL_PARAM 2

uint8_t PACKET_DATA[5] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; //Header + Mode + dataLowByte + dataHighByte + Footer
uint8_t PACKET_DATA_RECEIVE[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t RECEIVE_DATA[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
bool sensingMode;

//void addFunction(){
//	if(selectedSensingMode == 1){
//		sensingMode = 0;
//	}
//	else if(selectedSensingMode == 2){
//		sensingMode = 1;
//	}
//}

//unsigned char packetBuffer[18];

//void send_data_pack(){
//	packetBuffer[0] = 0xFF;
//	memcpy(&packetBuffer[1], dataSeg, 16);
//	pakcetBu
//}

void sendPacket(){
	uint8_t header = 0xFF;
	uint8_t footer = 0xFE;
	uint8_t ACK_DATA = 0x00;
	
	PACKET_DATA[0] = header;
	PACKET_DATA[1] = sensingMode;
	for(int checkingData = 0; checkingData < 16; checkingData++){
		if(checkingData < 8){
			PACKET_DATA[2] |= (dataSeg[checkingData] & 1) << checkingData;
		}
		else{
			PACKET_DATA[3] |= (dataSeg[checkingData] & 1) << (checkingData-8);
		}
	}
	PACKET_DATA[4] = footer;
	
	unsigned int panjangData = sizeof(PACKET_DATA);
	HAL_UART_Transmit(&huart1, (uint8_t*)PACKET_DATA, panjangData, 50);
	//HAL_UART_Receive(&huart1, (uint8_t*)ACK_DATA, sizeof(ACK_DATA), 50);
}

void receivePacket(){
	uint8_t header = 0xFF;
	uint8_t footer = 0xFE;
	
	if(PACKET_DATA_RECEIVE > 0){
		
	}
	if(PACKET_DATA_RECEIVE[0] != header || PACKET_DATA_RECEIVE[4] != header){
		//INVALID DATA
	}
	else{
		for(int i = 1; i < 2; i++){
			RECEIVE_DATA[i] = PACKET_DATA_RECEIVE[i];
		}
	}
	volatile int receiveDataLength = sizeof(PACKET_DATA_RECEIVE); 
	HAL_UART_Receive(&huart1, (uint8_t*)PACKET_DATA_RECEIVE, receiveDataLength, 50);
//	HAL_UART_Receive(*huart1, 
}