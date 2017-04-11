#include <stdbool.h>
#include <stdint.h>
#include "driverlib/inc/hw_memmap.h"
#include "driverlib/inc/hw_types.h"
#include "driverlib/inc/hw_nvic.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "mytm4c129.h"

/* Declaring Global Variables */
#define LED_PORT		GPIO_PORTN_BASE
#define	LED2_PIN		GPIO_PIN_0
#define LED1_PIN		GPIO_PIN_1

#define BUTTON_PORT		GPIO_PORTJ_BASE
#define BUTTON1_PIN		GPIO_PIN_0
#define BUTTON2_PIN		GPIO_PIN_1


/* Declaring Function Prototype */
void BUTTON_ISR(void);
uint32_t count=0;

int main(void)
{
	/* Configure system clock using external clock and PLL */
	MAP_SysCtlClockFreqSet(SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480,
			120000000);

	/* Enable peripheral clock */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

	/* Configure led as output */
	GPIOPinTypeGPIOOutput(LED_PORT, LED2_PIN | LED1_PIN);
	GPIOPinWrite(LED_PORT, LED2_PIN | LED1_PIN, 0x00);

	/* Configure two buttons as input with pull up */
	GPIODirModeSet(BUTTON_PORT, BUTTON1_PIN | BUTTON2_PIN,GPIO_DIR_MODE_IN);
	GPIOPadConfigSet(BUTTON_PORT, BUTTON1_PIN | BUTTON2_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	GPIOIntRegister(BUTTON_PORT,BUTTON_ISR);

	/* Set falling trigger */
	GPIOIntTypeSet(BUTTON_PORT,BUTTON1_PIN | BUTTON2_PIN, GPIO_FALLING_EDGE);

	/* GPIO Interrupt Enable */
	GPIOIntEnable(BUTTON_PORT, BUTTON1_PIN|BUTTON2_PIN);

	IntMasterEnable();
	/* Infinite Loop */
	while(1)
	{
	}
}


void BUTTON_ISR(void)
{
	 uint32_t status = GPIOIntStatus(BUTTON_PORT,true);
        
	GPIOIntClear(BUTTON_PORT,status);

	if((status & BUTTON1_PIN) == BUTTON1_PIN)
	{
		if(GPIOPinRead(LED_PORT,LED1_PIN))
		{
			GPIOPinWrite(LED_PORT,LED1_PIN,0x00);
		}
		else
		{
			GPIOPinWrite(LED_PORT,LED1_PIN,0xff);
		}
	}

	if((status & BUTTON2_PIN) == BUTTON2_PIN)
	{
		if(GPIOPinRead(LED_PORT,LED2_PIN))
		{
			GPIOPinWrite(LED_PORT,LED2_PIN,0x00);
		}
		else
		{
			GPIOPinWrite(LED_PORT,LED2_PIN,0xff);
		}
	}
}


