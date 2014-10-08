/* ###################################################################
 **     Filename    : mqx_tasks.c
 **     Project     : WeatherStation
 **     Processor   : MKL46Z256VMC4
 **     Component   : Events
 **     Version     : Driver 01.00
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2014-10-06, 23:33, # CodeGen: 11
 **     Abstract    :
 **         This is user's event module.
 **         Put your event handler code here.
 **     Settings    :
 **     Contents    :
 **         UsartDebug_task - void UsartDebug_task(uint32_t task_init_data);
 **
 ** ###################################################################*/
/*!
 ** @file mqx_tasks.c
 ** @version 01.00
 ** @brief
 **         This is user's event module.
 **         Put your event handler code here.
 */
/*!
 **  @addtogroup mqx_tasks_module mqx_tasks module documentation
 **  @{
 */
/* MODULE mqx_tasks */

#include "Cpu.h"
#include "Events.h"
#include "mqx_tasks.h"
#include "lcd/LCD.h"
#include "SegLCD1.h"
#include "sensors/adt7410.h"

#ifdef __cplusplus
extern "C" {
#endif 

/* User includes (#include below this line is not maintained by Processor Expert) */

/*
 ** ===================================================================
 **     Event       :  UsartDebug_task (module mqx_tasks)
 **
 **     Component   :  Task1 [MQXLite_task]
 **     Description :
 **         MQX task routine. The routine is generated into mqx_tasks.c
 **         file.
 **     Parameters  :
 **         NAME            - DESCRIPTION
 **         task_init_data  -
 **     Returns     : Nothing
 ** ===================================================================
 */
void UsartDebug_task(uint32_t task_init_data) {
	int counter = 0;
	typedef struct {
		LDD_TDeviceData *handle; /* LDD device handle */
		volatile uint8_t isSent; /* this will be set to 1 once the block has been sent */
		uint8_t rxChar; /* single character buffer for receiving chars */
		uint8_t (*rxPutFct)(uint8_t); /* callback to put received character into buffer */
	} UART_Debug_Desc;

	static UART_Debug_Desc debugData;
	//static const char* string = "TEST_EXAMPLE_FRDM46_KLZ_DEVELOPmentBoard\n";
	debugData.handle = USART0_DEBUG_Init(&debugData);
	while (1) {
		counter++;
		_time_delay_ticks(100000);
		//USART0_DEBUG_SendBlock(debugData.handle, string, strlen(string));
		/* Write your code here ... */

	}
}

/*
 ** ===================================================================
 **     Event       :  Lcd_task (module mqx_tasks)
 **
 **     Component   :  Task2 [MQXLite_task]
 **     Description :
 **         MQX task routine. The routine is generated into mqx_tasks.c
 **         file.
 **     Parameters  :
 **         NAME            - DESCRIPTION
 **         task_init_data  -
 **     Returns     : Nothing
 ** ===================================================================
 */
void Lcd_task(uint32_t task_init_data) {
	int counter = 0;

	while (1) {
		counter++;

		_time_delay_ticks(1000);
			if (counter % 2) {
			vfnLCD_Write_Char('H');

			vfnLCD_Write_Char('E');

			vfnLCD_Write_Char('L');
			vfnLCD_Write_Char('0');
		}

		else {
			vfnLCD_Write_Msg("  ");  // TURN ON all characters
			vfnLCD_Home();
		}

	}
}

/*
 ** ===================================================================
 **     Event       :  Task3_task (module mqx_tasks)
 **
 **     Component   :  Task3 [MQXLite_task]
 **     Description :
 **         MQX task routine. The routine is generated into mqx_tasks.c
 **         file.
 **     Parameters  :
 **         NAME            - DESCRIPTION
 **         task_init_data  -
 **     Returns     : Nothing
 ** ===================================================================
 */
void Task3_task(uint32_t task_init_data) {
	int counter = 0;
	initADT7410();
	LDD_TDeviceData *handle =USART0_DEBUG_Init(NULL);
	while (1) {
		counter++;
		int iInt= getIdNumber();
		if(iInt==2)	USART0_DEBUG_SendBlock(handle, "AAAAA", 4);
		char id =(char)iInt;
		vfnLCD_Write_Msg("  ");
		vfnLCD_Write_Char(id);
		static const char* string = "TEMPERATURE:";
	    USART0_DEBUG_SendBlock(handle, string, strlen(string));

	    USART0_DEBUG_SendBlock(handle, &id, 1);
		_time_delay_ticks(2000);

	}
}

/*
 ** ===================================================================
 **     Event       :  Task4_task (module mqx_tasks)
 **
 **     Component   :  Task4 [MQXLite_task]
 **     Description :
 **         MQX task routine. The routine is generated into mqx_tasks.c
 **         file.
 **     Parameters  :
 **         NAME            - DESCRIPTION
 **         task_init_data  -
 **     Returns     : Nothing
 ** ===================================================================
 */
void Task4_task(uint32_t task_init_data) {
	int counter = 0;

	while (1) {
		counter++;

		/* Write your code here ... */

	}
}

/* END mqx_tasks */

#ifdef __cplusplus
} /* extern "C" */
#endif 

/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.4 [05.10]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
