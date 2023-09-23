/*
 * mcp23.h
 *
 *  Created on: Sep 22, 2023
 *      Author: Michał
 */

#ifndef INC_MCP23_H_
#define INC_MCP23_H_

#pragma once

#include <stdint.h>

#define MCP_IODIR 0x00
#define MCP_IPOL 0x01
#define MCP_GPINTEN 0x02
#define MCP_DEFVAL 0x03
#define MCP_INTCON 0x04
#define MCP_IOCON 0x05
#define MCP_GPPU 0x06
#define MCP_INTF 0x07
#define MCP_INTCAP 0x08
#define MCP_GPIO 0x09
#define MCP_OLAT 0x0A

//adresy pinow

#define GP0 0x01
#define GP1 0x02
#define GP2 0x04
#define GP3 0x08
#define GP4 0x10
#define GP5 0x20
#define GP6 0x40
#define GP7 0x80


// Odczytanie wartości rejestru
// reg - rejestr, który ma zostać odczytany
// return - wartość odczytanego rejestru
uint8_t mcp_reg_read(uint8_t reg);

uint8_t mcp_gpio_readPin(uint8_t reg);

// Zapisywanie nowej wartości do rejestru
// reg - rejestr, do którego zapisujemy
// value - wartość, która ma zostać zapisana
// return - funkcja nie zwraca żadnej wartości
void mcp_gpio_writePin(uint8_t gpio_num, int value);

uint8_t check_bit(uint8_t bit_array, uint8_t position);

void mcp_gpio_writePin(uint8_t reg, int value);
#endif /* INC_MCP23_H_ */
