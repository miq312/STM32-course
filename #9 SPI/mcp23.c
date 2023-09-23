/*
 * mcp23.c
 *
 *  Created on: Sep 22, 2023
 *      Author: Michał
 */


#include "mcp23.h"
#include "spi.h"

void mcp_reg_write(uint8_t reg, uint8_t value)
{
	uint8_t tx[3] = { 0x40, reg, value };

	HAL_GPIO_WritePin(IOEXP_CS_GPIO_Port, IOEXP_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, tx, 3, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(IOEXP_CS_GPIO_Port, IOEXP_CS_Pin, GPIO_PIN_SET);
}

uint8_t mcp_reg_read(uint8_t reg)
{
	uint8_t txrx[3] = { 0x41, reg, 0xff};

	HAL_GPIO_WritePin(IOEXP_CS_GPIO_Port, IOEXP_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi2, txrx, txrx, 3, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(IOEXP_CS_GPIO_Port, IOEXP_CS_Pin, GPIO_PIN_SET);

	return txrx[2];
}

uint8_t mcp_gpio_readPin(uint8_t gpio_num)
{
	if(check_bit(mcp_reg_read(MCP_IODIR), gpio_num) == 0)
	{
		return check_bit(mcp_reg_read(MCP_GPIO), gpio_num);
	}

	else
	{
		return -1;
	}
}


void mcp_gpio_writePin(uint8_t gpio_num, int value)
{

	uint8_t bit_state = mcp_reg_read(MCP_GPIO);

	uint8_t current_gpio_value = check_bit(bit_state, gpio_num);

	if(value == 0 && current_gpio_value == 1)
	{
		bit_state ^= 1 << gpio_num;
	}

	else if(value == 1 && current_gpio_value == 0)
	{
		bit_state ^= 1 << gpio_num;
	}

	mcp_reg_write(MCP_OLAT, bit_state);
}

uint8_t check_bit(uint8_t bit_array, uint8_t position)
{
	if( ((bit_array >> position) & 0x01) == 0x01)
	{
			return 1;
	}

	else
	{
		return 0;
	}
}
