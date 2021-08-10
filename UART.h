/*
 * UART.h
 *
 *  Created on: 22 jul. 2021
 *      Author: arz_m
 */

#ifndef UART_H_
#define UART_H_

extern void UART_vfnDriverInit (void);
extern void UART_bfnRead(uint8_t *recived);
extern void transmit(unsigned char *DATA);

#endif /* UART_H_ */
