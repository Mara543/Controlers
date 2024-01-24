/*
 * sct.c
 *
 *  Created on: Jan 14, 2024
 *      Author: matej
 */
#include "main.h"
#include "sct.h"

void sct_init(void) {

	sct_led(0);
}

void sct_led(uint32_t value) {
	for (uint8_t i = 0; i < 32; i++) {
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_SDI_Pin, (value >> i) & 1);
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 1);
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 0);
	}
// Latch the value from the shift register to the output latch register
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 1);
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 0);

	// Enable outputs
	HAL_GPIO_WritePin(SCT_NOE_GPIO_Port, SCT_NOE_Pin, 0);

}


static const uint32_t reg_values[1][7] = {

   {//PCDE--------GFAB----PCDEGFAB---- dis1,2
	//----------------PCDE--------GFAB dis3
    0b00000000000000000000000000000000 << 0,
	0b00000000000000000000000010000000 << 0,
	0b00000000000000000000001000100000 << 0,
	0b00000000000000100010000010000000 << 0,
	0b00100000000000100010000000000010 << 0,
	0b00100000000000100010000010000010 << 0,
	0b00100000000010100010000000001010 << 0,

	},
};

void sct_value(uint16_t value){
	uint32_t reg=0;
	reg |= reg_values[0][value];


	sct_led(reg);
}

