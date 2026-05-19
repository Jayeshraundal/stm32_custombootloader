/*
 * 		bl_jump.c
 * 		created on 12.05.2026
 * 		Author: Jayesh Raundal
 *
 *
 * */
#include "main.h"
#include "bl_jump.h"
#include "flash_layout.h"


// function as pointer for appEntry
typedef void (*pFunction) (void);

void jumpToApplication(void){

	// declared variables
	uint32_t appStack;
	uint32_t appResetHandle;
	pFunction appEntry;


	appStack = *(volatile uint32_t *)APP_ADDR;
	appResetHandle = *(volatile uint32_t *)(APP_ADDR + 4);

	appEntry = (pFunction)appResetHandle;

	  // Disable interrupts

	__disable_irq();

	    // Stop SysTick

	SysTick->CTRL = 0;
	SysTick->LOAD = 0;
	SysTick->VAL  = 0;

    //Set main stack pointer

    __set_MSP(appStack);

    // Jump to application reset handler
    appEntry();

}
