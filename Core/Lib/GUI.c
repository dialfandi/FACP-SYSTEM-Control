#include "stm32f4xx_hal.h"
#include "Header.h"
#include "stdbool.h"
#include "LCD_Lib.h"
#include "DWT_Delay.h"
#include "stdio.h"
#include "string.h"
#include "main.h"
/* Initialization */
/* Function */
int buttonPress(GPIO_TypeDef *port, uint16_t pin, int delay);
void testFunction(void);
void silentFunction(void);
void muteFunction(void);
void resetFunction(void);
void zone(int zoneIndex, char temp[]);
void namezone(void);
void checkButton();

int menuSensingMode(void);
int menuScanSensor(void);
int menuSetThreshold(void);
int menuSetNameZone(void);
int selectMenu(void);
int menuSetDateTime(void);
void inMaintananceFunction(void);
int dateTimeSet(int timeMode);
/* Variable */
char buff[40];
bool lastb = 0;
bool flagSensorActive[17] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};
int charSize = 0;
int charIndex = 0;
unsigned int secdown = 60;
int count = 0;
int cx = 0;
int cy = 0;
int chx = 0;
int selectedSensingMode;
unsigned int valueSetInterval = 0;
bool flagSucces = false;
bool flag = 1;

int test = 0;
int countOut = 0;
bool toggleT = 0;
bool toggleM = 0;

unsigned int time;

int countBack = 0;
int countLeft = 0;
//> Temporary Variable per Zone
char temp[16][40];
char zoneUse[16];
char temp1[40],temp2[40],temp2[40],temp3[40],temp4[40],temp5[40],temp6[40],temp7[40],
	temp8[40],temp9[40],temp10[40],temp11[40],temp12[40],temp13[40],temp14[40],temp15[40],temp16[40];

