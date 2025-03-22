/*
================================================
================ INPUT OUTPUT ==================
================================================
*/
#include "stm32f4xx_hal.h"
#include "main.h"
#include "Header.h"
#include "dwt_delay.h"

void buzzerOn(int delay){
	HAL_GPIO_WritePin(GPIOA, BUZZER_Pin, GPIO_PIN_SET);
	DWT_Delayms(delay);
}
void buzzerOff(int delay){
	HAL_GPIO_WritePin(GPIOA, BUZZER_Pin, GPIO_PIN_RESET);
	DWT_Delayms(delay);
}
void buzzerBlink(int delay){
	HAL_GPIO_TogglePin(GPIOA, BUZZER_Pin);
	DWT_Delayms(delay);
}

void relayOn(int number){
		if(number == 0){
			HAL_GPIO_WritePin(RL_0_GPIO_Port, RL_0_Pin, HIGH);	
			flagSensorActive[0] = true;
		}
		else if(number == 1){
			HAL_GPIO_WritePin(RL_1_GPIO_Port, RL_1_Pin, HIGH);	
			flagSensorActive[1] = true;
		}
		else if(number == 2){
			HAL_GPIO_WritePin(RL_2_GPIO_Port, RL_2_Pin, HIGH);	
			flagSensorActive[2] = true;
		}
		else if(number == 3){
			HAL_GPIO_WritePin(RL_3_GPIO_Port, RL_3_Pin, HIGH);	
			flagSensorActive[3] = true;
		}
		else if(number == 4){
			HAL_GPIO_WritePin(RL_4_GPIO_Port, RL_4_Pin, HIGH);	
			flagSensorActive[4] = true;
		}
		else if(number == 5){
			HAL_GPIO_WritePin(RL_5_GPIO_Port, RL_5_Pin, HIGH);	
			flagSensorActive[5]= true;
		}
		else if(number == 6){
			HAL_GPIO_WritePin(RL_6_GPIO_Port, RL_6_Pin, HIGH);	
			flagSensorActive[6] = true;
		}
		else if(number == 7){
			HAL_GPIO_WritePin(RL_7_GPIO_Port, RL_7_Pin, HIGH);	
			flagSensorActive[7] = true;
		}
		else if(number == 8){
			HAL_GPIO_WritePin(RL_8_GPIO_Port, RL_8_Pin, HIGH);	
			flagSensorActive[8] = true;
		}
		else if(number == 9){
			HAL_GPIO_WritePin(RL_9_GPIO_Port, RL_9_Pin, HIGH);	
			flagSensorActive[9] = true;
		}
		else if(number == 10){
			HAL_GPIO_WritePin(RL_10_GPIO_Port, RL_10_Pin, HIGH);	
			flagSensorActive[10] = true;
		}
		else if(number == 11){
			HAL_GPIO_WritePin(RL_11_GPIO_Port, RL_11_Pin, HIGH);	
			flagSensorActive[11] = true;
		}
		else if(number == 12){
			HAL_GPIO_WritePin(RL_12_GPIO_Port, RL_12_Pin, HIGH);
			flagSensorActive[12] = true;			
		}
		else if(number == 13){
			HAL_GPIO_WritePin(RL_13_GPIO_Port, RL_13_Pin, HIGH);	
			flagSensorActive[13] = true;
		}
		else if(number == 14){
			HAL_GPIO_WritePin(RL_14_GPIO_Port, RL_14_Pin, HIGH);	
			flagSensorActive[14] = true;
		}
		else if(number == 15){
			HAL_GPIO_WritePin(RL_15_GPIO_Port, RL_15_Pin, HIGH);	
			flagSensorActive[15] = true;
		}
		else if(number == 16){
			HAL_GPIO_WritePin(RL_16_GPIO_Port, RL_16_Pin, HIGH);
			flagSensorActive[16]= true;
		}
		else{
			HAL_GPIO_WritePin(RL_0_GPIO_Port, RL_0_Pin, HIGH);
			HAL_GPIO_WritePin(RL_1_GPIO_Port, RL_1_Pin, HIGH);
			HAL_GPIO_WritePin(RL_2_GPIO_Port, RL_2_Pin, HIGH);
			HAL_GPIO_WritePin(RL_3_GPIO_Port, RL_3_Pin, HIGH);
			HAL_GPIO_WritePin(RL_4_GPIO_Port, RL_4_Pin, HIGH);
			HAL_GPIO_WritePin(RL_5_GPIO_Port, RL_5_Pin, HIGH);
			HAL_GPIO_WritePin(RL_6_GPIO_Port, RL_6_Pin, HIGH);
			HAL_GPIO_WritePin(RL_7_GPIO_Port, RL_7_Pin, HIGH);
			HAL_GPIO_WritePin(RL_8_GPIO_Port, RL_8_Pin, HIGH);
			HAL_GPIO_WritePin(RL_9_GPIO_Port, RL_9_Pin, HIGH);
			HAL_GPIO_WritePin(RL_10_GPIO_Port, RL_10_Pin, HIGH);
			HAL_GPIO_WritePin(RL_11_GPIO_Port, RL_11_Pin, HIGH);
			HAL_GPIO_WritePin(RL_12_GPIO_Port, RL_12_Pin, HIGH);
			HAL_GPIO_WritePin(RL_13_GPIO_Port, RL_13_Pin, HIGH);
			HAL_GPIO_WritePin(RL_14_GPIO_Port, RL_14_Pin, HIGH);
			HAL_GPIO_WritePin(RL_15_GPIO_Port, RL_15_Pin, HIGH);
			HAL_GPIO_WritePin(RL_16_GPIO_Port, RL_16_Pin, HIGH);
		}
}

