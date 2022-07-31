#include <string.h>
#include <stdio.h>
#include "main.h"
#include "zmod4510.h"

static uint8_t zmod4510_get_float (UART_HandleTypeDef *uart, char *cmd, float *fl)
{
    uint8_t i, temp[10], rxgood=0;

    // Get a float value
    if (HAL_UART_GetState(uart) != HAL_UART_STATE_READY)
        return 1;

    // Check 10 times if cmd can be sent and response can be read out
    for (i=0; i<10; i++)
    {
        HAL_UART_Transmit (uart, (uint8_t *)cmd, 3, 100);
        memset (temp, 0, 10);
        HAL_UART_Receive (uart, temp, 9, 100);
        
        if (temp[1] == '\n')
        {
            HAL_Delay (50);
            continue;
        }
        
        sscanf ((char *) temp, "%f\n", fl);
        rxgood = 1;
        break;
    }

    return rxgood;
}

uint8_t zmod4510_setup (UART_HandleTypeDef *uart, uint8_t ss)
{
    uint8_t ret, str[10];

    if (ss > 99)
        return 2;
    
    // Check 10 times if ID can be read out
    ret = zmod4510_get_id (uart, str);
    if (ret != 1)
        return ret;
    
    // Skip SS setting if set to 0
    if (ss == 0)
        return 1;

    // Set stabilization samples if non-zero
    sprintf ((char *) str, "SS%02d\n", ss);
    HAL_UART_Transmit (uart, str, 5, 100);
    HAL_UART_Receive (uart, str, 2, 100);
    if ((str[0] == 'S') && (str[1] == '\n'))
        return 1;
    else
        return 0;
}

uint8_t zmod4510_activate (UART_HandleTypeDef *uart, uint8_t power)
{
	uint8_t str[5];

    // Power up or power down the sensor
    if (power == 0)
        HAL_UART_Transmit (uart, (uint8_t *)"PD\n", 3, 100);
    else
        HAL_UART_Transmit (uart, (uint8_t *)"PU\n", 3, 100);

    HAL_UART_Receive (uart, str, 2, 100);
    if ((str[0] == 'S') && (str[1] == '\n'))
        return 1;
    else
        return 0;
}

uint8_t zmod4510_get_aqi (UART_HandleTypeDef *uart, float *aqi)
{
    // Get AQI as float
    return zmod4510_get_float (uart, "AQ\n", aqi);
}

uint8_t zmod4510_get_no2 (UART_HandleTypeDef *uart, float *no2)
{
    // Get NO2 as float
    return zmod4510_get_float (uart, "NO\n", no2);
}

uint8_t zmod4510_get_o3 (UART_HandleTypeDef *uart, float *o3)
{
    // Get O3 as float
    return zmod4510_get_float (uart, "O3\n", o3);
}

// id[] should at least have 8 bytes for 8-character ASCII ID
uint8_t zmod4510_get_id (UART_HandleTypeDef *uart, uint8_t id[])
{
    // Get ID in an array
    uint8_t i, temp[10], rxgood=0;
    memset (temp, 0, 10);

    if (HAL_UART_GetState(uart) != HAL_UART_STATE_READY)
        return 1;

    // Check 10 times if ID can be read out
    for (i=0; i<10; i++)
    {
        HAL_UART_Transmit (uart, (uint8_t *)"ID\n", 3, 100);
        HAL_UART_Receive (uart, temp, 9, 100);
        if (temp[8] == '\n')
        {
            memcpy (id, temp, 8);
            rxgood = 1;
            break;
        }
        if (temp[1] == '\n')
            continue;

        HAL_Delay (50);
    }

    return rxgood;
}
