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
 **         InitHw_task - void InitHw_task(uint32_t task_init_data);
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
#include "mqxlite.h"
#include "lcd/LCD.h"
#include "SegLCD1.h"
#include "sensors/adt7410.h"
#include "sensors/BMP180.h"
#include "uart/uart.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif 

/* User includes (#include below this line is not maintained by Processor Expert) */

static bool initHardware(void) {

	if (!uartInit(UART0_mod))
		return false;
	//i2cInit(I2C1_mod, 0x00); /*0x00 fake address, init of the bus , selecting devices is made further methods*/
	i2cInit(I2C0_mod, 0x00); /*0x00 fake address, init of the bus , selecting devices is made further methods*/
	adt7410Init(i2cGetI2CHandle(I2C0_mod), I2C0_mod);
	bmp180Init(i2cGetI2CHandle(I2C0_mod), I2C0_mod);
	return true;
}

/*
 ** ===================================================================
 **     Event       :  InitHw_task (module mqx_tasks)
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
void InitHw_task(uint32_t task_init_data) {

	//)
	//_task_block();  //init Hardware failed

	_task_id created_task;
	created_task = _task_create(0, LCDTASK_TASK, 0);
	if (created_task == MQX_NULL_TASK_ID) {

		// printf("Error: Cannot create task\n");
		//	_task_block();
	}
	/*
	 created_task = _task_create(0, SENSORSTASK_TASK, 0);
	 if (created_task == MQX_NULL_TASK_ID) {
	 // printf("Error: Cannot create task\n");
	 _task_block();
	 }
	 */
	//_task_destroy(MQX_NULL_TASK_ID);
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

		_time_delay_ticks(100);
		counter++;

		if (counter % 2) {
			vfnLCD_Write_Char('H');

			vfnLCD_Write_Char('E');

			vfnLCD_Write_Char('L');
			vfnLCD_Write_Char('0');
		}

		else {
			vfnLCD_Write_Msg("  ");  // TURN ON all characters
			vfnLCD_Home();
		}  //
	}
}

/*
 ** ===================================================================
 **     Event       :  Sensors_task (module mqx_tasks)
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
static void sprintfDouble(double v, int decimalDigits, uint8_t* buf,
		uint8_t bufSize) {
	int i = 1;
	int intPart, fractPart;
	for (; decimalDigits != 0; i *= 10, decimalDigits--)
		;
	intPart = (int) v;
	fractPart = (int) ((v - (double) (int) v) * i);
	snprintf(buf, bufSize, "%2d.%2d", intPart, fractPart);
}

void Sensors_task(uint32_t task_init_data) {
	static const char* string[] = { "\n\rADT7410: ", "readFailed", "readOk",
			"\n\rBMP180: " };
	uint8_t tempBuf[15];
	initHardware();
	while (1) {
		_time_delay_ticks(99);
		/*

		 int iInt = adt7410GetIdNumber();
		 snprintf(tempBuf, 4, "%d", iInt);
		 vfnLCD_Write_Msg("  ");  // TURN ON all characters
		 vfnLCD_Home();
		 vfnLCD_Write_MsgPlace(tempBuf, 4);
		 vfnLCD_Write_Msg(tempBuf);

		 */

		uartSendData(string[0], strlen(string[0]));
		if (adt7410ReadTemp() == 0)
			uartSendData(string[1], strlen(string[1]));
		else {
			sprintfDouble(adt7410GetTemperature(), 2, tempBuf, 6);
			//snprintf(tempBuf, 9, "%5.2f", temp);
			uartSendData(tempBuf, 5);
		}

		uartSendData(string[3], strlen(string[3]));

		if (bmp180ReadData() == 0)
			uartSendData(string[1], strlen(string[1]));
		else {
			sprintfDouble(bmp180GetPressure(), 2, tempBuf, 6);
			/*float adc_read = bmp180GetPressure();
			int d1 = adc_read;            // Get the integer part
			float f2 = adc_read - d1;     // Get fractional part
			int d2 = (int) (f2 * 10000);
			sprintf(tempBuf, "%d.%02d\r\n", d1, d2);
*/
			tempBuf[6] = '\r';
						tempBuf[7] = '\n';
			uartSendData(tempBuf, 8);
			sprintfDouble(bmp180GetTemperature(), 2, tempBuf, 6);
			tempBuf[6] = '\r';
			tempBuf[7] = '\n';
			uartSendData(tempBuf, 8);
		}

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