void relayOff(int number){
		if(number == 0){
			HAL_GPIO_WritePin(RL_0_GPIO_Port, RL_0_Pin, LOW);	
			flagSensorActive[0] = false;
		}
		else if(number == 1){
			HAL_GPIO_WritePin(RL_1_GPIO_Port, RL_1_Pin, LOW);	
			flagSensorActive[1] = false;
		}
		else if(number == 2){
			HAL_GPIO_WritePin(RL_2_GPIO_Port, RL_2_Pin, LOW);	
			flagSensorActive[2] = false;
		}
		else if(number == 3){
			HAL_GPIO_WritePin(RL_3_GPIO_Port, RL_3_Pin, LOW);	
			flagSensorActive[3] = false;
		}
		else if(number == 4){
			HAL_GPIO_WritePin(RL_4_GPIO_Port, RL_4_Pin, LOW);	
			flagSensorActive[4] = false;
		}
		else if(number == 5){
			HAL_GPIO_WritePin(RL_5_GPIO_Port, RL_5_Pin, LOW);	
			flagSensorActive[5] = false;
		}
		else if(number == 6){
			HAL_GPIO_WritePin(RL_6_GPIO_Port, RL_6_Pin, LOW);	
			flagSensorActive[6] = false;
		}
		else if(number == 7){
			HAL_GPIO_WritePin(RL_7_GPIO_Port, RL_7_Pin, LOW);	
			flagSensorActive[7] = false;
		}
		else if(number == 8){
			HAL_GPIO_WritePin(RL_8_GPIO_Port, RL_8_Pin, LOW);	
			flagSensorActive[8] = false;
		}
		else if(number == 9){
			HAL_GPIO_WritePin(RL_9_GPIO_Port, RL_9_Pin, LOW);	
			flagSensorActive[9] = false;
		}
		else if(number == 10){
			HAL_GPIO_WritePin(RL_10_GPIO_Port, RL_10_Pin, LOW);	
			flagSensorActive[10] = false;
		}
		else if(number == 11){
			HAL_GPIO_WritePin(RL_11_GPIO_Port, RL_11_Pin, LOW);	
			flagSensorActive[11] = false;
		}
		else if(number == 12){
			HAL_GPIO_WritePin(RL_12_GPIO_Port, RL_12_Pin, LOW);
			flagSensorActive[12] = false;			
		}
		else if(number == 13){
			HAL_GPIO_WritePin(RL_13_GPIO_Port, RL_13_Pin, LOW);	
			flagSensorActive[13] = false;
		}
		else if(number == 14){
			HAL_GPIO_WritePin(RL_14_GPIO_Port, RL_14_Pin, LOW);	
			flagSensorActive[14] = false;
		}
		else if(number == 15){
			HAL_GPIO_WritePin(RL_15_GPIO_Port, RL_15_Pin, LOW);	
			flagSensorActive[15] = false;
		}
		else if(number == 16){
			HAL_GPIO_WritePin(RL_16_GPIO_Port, RL_16_Pin, LOW);
			flagSensorActive[16] = false;
		}
		else{
			HAL_GPIO_WritePin(RL_0_GPIO_Port, RL_0_Pin, LOW);
			HAL_GPIO_WritePin(RL_1_GPIO_Port, RL_1_Pin, LOW);
			HAL_GPIO_WritePin(RL_2_GPIO_Port, RL_2_Pin, LOW);
			HAL_GPIO_WritePin(RL_3_GPIO_Port, RL_3_Pin, LOW);
			HAL_GPIO_WritePin(RL_4_GPIO_Port, RL_4_Pin, LOW);
			HAL_GPIO_WritePin(RL_5_GPIO_Port, RL_5_Pin, LOW);
			HAL_GPIO_WritePin(RL_6_GPIO_Port, RL_6_Pin, LOW);
			HAL_GPIO_WritePin(RL_7_GPIO_Port, RL_7_Pin, LOW);
			HAL_GPIO_WritePin(RL_8_GPIO_Port, RL_8_Pin, LOW);
			HAL_GPIO_WritePin(RL_9_GPIO_Port, RL_9_Pin, LOW);
			HAL_GPIO_WritePin(RL_10_GPIO_Port, RL_10_Pin, LOW);
			HAL_GPIO_WritePin(RL_11_GPIO_Port, RL_11_Pin, LOW);
			HAL_GPIO_WritePin(RL_12_GPIO_Port, RL_12_Pin, LOW);
			HAL_GPIO_WritePin(RL_13_GPIO_Port, RL_13_Pin, LOW);
			HAL_GPIO_WritePin(RL_14_GPIO_Port, RL_14_Pin, LOW);
			HAL_GPIO_WritePin(RL_15_GPIO_Port, RL_15_Pin, LOW);
			HAL_GPIO_WritePin(RL_16_GPIO_Port, RL_16_Pin, LOW);
		}
}

