#include "mytm4c129.h"

volatile uint32_t time_keeper;


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
void SysTick_For_Delay_Init(uint32_t System_Clock_Hz)
{
	/* Generate 1ms interrupt */
	MAP_SysTickPeriodSet(System_Clock_Hz/1000);

	SysTickIntRegister(SysTick_ISR);

	/* Global interrupt enable */
	MAP_IntMasterEnable();

	/* Systick interrupt enable */
	MAP_SysTickIntEnable();
}



/*	@Description	:	This is systick timer Interrupt Service Rountie
 *	
 *	@Brief			:	None
 *
 *	@Return			:	None
 *
 *	@Note			:	None
 * 
 */
void SysTick_ISR(void)
{
	/*	The SysTick interrupt handler does not need to clear the SysTick interrupt source
	 * 	as it is cleared automatically by the NVIC when the SysTick interrupt handler is
	 * 	called.
	 */

	if(time_keeper)
	{
		time_keeper--;
	}
	else
	{
		/* SysTick disable */
		MAP_SysTickDisable();
	}
}



/*	@Description	:	This is precision delay function 
 *	
 *	@Brief			:	time_in_ms - Time to delay (mS)
 *
 *	@Return			:	None
 *
 *	@Note			:	Do not use Delay_ms in any ISR, CPU will stuck
 * 
 */
void Delay_ms(uint32_t time_in_ms)
{

	time_keeper = time_in_ms;

	/* Systick enable */
	MAP_SysTickEnable();

	/* Reset systick counter */
	HWREG(NVIC_ST_CURRENT) = HWREG(NVIC_ST_RELOAD);

	while(time_keeper);

}



