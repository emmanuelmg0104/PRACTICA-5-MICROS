/*
 * UART.c
 *
 *  Created on: 22 jul. 2021
 *      Author: arz_m
 */

#include <stdio.h>
#include "MKL25Z4.h"
#include "Arduino.h"


void UART_vfnDriverInit (void);
unsigned char UART_bfnRead(uint8_t *recived);
void transmit( char *DATA);
void COMM_bfnReceiveMsg ( char *bpDataRx);


void UART_vfnDriverInit (void){
	MCG->C4=0xA0;							//Configuramos reloj a 48MHz
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);	//Seleccionamos el reloj MCGFLLCLK
	SIM->SCGC4|=SIM_SCGC4_UART0_MASK;		//Habilitamos el reloj de UART0
	SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;		//Habilitamos el reloj del puerto A
	PORTA->PCR[1]|=PORT_PCR_MUX(2);			//Configuramos puerto A1 como Rx
	PORTA->PCR[2]|=PORT_PCR_MUX(2);			//Configuramos puerto A2 como Tx
	UART0->BDL=0x38;						//Valores bajos de Baudios
	UART0->BDH=0x1;							//Valores altos de Baudios
	UART0->C1=0x0;							//Configuracion UART: Sin paridad, 8 bits, funcionamiento normal(Rx Tx habilitados, modo de espera)
	UART0->C2=0xC;							//Habilitar transmisor y receptor
	//UART0->C2 |= UART_C2_RE(1);
	//UART0->C2 |= UART_C2_TE(1);
	UART0->C4=0x20;							//El receptor y transmisor usaran datos de 8 o 9 bits
}

void transmit(char *DATA){
	while(*DATA){
		UART0->D=*DATA;
		delayMs(500);
		while(!(UART0->S1&UART_S1_TDRE_MASK));
		DATA++;
	}
}



//unsigned char UART_bfnRead(uint8_t *recived){
//  //UART0->C2=0X4;
//	while(!(UART0->S1 & UART0_S1_RDRF_MASK));  //jala sin este
//  *recived=UART0->D; //Guardar el valor recivido en buffer de UART
//}
//dato
//COMM_bfnReceiveMsg(&dato)


void COMM_bfnReceiveMsg ( char *bpDataRx){
	char letra=0;

			while(bpDataRx){
				//while(!(UART0->S1 & UART0_S1_RDRF_MASK));  //jala sin este
				if(UART_S1_RDRF_MASK & UART0->S1){
				letra=UART0->D;
				if(letra){
					if(letra=='4'){
						break;
						}
						*bpDataRx=letra;
						bpDataRx++;
				}
						}if(UART_S1_OR_MASK & UART0->S1){
							UART0->S1 |= UART_S1_OR_MASK;//limpiar buffer
							}
						}

}
