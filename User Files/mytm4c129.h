#ifndef __MY_TM4C129_H
#define __MY_TM4C129_H

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/inc/hw_memmap.h"
#include "driverlib/inc/hw_types.h"
#include "driverlib/inc/hw_nvic.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

/* Declaring Function Prototype */


/*	@Description	:	This function initialize systick timer for Delay_ms
 *                   	Enable Global Interrupt and Systick Interrupt
 *	
 *	@Brief			:	+	System_Clock_Hz - This is system clock value in hz
 *
 *	@Return			:	None
 *
 *	@Note			:	User must be call this function before call any Delay_ms
 * 
 */
void SysTick_For_Delay_Init(uint32_t System_Clock_Hz);


/*	@Description	:	This is systick timer Interrupt Service Rountie
 *	
 *	@Brief			:	None
 *
 *	@Return			:	None
 *
 *	@Note			:	None
 * 
 */
void SysTick_ISR(void);


/*	@Description	:	This is precision delay function 
 *	
 *	@Brief			:	time_in_ms - Time to delay (mS)
 *
 *	@Return			:	None
 *
 *	@Note			:	Do not use Delay_ms in any ISR, CPU will stuck
 * 
 */
void Delay_ms(uint32_t time_in_ms);

#endif
