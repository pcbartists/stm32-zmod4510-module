#ifndef _ZMOD4510_H_
#define _ZMOD4510_H_

// Failure modes
#define 	ZMOD_OK			1
#define 	ZMOD_TIMEOUT	0
#define 	ZMOD_PARAM_ERR	2

#define 	ZMOD_ERR_CHECK(x,y) 	if(x!=ZMOD_OK)y()

/*
  Function:     Test if ZMOD4510 module is connected, set stabilization sample count
  Arguments:    uart:		UART_HandleTypeDef pointer to UART port where ZMOD4510 is connected
  	  	  	  	ss:			Stabilization sample count, set to 0 to leave at default
  Return:       ZMOD_OK on success, failure codes on failure
  Notes:        - Stabilization sample count must be set to a number between 1 and 99. 0 means no change.
                - After power-up or reset, ss should only be set once. Subsequent calls should pass ss = 0
*/
uint8_t zmod4510_setup (UART_HandleTypeDef *uart, uint8_t ss);

/*
  Function:     Get unique ID value from the ZMOD4510 module
  Arguments:    uart:		UART_HandleTypeDef pointer to UART port where ZMOD4510 is connected
  	  	  	  	id:			Pointer to array with at least 9 characters, returns NULL terminated ID string
  Return:       ZMOD_OK on success, failure codes on failure
  Notes:        -
*/
uint8_t zmod4510_get_id (UART_HandleTypeDef *uart, uint8_t id[]);

/*
  Function:     Send power=up or power-down command to the ZMOD4510 module
  Arguments:    uart:		UART_HandleTypeDef pointer to UART port where ZMOD4510 is connected
  	  	  	  	power:		0 = power down module, 1 = power up module
  Return:       ZMOD_OK on success, failure codes on failure
  Notes:        -
*/
uint8_t zmod4510_activate (UART_HandleTypeDef *uart, uint8_t power);

/*
  Function:     Get AQI value from the ZMOD4510 module
  Arguments:    uart:		UART_HandleTypeDef pointer to UART port where ZMOD4510 is connected
  	  	  	  	aqi:		Pointer to float for reading AQI value
  Return:       ZMOD_OK on success, failure codes on failure
  Notes:        - Refreshed every 30 seconds if module is powered up
*/
uint8_t zmod4510_get_aqi (UART_HandleTypeDef *uart, float *aqi);

/*
  Function:     Get NO2 value from the ZMOD4510 module (in ppb)
  Arguments:    uart:		UART_HandleTypeDef pointer to UART port where ZMOD4510 is connected
  	  	  	  	no2:		Pointer to float for reading NO2 value
  Return:       ZMOD_OK on success, failure codes on failure
  Notes:        - Refreshed every 30 seconds if module is powered up
*/
uint8_t zmod4510_get_no2 (UART_HandleTypeDef *uart, float *no2);

/*
  Function:     Get O3 value from the ZMOD4510 module
  Arguments:    uart:		UART_HandleTypeDef pointer to UART port where ZMOD4510 is connected
  	  	  	  	o3:			Pointer to float for reading O3 value
  Return:       ZMOD_OK on success, failure codes on failure
  Notes:        - Refreshed every 30 seconds if module is powered up
*/
uint8_t zmod4510_get_o3 (UART_HandleTypeDef *uart, float *o3);

#endif
