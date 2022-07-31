#include "main.h"
#include "user_main.h"
#include "zmod4510.h"

extern UART_HandleTypeDef huart1;
float aqi, no2, o3;

void user_main (void)
{
    uint8_t id[10];
    
    ZMOD_ERR_CHECK (zmod4510_setup (&huart1, 60), Error_Handler);
    ZMOD_ERR_CHECK (zmod4510_get_id (&huart1, id), Error_Handler);
    ZMOD_ERR_CHECK (zmod4510_activate (&huart1, 1), Error_Handler);

    while (1)
    {
    	ZMOD_ERR_CHECK (zmod4510_get_aqi (&huart1, &aqi), Error_Handler);
    	ZMOD_ERR_CHECK (zmod4510_get_no2 (&huart1, &no2), Error_Handler);
    	ZMOD_ERR_CHECK (zmod4510_get_o3 (&huart1, &o3), Error_Handler);
    	HAL_Delay (5000);
    }
}
