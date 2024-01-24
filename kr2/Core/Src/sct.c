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
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_SDI_Pin, (value >> i) %2);
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 1);
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 0);
	}
// Latch the value from the shift register to the output latch register
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 1);
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 0);

	// Enable outputs
	HAL_GPIO_WritePin(SCT_NOE_GPIO_Port, SCT_NOE_Pin, 0);

}


static const uint32_t reg_values[1][10] = {

	{
    //----43215678---- @ LED
    0b0000000100000000 << 16,
	0b0000001100000000 << 16,
	0b0000011100000000 << 16,
	0b0000111000000000 << 16,
	0b0000110010000000 << 16,
	0b0000100011000000 << 16,
	0b0000000011100000 << 16,
	0b0000000001110000 << 16,
	0b0000000000110000 << 16,
	0b0000000000010000 << 16,
					},

	};

void sct_value(uint8_t led){
	uint32_t reg=0;
	reg |= reg_values[0][led];

	sct_led(reg);
}

