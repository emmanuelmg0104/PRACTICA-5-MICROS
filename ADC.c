/*
 * ADC.c
 *
 *  Created on: 24 jun. 2021
 *      Author: Personal
 */

#include "MKL25Z4.h"
#include<stdio.h>
#include "adc.h"
//**************************************************
//				ADC DRIVERS
//**************************************************

void ADC_vfnDriverInit ( void )
{
	SIM->SCGC6 = 0x8000000; //Activar reloj del ADC viene del manual 800,000

	SIM->SCGC5 = 0x3E00;	//Inicializar reloj del puerto B

	PORTB->PCR[0] |= PORT_PCR_MUX(0); // Entrada analogica B0, SE PONE UN CERO PARA INDICAR QUE ES ENTRADA ANALOGICA


	/*8 bit conversion*/
	ADC0->CFG1 = 0x70; //1111000      0x70 = 8bits  INDICA RESOLUCION MODE 00

	ADC0->CFG1 |= (ADC_CFG1_ADLPC(0)); //Modo de POTENCIA NORMAL   //JALA CON 1

	ADC0->SC1[0] = ADC_SC1_ADCH(31); //Desactivar todos los canales (1F =31) PRIMEROS 5BITS ADCH DEL REGISTRO SC1

}

unsigned short  ADC_bfnReadADC(unsigned char channelNumber)
{
	unsigned short x=0;
	//canal 8


	ADC0->SC1[0] = channelNumber & ADC_SC1_ADCH_MASK;  //canal and matriz de ADCH para activar canal 8 porque anteriormente valian 0, y solo se activa el canal 8, activa b0 como entrada de ADC.
	          //se ejecuta la conversion                  //Write to SC1A to start conversion
	while(ADC0->SC2 & ADC_SC2_ADACT_MASK);   			//Conversion in progress la mascara hace referencia a que nuestra conversion esta en progreso. todos los valores en 0,
	while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK));			//wait till conversion is complete
	x = ADC0->R[0];
	return ADC0->R[0]; //return the ADC value


}
