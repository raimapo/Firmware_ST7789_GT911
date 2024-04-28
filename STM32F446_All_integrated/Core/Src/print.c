#include "print.h"

/***** Thread safe print, but maybe not ************/
static int inHandlerMode (void) // If in interruption __get_IPSR() return 1, Otherwise return to 0
{
   return __get_IPSR();  
}

void print_usart1(char const *format, ...)
{ 
	char buf[64];
	if(inHandlerMode() != 0)
	{
		taskDISABLE_INTERRUPTS();
	}
	else
	{
		while(HAL_UART_GetState(&huart3) == HAL_UART_STATE_BUSY_TX)// If the serial port is busy, suspend this task 
		taskYIELD();
	}
	va_list ap;
	va_start(ap, format);
	vsprintf(buf, format, ap);
	HAL_UART_Transmit(&huart3, (uint8_t *)buf, strlen(buf), 100);
	va_end(ap);
	if(inHandlerMode() != 0)
	taskENABLE_INTERRUPTS();

}
/****************************************/

#define DEBUG_BUFFER_SIZE    (256)
#define DEBUG_TIMEOUT        (1000)

osSemaphoreId DEBUG_TX_completeID;
osSemaphoreDef(DEBUG_TX_complete);
uint8_t DEBUG_TX_Buffer[DEBUG_BUFFER_SIZE] = {0};  //!< Debug buffer.

bool DEBUG_Init(void)
{
    if ((DEBUG_TX_completeID = osSemaphoreCreate(osSemaphore(DEBUG_TX_complete), 1)) == NULL)
    {
        return false;
    }
    return true;
}

void DEBUG_Printf(const char *fmt, ...)
{
    uint16_t i = 0;
    va_list args;
    if (osSemaphoreWait(DEBUG_TX_completeID, 1000) == osOK)
    {
        va_start(args, fmt);
        i = vsnprintf((char*) DEBUG_TX_Buffer, DEBUG_BUFFER_SIZE - 1, fmt, args);
        DEBUG_TX_Buffer[i] = 0x00;

        uint16_t retry = 4096;

        while ((retry--)&&(HAL_UART_Transmit(&huart3, &DEBUG_TX_Buffer[0], strlen((char*)&DEBUG_TX_Buffer[0]), 0xFFF) != HAL_OK));

        va_end(args);
        osSemaphoreRelease(DEBUG_TX_completeID);
    }
    return;
}