void limitOn(int number){
	if(number == 0){
			HAL_GPIO_WritePin(GPIOB, LIM0_Pin, HIGH);
	}else if(number == 1){
			HAL_GPIO_WritePin(GPIOE, LIM1_Pin, HIGH);
	}else if(number == 2){
			HAL_GPIO_WritePin(GPIOE, LIM2_Pin, HIGH);
	}else if(number == 3){
			HAL_GPIO_WritePin(GPIOE, LIM3_Pin, HIGH);
	}else if(number == 4){
			HAL_GPIO_WritePin(GPIOE, LIM4_Pin, HIGH);
	}else if(number == 5){
			HAL_GPIO_WritePin(GPIOE, LIM5_Pin, HIGH);
	}else if(number == 6){
			HAL_GPIO_WritePin(GPIOE, LIM6_Pin, HIGH);
	}else if(number == 7){
			HAL_GPIO_WritePin(GPIOE, LIM7_Pin, HIGH);
	}else if(number == 8){
			HAL_GPIO_WritePin(GPIOE, LIM8_Pin, HIGH);
	}else if(number == 9){
			HAL_GPIO_WritePin(GPIOE, LIM9_Pin, HIGH);
	}else if(number == 10){
			HAL_GPIO_WritePin(GPIOB, LIM10_Pin, HIGH);
	}else if(number == 11){
			HAL_GPIO_WritePin(GPIOB, LIM11_Pin, HIGH);
	}else if(number == 12){
			HAL_GPIO_WritePin(GPIOB, LIM12_Pin, HIGH);
	}else if(number == 13){
			HAL_GPIO_WritePin(GPIOB, LIM13_Pin, HIGH);
	}else if(number == 14){
			HAL_GPIO_WritePin(GPIOD, LIM14_Pin, HIGH);
	}else if(number == 15){
			HAL_GPIO_WritePin(GPIOD, LIM15_Pin, HIGH);
	}else{
			HAL_GPIO_WritePin(GPIOB, LIM0_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, LIM1_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, LIM2_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, LIM3_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, LIM4_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, LIM5_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, LIM6_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, LIM7_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, LIM8_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, LIM9_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOB, LIM10_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOB, LIM11_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOB, LIM12_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOB, LIM13_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOD, LIM14_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOD, LIM15_Pin, HIGH);
	}
}