char tempAlpha[27];
char alphabet[] = { ' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	
uint8_t hour,minute,second,day,month,year;
	
	/*char zone[] = {"ZONE1 : ", "ZONE2: ", "ZONE3: ", "ZONE4: ", "ZONE5: ", "ZONE6: ", 
		"ZONE7: ", "ZONE8: ", "ZONE9: ", "ZONE10: ", "ZONE11: ", "ZONE12: ", "ZONE13: ", "ZONE14: ",
		"ZONE15: ", "ZONE16: "};*/
char* ptrAlpha;
char* ptrZone;
//EEPROM
	//HAL_DATA_EEPROMEx_Program();

//Set Display Size
	
//Eliminate Debounce//

int buttonPress(GPIO_TypeDef *port, uint16_t pin, int delay){
	//HAL_I2C_Mem_Write();
	bool button = BUTTON_Read(port, pin);
	if(!button){
		DWT_Delayms(delay);
		if(!button){
			//LCD_Putsxy(0,0,"Stable Key");
			return 0;
		}
		else if(button){
			return 1;
		}
		//while(!button);
	}
}


void interface(void){
	testFunction();
	silentFunction();
	muteFunction();
	inMaintananceFunction();
	//resetFunction();
}
void inMaintananceFunction(void){

	if(!buttonPress(BUTTON_PROG_PORT, BUTTON_PROG_PIN, 500)){
			LCD_Clear();
		while(1){
//			LCD_Clear();
			LCD_Putsxy(0,0, "TROUBLE 3 MAINTENANCE");
//			LCD_Putsxy(0, 1, dateTime);
//			DWT_Delayms(1000);
			if(!buttonPress(BUTTON_RESET_PORT, BUTTON_RESET_PIN, 500)){
				LCD_Clear();
				break;
			}
		}
	}
}
//void testFunction(void) { // DONE
//    // Cek apakah tombol TEST ditekan dengan debounce 500ms
//    if (!buttonPress(BUTTON_TEST_PORT, BUTTON_TEST_PIN, 500)) {
//        LCD_Clear(); // Bersihkan LCD saat masuk test function

//        // Tampilkan pesan TEST FUNCTION sekali saja
//        LCD_Putsxy(0, 0, "TEST FUNCTION!");

//        // Nyalakan semua relay dan buzzer
//        relayOn(0xFFFF);  // Nyalakan semua relay
//        buzzerOn(500);   // Bunyikan buzzer 1 kHz

//        // Loop sampai tombol RESET ditekan
//        while (1) {
//            // Jika tombol RESET ditekan, keluar dari test function
//            if (!buttonPress(BUTTON_RESET_PORT, BUTTON_RESET_PIN, 500)) {
//                // Proses reset
//                LCD_Clear();
//                LCD_Putsxy(0, 0, "RESET FUNCTION");
//                
//                buzzerOff(0);  // Matikan buzzer
//                relayOff(18);  // Matikan semua relay (18 relay misalnya)

//                //DWT_Delayms(1000); // Tunggu sebentar untuk tampilkan pesan reset

//                LCD_Clear(); // Bersihkan layar
//                break; // Keluar dari loop test function
//            }
//            DWT_Delayms(50); // Hindari loop terlalu cepat, hemat CPU
//        }
//    }
//}

void testFunction(void){ //DONE
	if(!buttonPress(BUTTON_TEST_PORT, BUTTON_TEST_PIN, 500)){
		LCD_Clear();
		while(1){
			// bool alarm = 1;
			LCD_Putsxy(0,0, "           TEST FUNCTION!");
			/*NYALAKKAN LAMPU ALARM*/
			relayOn(0xFFFF);
			buzzerOn(1);
			//buzzerOff(1000);
			if(!buttonPress(BUTTON_RESET_PORT, BUTTON_RESET_PIN, 500)){
				LCD_Clear();
				DWT_Delayms(100);
				relayOff(18);
				LCD_Putsxy(0,0, "RESET FUNCTION");
				buzzerOff(0);
				LCD_Clear();
				break;
			}
		}
	}
}

void silentFunction(void){
	//while(sensor == 1){
	if(flagSensorActive[0] || flagSensorActive[1] || flagSensorActive[2] || flagSensorActive[3] || flagSensorActive[4] || flagSensorActive[5] || flagSensorActive[6] || flagSensorActive[7] || flagSensorActive[8] || flagSensorActive[9] || flagSensorActive[10] || flagSensorActive[11] || flagSensorActive[12] || flagSensorActive[13] || flagSensorActive[14] || flagSensorActive[15] || flagSensorActive[16]){
		if(!buttonPress(BUTTON_SILENT_PORT, BUTTON_SILENT_PIN, 500)){
			LCD_Clear();
			LCD_BlinkOff();
			LCD_Putsxy(0,0, "Buzzer Off");
			relayOff(17);				// NONAKTIF ALL RELAY
			buzzerOff(100); 		// NONAKTIFKAN BUZZER
			DWT_Delayms(60000); // SILENT BUZZER 1 MINUTE 
			LCD_BlinkOff();
			LCD_Clear();
			// CHECK RELAY YANG SEBELUMNYA AKTIF => UNTUK AKTIF LAGI
			for(int i = 0; i <=16; i++){
				if(flagSensorActive[i]){
					relayOn(i);
				}
			}
		}
	}
}

void resetFunction(void){
	//buttonPress(BUTTON_RESET_PORT, BUTTON_RESET_PIN);
	/*
	if(sensor == 0 && !buttonPress(BUTTON_RESET_PORT, BUTTON_RESET_PIN, 500)){
		LCD_Clear();
		LCD_BlinkOff();
		LCD_Putsxy(0,0,"           RESET SYSTEM");
		DWT_Delayms(2000);
		LCD_BlinkOff();
		LCD_Putsxy(0,0,"          RESTART SYSTEM");
		DWT_Delayms(5000);
		//Off all Alarm
		NVIC_SystemReset();
	}
	else if(sensor == 1 && !buttonPress(BUTTON_RESET_PORT, BUTTON_RESET_PIN, 500)){
		LCD_Clear();
		LCD_Putsxy(0,0, "       SYSTEM CANNOT RESET");
		//Cannot off Alarm 
	}
	*/
	
}

void muteFunction(void){
	if(flagSensorActive[0] || flagSensorActive[1] || flagSensorActive[2] || flagSensorActive[3] || flagSensorActive[4] || flagSensorActive[5] || flagSensorActive[6] || flagSensorActive[7] || flagSensorActive[8] || flagSensorActive[9] || flagSensorActive[10] || flagSensorActive[11] || flagSensorActive[12] || flagSensorActive[13] || flagSensorActive[14] || flagSensorActive[15] || flagSensorActive[16]){
		if(!buttonPress(BUTTON_MUTE_PORT, BUTTON_MUTE_PIN, 500)){
			relayOff(17);
			buzzerOff(10);
			//HAL_GPIO_WritePin(GPIOA, BUZZER_Pin, GPIO_PIN_RESET);
			LCD_Clear();
			LCD_Putsxy(0,0, "MUTE");
			/* Buzzer OFF */
			while(1){/*Buzzer OFF*/
				HAL_GPIO_WritePin(GPIOA, BUZZER_Pin, GPIO_PIN_RESET);
				if(!buttonPress(BUTTON_RESET_PORT, BUTTON_RESET_PIN, 500)){
					LCD_Clear();
					break;
				}
			}
		}
	}
}
void troubleFunction(void){
	/*Jika Buttry Tidak Connect */
	LCD_Putsxy(0,0, "Battery Disconnect");
	
	/*Jika Power AC Loss*/
	LCD_Putsxy(1,0, "AC Power Loss");
	
	/*SIstem Disable*/
	/* Parameternya APAAA?? */
}
void zone(int zoneIndex, char temp[]){
	//int zoneNumber = zoneIndex;
	int couterrr = 0;
	char buffer[40];
	char* ptrAlpha;
	temp[0] = ' ';
	
	if(zoneIndex <= 9){
		cx = 8;
		chx = 8;
	}
	else if(zoneIndex >= 10){
		cx = 9;
		chx = 9;
	}
	//cx = 7;
	//chx = 7;
	
	while(1){
		sprintf(buffer, "ZONE %d:", zoneIndex);
		LCD_Putsxy(0,0,buffer);
		LCD_CursorSet(cx,0);
		LCD_BlinkOn();
		if(cx <= chx){cx = chx;}
		else if(cx >= 39){cx = 39;}
						
		if(!buttonPress(BUTTON_UP_PORT, BUTTON_UP_PIN, 500)){
			charIndex++;
			if(charIndex == charSize){
				charIndex = 0;
			}
			if(charIndex > 26){
				charIndex = 0;
			}
			ptrAlpha = &alphabet[charIndex];
			LCD_CursorSet(cx,0);
			//LCD_BlinkOn();
			LCD_Puts(1, ptrAlpha);
			DWT_Delayms(200);
		}
		else if(!buttonPress(BUTTON_DOWN_PORT, BUTTON_DOWN_PIN, 500)){
			charIndex--;
			if(charIndex < 0){
				charIndex = 26;
			}
			if(charIndex > 26){charIndex = 1;}
			else if(charIndex < 0){charIndex = 26;}
			
			ptrAlpha = &alphabet[charIndex];
			LCD_CursorSet(cx, 0);
			//LCD_BlinkOn();
			LCD_Puts(1, ptrAlpha);
			DWT_Delayms(200);
		}
					
		if(!buttonPress(BUTTON_OK_PORT, BUTTON_OK_PIN, 500)){
			couterrr++;
			temp[couterrr] = alphabet[charIndex];
			LCD_CursorSet(cx, 0);
			LCD_Puts(1, ptrAlpha);
			charIndex = 0;			
			cx++;
			DWT_Delayms(200);
		}
					
		if(!buttonPress(BUTTON_RIGHT_PORT, BUTTON_RIGHT_PIN, 500)){
			countBack++;
			if(countBack > 4){
				LCD_Clear();
				sprintf(buffer, "       SAVE NAME ZONE %d SUCCESS", zoneIndex);
				LCD_Putsxy(0,0, buffer);
				LCD_Putsxy(0,1, temp);
				DWT_Delayms(5000);
				countBack = 0;
				LCD_Clear();
				break;
			}
		}
							
		if(!buttonPress(BUTTON_LEFT_PORT, BUTTON_LEFT_PIN, 500)){
			countLeft++;
			if(countLeft > 4){
				countLeft = 0;
			break;
			}
		}
	}
}

void namezone(){

	//LCD_BlinkOn();
	if(count < 0){count = 15;}
	else if(count > 15){count = 0;}
	
	if(!buttonPress(BUTTON_UP_PORT, BUTTON_UP_PIN, 500)){
		count++;
	}
	else if(!buttonPress(BUTTON_DOWN_PORT, BUTTON_DOWN_PIN, 500)){
		count--;
	}
	
	else if(!buttonPress(BUTTON_OK_PORT, BUTTON_OK_PIN, 500)){
		LCD_Clear();
		switch(count){
			case 0:
				zone(1, temp1);
					//zoneTry(1, temp[1][40], 0);
			break;
			case 1:
				zone(2, temp2);
			break;
			case 2:
				zone(3, temp3);
			break;
			case 3:
				zone(4, temp4);
			break;
			case 4:
				zone(5, temp5);
			break;
			case 5:
				zone(6, temp6);
			break;
			case 6:
				zone(7, temp7);
			break;
			case 7:
				zone(8, temp8);
			break;
			case 8:
				zone(9, temp9);
			break;
			case 9:
				zone(10, temp10);;
			break;
			case 10:
				zone(11, temp11);
			break;
			case 11:
				zone(12, temp12);
			break;
			case 12:
				zone(13, temp13);
			break;
			case 13:
				zone(14, temp14);;
			break;
			case 14:
				zone(15, temp15);
			break;
			case 15:
				zone(16, temp16);
			break;

			default:
					LCD_Putsxy(0,0, "CASE LOOP AGAIN");
			break;		
		}
	}
	
	switch(count){
		case 0:
			LCD_Putsxy(0,0,"INPUT NAME IN ZONE 1? ");
		break;
		case 1:
			LCD_Putsxy(0,0,"INPUT NAME IN ZONE 2?");
		break;
		case 2:
			LCD_Putsxy(0,0,"INPUT NAME IN ZONE 3?");
		break;
		case 3:
			LCD_Putsxy(0,0,"INPUT NAME IN ZONE 4?");
		break;
		case 4:
			LCD_Putsxy(0,0,"INPUT NAME IN ZONE 5?");
		break;
		case 5:
			LCD_Putsxy(0,0,"INPUT NAME IN ZONE 6?");
		break;
		case 6:
			LCD_Putsxy(0,0,"INPUT NAME IN ZONE 7?");
		break;
		case 7:
			LCD_Putsxy(0,0,"INPUT NAME IN ZONE 8?");
		break;
		case 8:
			LCD_Putsxy(0,0,"INPUT NAME IN ZONE 9? ");
		break;
		case 9:
			LCD_Putsxy(0,0,"INPUT NAME IN ZONE 10?");
		break;
		case 10:
			LCD_Putsxy(0,0,"INPUT NAME IN ZONE 11?");
		break;
		case 11:
			LCD_Putsxy(0,0,"INPUT NAME IN ZONE 12?");
		break;
		case 12:
			LCD_Putsxy(0,0,"INPUT NAME IN ZONE 13?");
		break;
		case 13:
			LCD_Putsxy(0,0,"INPUT NAME IN ZONE 14?");
		break;
		case 14:
			LCD_Putsxy(0,0,"INPUT NAME IN ZONE 15?");
		break;
		case 15:
			LCD_Putsxy(0,0,"INPUT NAME IN ZONE 16?");
		break;
	}
}
int menuSetNameZone(void){
	bool flagSetName = false;
	int count = 0;
	LCD_Clear();
	while(1){
		namezone();
		if(!buttonPress(BUTTON_LEFT_PORT, BUTTON_LEFT_PIN, 500)){
// check the used zone
			for(int i = 0; i < 16; i++){
				if(strlen(i == 0 ? temp1 : i == 1 ? temp2 : i == 2 ? temp3 : i == 3 ? temp4 : i == 4 ? temp5 : i == 5 ? temp6 : i == 6 ? temp7 : i == 7 ? temp8 : i == 8 ? temp9 : i == 9 ? temp10 : i == 10 ? temp11 : i == 11 ? temp12 : i == 12 ? temp13 : i == 13 ? temp14 : i == 14 ? temp15 : temp16) > 1)
					{
						count++;
						// zoneUse[i] = i + 1;
						zoneUse[i] = 1;					// 1 => Used
					}else{
						zoneUse[i] = 0; 				// 0 => Not Used
					}
			}
			
			// validate the used zone
			for(int i =0; i<16; i++){
				if(zoneUse[i] == 0){
						limitOn(i);		
				}
			}
//					if(strlen(temp1) > 1) {
//						count++;
//						zoneUse[0] = 1;
//					}
//					if(strlen(temp2) > 1) {
//						count++;
//						zoneUse[1] = 2;
//					}
				
				if(count != 0){
					flagSetName = true;
				}else{
					flagSetName = false;
				}
			break;
		}			
	}
	return flagSetName;
}
int menuSensingMode(void){
	bool sensingSelected = false;
	int count = 0;
		LCD_Clear();
		LCD_Putsxy(0,0, "=> MENU SENSING MODE <=");
		while(1){
		if(!buttonPress(BUTTON_DOWN_PORT, BUTTON_DOWN_PIN, 500)){ 			// BUTTON DOWN
			count++;
			if(count > 2) count = 2;
		}else if(!buttonPress(BUTTON_UP_PORT, BUTTON_UP_PIN, 500)){		// BUTTON UP
			count--;
			if(count <= 0) count = 1;
		}else if(!buttonPress(BUTTON_OK_PORT, BUTTON_OK_PIN, 500)){		// BUTTON OK
			if(count == 1){
				LCD_Clear();
				sensingSelected = true;
				selectedSensingMode = 1;	// SELECT MODE SINGLE WIRE
				break;
			}else if(count == 2){
				LCD_Clear();
				sensingSelected = true;
				selectedSensingMode = 2; 	// SELECT MODE CROSS WIRE
				break;
			}else{
				LCD_Clear();
				sensingSelected = false;
				selectedSensingMode = 0;	// BELUM DIPILIH
				break;
			}
		}else if(!buttonPress(BUTTON_LEFT_PORT, BUTTON_LEFT_PIN, 500)){	// BUTTON BACK
			LCD_Clear();
			sensingSelected = false;	
			selectedSensingMode = 0;		// BELUM DIPILIH
			break;
		}
		
			if(count == 1){
				LCD_Putsxy(0,1, "MODE SINGLE WIRE          ");
			}else if(count == 2){
				LCD_Putsxy(0,1, "MODE CROSS WIRE           ");
			}else{
				LCD_Putsxy(0,1, "USE UP&DOWN KEYS TO SELECT");
			}

		}
	return sensingSelected;
}

int menuScanSensor(void){
	bool flagScanSensor = false;
//	char bufferr[50];
	LCD_Clear();
	while(1){
		LCD_Putsxy(0,0, "==========> MENU SCAN SENSOR <==========");
		LCD_Putsxy(0,1,"Press OK TO SCAN or BACK TO CANCEL");
		if(!buttonPress(BUTTON_OK_PORT, BUTTON_OK_PIN, 500)){
			LCD_Clear();
			LCD_Putsxy(0,0, "Sensor scan is processed");
			LCD_Putsxy(0,1, "Please wait...");
			DWT_Delayms(2000);
			LCD_Clear();
			flagScanSensor = scanSensor();
			if(flagScanSensor == true){		// APABILA SCAN SUKSES
				LCD_Clear();
				break;
			}
		}else if(!buttonPress(BUTTON_LEFT_PORT, BUTTON_LEFT_PIN, 500)){
			LCD_Clear();
			flagScanSensor = false;
			break;
		}
	}
	return flagScanSensor;
}
int dateTimeSet(int timeMode){
	char bufferr[30];
	int value = 0;
	if(timeMode == 6)value = 2000;
	LCD_Clear();
	LCD_Putsxy(0,0,"MENU SET DATE TIME");
	while(1){
		if(!buttonPress(BUTTON_UP_PORT, BUTTON_UP_PIN, 100)){			// DOWN => INCREMENT
			value++;
			LCD_Clear();
			LCD_Putsxy(0,0,"MENU SET DATE TIME");
			if(timeMode == 1){if(value >=24) {value = 24;}
			}else if(timeMode == 2){if(value >=60) {value = 60;}
			}else if(timeMode == 3){if(value >=60) {value = 60;}
			}else if(timeMode == 4){if(value>=31) {value = 31;}
			}else if(timeMode == 5){if(value>=12) {value = 12;}
			}else if(timeMode == 6){if(value>=2100) {value = 2100;}}
		}else if(!buttonPress(BUTTON_DOWN_PORT, BUTTON_DOWN_PIN, 100)){		// UP		=> DECREMENT
			value--;
			LCD_Clear();
			LCD_Putsxy(0,0,"MENU SET DATE TIME");
			if(timeMode == 1){if(value <= 0) {value = 0;}
			}else if(timeMode == 2){if(value <= 0) {value = 0;}
			}else if(timeMode == 3){if(value <= 0) {value = 0;}
			}else if(timeMode == 4){if(value <= 0) {value = 0;}
			}else if(timeMode == 5){if(value <= 0) {value = 0;}
			}else if(timeMode == 6){if(value <= 2000){value = 2000;}}
		}else if(!buttonPress(BUTTON_LEFT_PORT, BUTTON_LEFT_PIN, 500)){		// CANCEL
			value = 0;
			//valueSetInterval = 0;
			break;
		}else if(!buttonPress(BUTTON_OK_PORT, BUTTON_OK_PIN, 500)){				// OK
			if(value != 0){
				//valueSetInterval = value;
				LCD_Clear();
				if(timeMode == 1){
					sprintf(bufferr, "Set Hour value %d saved", value);
				}else if(timeMode == 2){
					sprintf(bufferr, "Set Minute value %d saved", value);
				}else if(timeMode == 3){
					sprintf(bufferr, "Set Second value %d saved", value);
				}else if(timeMode == 4){
					sprintf(bufferr, "Set Day value %d saved", value);
				}else if(timeMode == 5){
					sprintf(bufferr, "Set Month value %d saved", value);
				}else if(timeMode == 6){
					sprintf(bufferr, "Set Year value %d saved", value);
				}
				LCD_Putsxy(0,1,bufferr);
				DWT_Delayms(2000);
				LCD_Clear();
				break;
			}else{
				LCD_Clear();
				if(timeMode == 1){
					LCD_Putsxy(0,0,"Save Hour value failed");
					LCD_Putsxy(0,1,"Because Hour value is 0");
				}else if(timeMode == 2){
					LCD_Putsxy(0,0,"Save Minute value failed");
					LCD_Putsxy(0,1,"Because Minute value is 0");
				}else if(timeMode == 3){
					LCD_Putsxy(0,0,"Save Second value failed");
					LCD_Putsxy(0,1,"Because Second value is 0");
				}else if(timeMode == 4){
					LCD_Putsxy(0,0,"Save Day value failed");
					LCD_Putsxy(0,1,"Because Day value is 0");
				}else if(timeMode == 5){
					LCD_Putsxy(0,0,"Save Month value failed");
					LCD_Putsxy(0,1,"Because Month value is 0");
				}else if(timeMode == 6){
					LCD_Putsxy(0,0,"Save year value failed");
					LCD_Putsxy(0,1,"Because year value is 0");
				}
				DWT_Delayms(2000);
				LCD_Clear();
			}
		}
		if(timeMode == 1){
			  sprintf(bufferr, "Hour : %d", value);
		}else if(timeMode == 2){
				sprintf(bufferr, "Minute : %d", value);
		}else if(timeMode == 3){
				sprintf(bufferr, "Second : %d", value);
		}else if(timeMode == 4){
			  sprintf(bufferr, "Day : %d", value);	
		}else if(timeMode == 5) {
		    sprintf(bufferr, "Month : %d", value);
		}else if(timeMode == 6) {
		   sprintf(bufferr, "Year : %d", value);	
		}
		LCD_Putsxy(0,1,bufferr);
	}
	
	return value;
}
int menuSetThreshold(void){
	char bufferr[30];
	int value = 0;
	bool flagSetThreshold = false;
	LCD_Clear();
	LCD_Putsxy(0,0,"MENU SET THRESHOLD VALUE");
	while(1){
		if(!buttonPress(BUTTON_UP_PORT, BUTTON_UP_PIN, 100)){		// INCREMENT
			value++;
			LCD_Clear();
			LCD_Putsxy(0,0,"MENU SET THRESHOLD VALUE");
		}else if(!buttonPress(BUTTON_DOWN_PORT, BUTTON_DOWN_PIN, 100)){	// DECREMENT
			value--;
			LCD_Clear();
			LCD_Putsxy(0,0,"MENU SET THRESHOLD VALUE");
			if(value <=0){
				value = 0;
			}
		}else if(!buttonPress(BUTTON_LEFT_PORT, BUTTON_LEFT_PIN, 500)){	// CANCEL
			flagSetThreshold = false;
			valueSetInterval = 0;
			break;
		}else if(!buttonPress(BUTTON_OK_PORT, BUTTON_OK_PIN, 500)){		// OK ATAU SAVE
			if(value != 0){
				flagSetThreshold = true;
				valueSetInterval = value;
				LCD_Clear();
				sprintf(bufferr, "Threshold value %d saved", value);
				LCD_Putsxy(0,1,bufferr);
				DWT_Delayms(2000);
				LCD_Clear();
				break;
			}else{
				flagSetThreshold = false;
				LCD_Clear();
				LCD_Putsxy(0,0,"Save threshold value failed");
				LCD_Putsxy(0,1,"Because threshold value is 0");
				DWT_Delayms(2000);
				LCD_Clear();
			}
		}
		sprintf(bufferr, "VALUE : %d", value);
		LCD_Putsxy(0,1,bufferr);
	}
	return flagSetThreshold;
}
int menuSetDateTime(void){
	bool flagDateTime = false;
	uint8_t plus = 0;
	while(1){
		plus++;
		if(plus == 1){				// SET HOUR
			hour = dateTimeSet(1);
			if(hour <= 0) break;
		}else if(plus == 2){	// SET MINUTE
			minute = dateTimeSet(2);
			if(minute <= 0) plus = 0;
		}else if(plus == 3){	// SET SECOND
			second = dateTimeSet(3);
			if(second <= 0) plus = 1;
		}else if(plus == 4){	// SET DAY
		  day = dateTimeSet(4);
			if(day <= 0) plus = 2;
		}else if(plus == 5){	// SET MONTH
			month = dateTimeSet(5);
			if(month <= 0) plus = 3;
		}else if(plus == 6){	// SET YEAR
			year = dateTimeSet(6);
			if(year <= 0) plus = 4;
		}
		
		// CHECK APABILA SEMUA TERISI
		if(hour > 0 && minute > 0 && second > 0 && day > 0 && month > 0 && year > 0){
			flagDateTime = true;
			break;
		}			
	}
	return flagDateTime;
}
void RunningSystem(void){
	LCD_Clear();
	LCD_Putsxy(0,0, "SYSTEM RUN");
}
int selectMenu(void){
	bool flagSystemSIP = false;
	int count = 0;
//	int increm = 0;
	bool flagSetMenu[5] = {false, false, false, false, false};
	LCD_Clear();
	LCD_Putsxy(0,0,"MENU OPTIONS");
	LCD_Putsxy(0,1,"PRESS UP & DOWN TO CHOOSE");
	DWT_Delayms(2000);
	LCD_Clear();
	while(1){
			interface();
			LCD_Putsxy(0,0,"============> MENU OPTIONS <============");
		if(!buttonPress(BUTTON_UP_PORT, BUTTON_UP_PIN, 500)){
			count--;
			if(count < 0) count = 0;
		}else if(!buttonPress(BUTTON_DOWN_PORT, BUTTON_DOWN_PIN, 500)){
			count++;
			if(count > 3) count = 4;
		}else if(!buttonPress(BUTTON_OK_PORT, BUTTON_OK_PIN, 500)){
			if(count == 0){
				 flagSetMenu[0] = menuSensingMode();
			}else if(count == 1){
				 flagSetMenu[1] =  menuSetNameZone();
			}else if(count == 2){
				flagSetMenu[2] = menuScanSensor();
			}else if(count == 3){
				flagSetMenu[3] = menuSetThreshold();
			}else if(count == 4){
				flagSetMenu[4] = menuSetDateTime();
			}
		}
		
		if(count == 0){
			LCD_Putsxy(0,1, "SENSING MODE MENU");
		}else if(count == 1){
			LCD_Putsxy(0,1, "ZONE NAME MENU   ");
		}else if(count == 2){
			LCD_Putsxy(0,1, "SCAN SENSOR MENU ");
		}else if(count == 3){
			LCD_Putsxy(0,1, "SET INTERVAL MENU");
		}else if(count == 4){
			LCD_Putsxy(0,1, "SET DateTime MENU");
		}
		
		// CHECK APABILA SYSTEM TERPENUHI
//		if((flagSetMenu[0] == true) && (flagSetMenu[1] == true) && (flagSetMenu[2] == true) && (flagSetMenu[3] == true) && (flagSetMenu[4] == true)){
		if((flagSetMenu[0] == true) && (flagSetMenu[1] == true) && (flagSetMenu[2] == true) && (flagSetMenu[3] == true)){
		//if(flagSetMenu[0] == true){	
			LCD_Clear();
			sprintf(buff, " SETTING SUCCESS => %d || %d || %d || %d || %d", flagSetMenu[0],flagSetMenu[1],flagSetMenu[2],flagSetMenu[3], flagSetMenu[4]);
			LCD_Putsxy(0,0, buff);
			flagSystemSIP = true;
			DWT_Delayms(2000);
			break;
		}			
		
	}
	return flagSystemSIP;
}

void checkButton(){
//	if(!buttonPress(BUTTON_TEST_PORT, BUTTON_TEST_PIN, 100)){
//		LCD_Clear();
//		LCD_Putsxy(0,0,"TEST  ");		
//	}
//	if(!buttonPress(BUTTON_MUTE_PORT, BUTTON_MUTE_PIN, 100)){
//		LCD_Clear();
//		LCD_Putsxy(0,0,"MUTE  ");		
//	}
//	if(!buttonPress(BUTTON_RESET_PORT, BUTTON_RESET_PIN, 100)){
//		LCD_Clear();
//		LCD_Putsxy(0,0,"RESET ");		
//	}
//	if(!buttonPress(BUTTON_SILENT_PORT, BUTTON_SILENT_PIN, 100)){
//		LCD_Clear();
//		LCD_Putsxy(0,0,"SILENT");		
//	}
//	if(!buttonPress(BUTTON_UP_PORT, BUTTON_UP_PIN, 100)){
//		LCD_Clear();
//		LCD_Putsxy(0,0,"UP    ");		
//	}
//	if(!buttonPress(BUTTON_LEFT_PORT, BUTTON_LEFT_PIN, 100)){
//		LCD_Clear();
//		LCD_Putsxy(0,0,"LEFT  ");		
//	}
//	if(!buttonPress(BUTTON_RIGHT_PORT, BUTTON_RIGHT_PIN, 100)){
//		LCD_Clear();
//		LCD_Putsxy(0,0,"RIGHT ");		
//	}
//	if(!buttonPress(BUTTON_OK_PORT, BUTTON_OK_PIN, 100)){
//		LCD_Clear();
//		LCD_Putsxy(0,0,"OK    ");		
//	}
//	if(!buttonPress(BUTTON_UNUSE_PORT, BUTTON_UNUSE_PIN, 100)){
//		LCD_Clear();
//		LCD_Putsxy(0,0,"UNUSE ");		
//	}
//	if(!buttonPress(BUTTON_PROG_PORT, BUTTON_PROG_PIN, 100)){
//		LCD_Clear();
//		LCD_Putsxy(0,0,"PROG  ");		
//	}
	
	if(!buttonPress(BT_0_GPIO_Port, BT_0_Pin, 100)){
		LCD_Clear();
		LCD_Putsxy(0,0,"00");		//aman
	}
	if(!buttonPress(BT_1_GPIO_Port, BT_1_Pin, 100)){
		LCD_Clear();
		LCD_Putsxy(0,0,"01");		//aman
	}
	//if(!buttonPress(BT_2_GPIO_Port, BT_2_Pin, 100)){
	if(!buttonPress(BUTTON_MUTE_PORT, BUTTON_MUTE_PIN, 100)){
		LCD_Clear();
		LCD_Putsxy(0,0,"02");		
	}
	if(!buttonPress(BT_3_GPIO_Port, BT_3_Pin, 100)){
		LCD_Clear();
		LCD_Putsxy(0,0,"03");		//aman
	}
	if(!buttonPress(BT_4_GPIO_Port, BT_4_Pin, 100)){
		LCD_Clear();
		LCD_Putsxy(0,0,"04");		//aman
	}
	if(!buttonPress(BT_5_GPIO_Port, BT_5_Pin, 100)){
		LCD_Clear();
		LCD_Putsxy(0,0,"05");		//aman
	}
	if(!buttonPress(BT_6_GPIO_Port, BT_6_Pin, 100)){
		LCD_Clear();
		LCD_Putsxy(0,0,"06");		//aman
	}
	if(!buttonPress(BT_7_GPIO_Port, BT_7_Pin, 100)){
		LCD_Clear();
		LCD_Putsxy(0,0,"07");		//aman
	}
	if(!buttonPress(BT_8_GPIO_Port, BT_8_Pin, 100)){
		LCD_Clear();
		LCD_Putsxy(0,0,"08");		//aman
	}
	if(!buttonPress(BT_9_GPIO_Port, BT_9_Pin, 100)){
		LCD_Clear();
		LCD_Putsxy(0,0,"09");		//aman
	}
	if(!buttonPress(BT_10_GPIO_Port, BT_10_Pin, 100)){
		LCD_Clear();
		LCD_Putsxy(0,0,"10");		
	}
}