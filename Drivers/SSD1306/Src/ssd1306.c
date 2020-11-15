/*
 * ssd1306.c
 *
 *  Created on: Nov 4, 2020
 *      Author: Rajssss@GitHub.com
 */

#include "ssd1306.h"


//I2C handle to be used
extern I2C_HandleTypeDef SSD1306_I2C_HANDLE;



uint8_t cmd[] = {

		/**********************************************************************************
		 *
		 *  SSD1306 Driver Initialization Commands.
		 *
		 * ********************************************************************************/

		0xA8, 0x3F,				/* Set MUX Ratio */
		0xD3, 0x00,				/* Set Display Offset */
		0x40,					/* Set Display Start Line */
		0xA1,					/* Set Segment re-map */
		0xC8,					/* Set COM Output Scan Direction */
		0xDA, 0x02,				/* Set COM Pins hardware configuration */
		0x81, 0x7F,				/* Set Contrast Control */
		0xA4,					/* Disable Entire Display On */
		0xA6,					/* Set Normal Display */
		0xD5, 0x80,				/* Set Oscillator Frequency */
		0x8D, 0x14,				/* Enable Charge Pump Regulator */
		0xAF					/* Display On */
};



void ssd1306_init(void)
{
	char tmp[2];

	memset(tmp, 0, 1);
	sprintf(tmp, "%x", 0x00);

	//tell driver that its command (0x00)
	HAL_I2C_Master_Transmit(&SSD1306_I2C_HANDLE, SSD1306_I2C_ADDR, (uint8_t *)tmp, 1, 100);

	//then send the commands
	HAL_I2C_Master_Transmit(&SSD1306_I2C_HANDLE, SSD1306_I2C_ADDR, cmd, sizeof(cmd), HAL_MAX_DELAY);

}




void ssd1306_position(uint8_t x, uint8_t y)
{
	char tmp[2];

	memset(tmp, 0, 1);
	sprintf(tmp, "%x", (0x00 + (0x0F & x)));
	HAL_I2C_Master_Transmit(&SSD1306_I2C_HANDLE, SSD1306_I2C_ADDR, (uint8_t *)tmp, 1, 100);					//set lower column

	memset(tmp, 0, 1);
	sprintf(tmp, "%x", (0x10 + (0x0F & (x >> 4))));
	HAL_I2C_Master_Transmit(&SSD1306_I2C_HANDLE, SSD1306_I2C_ADDR, (uint8_t *)tmp, 1, 100);					//set higher column

	memset(tmp, 0, 1);
	sprintf(tmp, "%x", (0xB0 + y));
	HAL_I2C_Master_Transmit(&SSD1306_I2C_HANDLE, SSD1306_I2C_ADDR, (uint8_t *)tmp, 1, 100);			//set row


}




void ssd1306_reset()
{
	char tmp[5];

	//clear the whole screen
	ssd1306_position(0, 0);



	for(int i = 0; i<8; i++)
	{
		for(int j = 0; j<128; j++)
		{
			memset(tmp, 0, 1);
			sprintf(tmp, "%x", 0x40);
			HAL_I2C_Master_Transmit(&SSD1306_I2C_HANDLE, SSD1306_I2C_ADDR, (uint8_t *)tmp, 1, 100);

			memset(tmp, 0, 1);
			sprintf(tmp, "%x", 0x00);
			HAL_I2C_Master_Transmit(&SSD1306_I2C_HANDLE, SSD1306_I2C_ADDR, (uint8_t *)tmp, 1, 100);
		}
	}

	ssd1306_position(0, 0);

}


