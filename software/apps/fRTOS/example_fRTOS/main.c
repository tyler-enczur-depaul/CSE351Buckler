#include<stdio.h>

#include "app_error.h"
#include "app_timer.h"/**/
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_drv_clock.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_serial.h"

#include "buckler.h"

#include "FreeRTOS.h"
#include "task.h"


TaskHandle_t  vtask1_handle;  
TaskHandle_t  vtask2_handle;  

void prvSetupHardware(){

	printf("Include any hardware initialization commands here. \n");
}


/* The task functions. */
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );




int main( void )
{

	ret_code_t error_code;

    /* Initialize clock driver for better time accuracy in FREERTOS */
    error_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(error_code);


	printf("Successful compilation of FreeRTOS \n");


	prvSetupHardware();

	 /* Create the first task at priority 2. The task parameter is not used 
	 and set to NULL.  */
	

	 /* Create the second task at priority 1 - which is lower than the priority
	 given to Task 1. Again the task parameter is not used so is set to NULL */



	 printf("The two tasks are created now \n");


	 /* Start the scheduler so the tasks start executing. */
	 vTaskStartScheduler(); 
	 
	 /* If all is well then main() will never reach here as the scheduler will 
	 now be running the tasks. If main() does reach here then it is likely there
	 was insufficient heap memory available for the idle task to be created. 
	 Chapter 2 provides more information on heap memory management. */
	
	 for( ;; );
 	return 0;
}


/*-----------------------------------------------------------*/

void vTask1( void *pvParameters )
{

}
// /*-----------------------------------------------------------*/

void vTask2( void *pvParameters )
{

}

