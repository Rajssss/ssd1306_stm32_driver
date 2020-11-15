/*
 * ssd1360.h
 *
 *  Created on: Nov 4, 2020
 *      Author: Rajssss@GitHub.com
 */

#ifndef SSD1306_INC_SSD1306_H_
#define SSD1306_INC_SSD1306_H_

//Includes
#include <stdio.h>
#include <string.h>
#include "ssd1306_conf.h"
#include "stm32f4xx_hal.h"


//Prototypes
void ssd1306_init(void);
void ssd1306_position(uint8_t x, uint8_t y);
void ssd1306_reset();


#endif /* SSD1306_INC_SSD1306_H_ */
