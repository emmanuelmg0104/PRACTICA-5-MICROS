/**
 * @file    Practica5_UART.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "Arduino.h"
#include "LCD1.h"
#include "UART.h"
#include "PWM.h"
#include "adc.h"

int main(void){

  	/* Init board hardware. */
	BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    UART_vfnDriverInit ();  //Inicializar UART
    LCD_init(); 			//Inicializar LCD
    PWM_vfnDriverInit(); 	//Inicializar PWM



    DPY_bInitialPosition(); //Servo en Pos. Inicial 0°

    unsigned int vActual=0;
    unsigned int vPasado=0;
    unsigned char Grados = "236";
    unsigned char r0[10];
 unsigned char dato[]="hola";
    char buffer[11];
//profe, el azul se tiene que mandar cmo "a", "z","u","l"
//no se puede enviar el string azul, debido a que el protocolo uart
//solo maneja 8 bits, y el arduino tiene librerias"faciles"
//reference manual pagina 734, tenemos planeado guardarlo en un arreglo por medio de apuntadores y hacer la comparacion con otro arreglo para prender los focos
// *preguntar por que el modulo "si recibe los datos a enviar" pero no los manda, si puede ayudar

    while(1){

    	COMM_bfnReceiveMsg(&buffer[0]);

    	//transmit(236);
 dato[0]=Grados;
//

    	//transmit(dato);
    	//RetardoMs(1000);
    	//  printf("%c\n",dato);

    	if(r0 != 0){

    		vActual = r0;

    		if(vActual != vPasado){
    			Grados = r0;
    			PWM_bfnAngleAdjustment (Grados);
    		 	LCD_command(DISPLAY_CLEAR);
    		 	DPY_bfnWriteMsg("TEMP:");
    		 	enteroACadena(r0,buffer);
    		 	DPY_bfnWriteMsg(buffer);
    		}
    		vPasado = r0;
    	}
    }
    return 0;
}