void limitOff(int number){
		if(number == 0){
			HAL_GPIO_WritePin(GPIOB, LIM0_Pin, LOW);
	}else if(number == 1){
			HAL_GPIO_WritePin(GPIOE, LIM1_Pin, LOW);
	}else if(number == 2){
			HAL_GPIO_WritePin(GPIOE, LIM2_Pin, LOW);
	}else if(number == 3){
			HAL_GPIO_WritePin(GPIOE, LIM3_Pin, LOW);
	}else if(number == 4){
			HAL_GPIO_WritePin(GPIOE, LIM4_Pin, LOW);
	}else if(number == 5){
			HAL_GPIO_WritePin(GPIOE, LIM5_Pin, LOW);
	}else if(number == 6){
			HAL_GPIO_WritePin(GPIOE, LIM6_Pin, LOW);
	}else if(number == 7){
			HAL_GPIO_WritePin(GPIOE, LIM7_Pin, LOW);
	}else if(number == 8){
			HAL_GPIO_WritePin(GPIOE, LIM8_Pin, LOW);
	}else if(number == 9){
			HAL_GPIO_WritePin(GPIOE, LIM9_Pin, LOW);
	}else if(number == 10){
			HAL_GPIO_WritePin(GPIOB, LIM10_Pin, LOW);
	}else if(number == 11){
			HAL_GPIO_WritePin(GPIOB, LIM11_Pin, LOW);
	}else if(number == 12){
			HAL_GPIO_WritePin(GPIOB, LIM12_Pin, LOW);
	}else if(number == 13){
			HAL_GPIO_WritePin(GPIOB, LIM13_Pin, LOW);
	}else if(number == 14){
			HAL_GPIO_WritePin(GPIOD, LIM14_Pin, LOW);
	}else if(number == 15){
			HAL_GPIO_WritePin(GPIOD, LIM15_Pin, LOW);
	}else{
			HAL_GPIO_WritePin(GPIOB, LIM0_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, LIM1_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, LIM2_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, LIM3_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, LIM4_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, LIM5_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, LIM6_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, LIM7_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, LIM8_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, LIM9_Pin, LOW);
			HAL_GPIO_WritePin(GPIOB, LIM10_Pin, LOW);
			HAL_GPIO_WritePin(GPIOB, LIM11_Pin, LOW);
			HAL_GPIO_WritePin(GPIOB, LIM12_Pin, LOW);
			HAL_GPIO_WritePin(GPIOB, LIM13_Pin, LOW);
			HAL_GPIO_WritePin(GPIOD, LIM14_Pin, LOW);
			HAL_GPIO_WritePin(GPIOD, LIM15_Pin, LOW);
	}
}











