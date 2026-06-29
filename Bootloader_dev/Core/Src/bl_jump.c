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
#include "app_header.h"

#define APP_MAGIC    0xABCDEFAB

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
	SCB->VTOR = APP_ADDR;
    __set_MSP(appStack);
    __enable_irq();
    // Jump to application reset handler
    appEntry();

}


int bootloader_is_app_valid(void)
{
	uint32_t HDR_ADDR = APP_HEAD_ADDR;
    const app_header_t *app_hdr = (const app_header_t *)HDR_ADDR;

    /* Magic */
    if (app_hdr->magic != APP_MAGIC)
        return 1;

    /* Reset handler sanity */
    uint32_t reset_handler = *(uint32_t *)(APP_ADDR + 4);
    if ((reset_handler & 0xFF000000) != 0x08000000)
        return 2;

    return 0;   // VALID
}

