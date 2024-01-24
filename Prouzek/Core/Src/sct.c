/*
 * sct.c
 *
 *  Created on: Oct 12, 2023
 *      Author: xkleme13
 */

//Includes
#include "stm32f0xx.h"
#include "main.h"
#include "sct.h"

void sct_init(void) {
	sct_led(0);
}

void sct_led(uint32_t value) {
	HAL_GPIO_WritePin(SCT_NOE_GPIO_Port, SCT_NOE_Pin, 0);		//Output enable
	for (uint8_t i = 0; i < 32; i++) {
		HAL_GPIO_WritePin(SCT_SDI_GPIO_Port, SCT_SDI_Pin, value & 1);//bitova maska 0bxxxX & 0b0001
		value >>= 1;									//posunu na dalsi bit
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 1);			//clk
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 0);
	}
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 1);				//latch
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 0);
}

static const uint32_t reg_values[1][8] = {			//[počet tabulek][počet řádků] Dvou rozměrné pole

//zobrazování na displeji

		{
				//PCDE--------GFAB----PCDEGFAB---- display 1,2
				//----------------PCDE--------GFAB   display 3
				0b00000000000000100000000000000000 << 0,
				0b00000000000000000000000000100000 << 0,
				0b00000000000000000000000000000010 << 0,
				0b00000000000000000100000000000001 << 0,
				0b00000000000000000010000000000000 << 0,
				0b00000000000000000000001000000000 << 0,
				0b00100000000000000000000000000000 << 0,
				0b00010000000001000000000000000000 << 0, },

};

void sct_value(uint16_t value) {				//pro ledky, přidat druhjou proměnou
	uint32_t reg = 0;							//initialize to 0
	reg |= reg_values[0][value];				//určuje kterým řádkem má začít

	sct_led(reg);

}
