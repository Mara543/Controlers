#ifndef INC_SCT_H_
#define INC_SCT_H_

#include "main.h"

void sct_led(uint32_t value);

void sct_value(int16_t value, uint8_t led, uint8_t pointIndex);

void sct_init(void);

#endif /* INC_SCT_H_ */
