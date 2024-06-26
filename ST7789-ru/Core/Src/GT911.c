
#include "GT911.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c1;
extern void *	 memset (void *, int, size_t);

uint8_t GTDMAReadOK_F = 0;
uint8_t GTDMASendOK_F = 0;
uint8_t DMAbuf[41];
uint8_t GT911buf[41];
uint16_t IICError = 0;
GT911_Dev Dev_Now,Dev_Backup;

extern void HAL_Delay(uint32_t Delay);
extern osStatus osDelay (uint32_t millisec);
/*
  * @brief  IIC
  * @param  None
  * @retval None
 */
static void i2c_hw_reset(void) {

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_SET);

    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_RESET ||
        HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == GPIO_PIN_RESET) {

    }

    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    hi2c1.Instance->CR1 |= I2C_CR1_SWRST;
    hi2c1.Instance->CR1 &= ~I2C_CR1_SWRST;
	HAL_I2C_DeInit(&hi2c1);
	HAL_I2C_Init(&hi2c1);
}

/*
  * @brief  GT911 Init
  * @param  None
  * @retval None
 */
void GT911_init()
{
	Dev_Now.GT911_RST=0;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.Pin = GT911_RST_PIN | GT911_INT_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GT911_RST_PORT, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(GT911_RST_PORT,GT911_RST_PIN,GPIO_PIN_RESET);    
	osDelay(1000);
	HAL_GPIO_WritePin(GT911_INT_PORT,GT911_INT_PIN,GPIO_PIN_RESET);    
	osDelay(1000);
	HAL_GPIO_WritePin(GT911_RST_PORT,GT911_RST_PIN,GPIO_PIN_SET);    
	osDelay(2000);
	
	GPIO_InitStruct.Pin = GT911_INT_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GT911_INT_PORT, &GPIO_InitStruct);
	
	osDelay(100);
	Dev_Now.GT911_RST=1;
}


/*
  * @brief  IIC Reset
  * @param  None
  * @retval None
 */
void IICReset(void)
{
	SET_BIT(hi2c1.Instance->CR1, I2C_CR1_STOP);
	hi2c1.State = HAL_I2C_STATE_READY;
	hi2c1.Mode = HAL_I2C_MODE_NONE;
	i2c_hw_reset();
	IICError ++;
}

#define regNum	41
void GT911_Scan(void)
{
	uint8_t Clearbuf = 0;
	uint8_t i = 0;

	if (Dev_Now.Touch == 1)
	{
		Dev_Now.Touch = 0;
		if(GTDMASendOK_F)
		{
			GTDMASendOK_F = 0;
			if(HAL_I2C_Mem_Read_DMA(&hi2c1, CT_CMD_WR, GT911_READ_XY_REG, I2C_MEMADD_SIZE_16BIT, DMAbuf, regNum))
			{
				IICReset();
				return;
			}
		}
		else
		{
			if(HAL_I2C_Mem_Write_DMA(&hi2c1, CT_CMD_WR, GT911_READ_XY_REG, I2C_MEMADD_SIZE_16BIT, &Clearbuf, 1))
			{
				IICReset();
				return;
			}
		}
	}

	if(GTDMAReadOK_F)
	{
		GTDMAReadOK_F = 0;
		if ((GT911buf[0]&0x80) == 0x00)
		{
			if(HAL_I2C_Mem_Write_DMA(&hi2c1, CT_CMD_WR, GT911_READ_XY_REG, I2C_MEMADD_SIZE_16BIT, &Clearbuf, 1))
			{
				IICReset();
				return;
			}
		}
		else
		{
			Dev_Now.TouchpointFlag = GT911buf[0];
			Dev_Now.TouchCount = GT911buf[0]&0x0f;

			if(HAL_I2C_Mem_Write_DMA(&hi2c1, CT_CMD_WR, GT911_READ_XY_REG, I2C_MEMADD_SIZE_16BIT, &Clearbuf, 1))
			{
				IICReset();
				return;
			}
			Dev_Now.Touchkeytrackid[0] = GT911buf[1];
			Dev_Now.X[0] = ((uint16_t)GT911buf[3] << 8) + GT911buf[2];
			Dev_Now.Y[0] = ((uint16_t)GT911buf[5] << 8) + GT911buf[4];
			Dev_Now.S[0] = ((uint16_t)GT911buf[7] << 8) + GT911buf[6];

			Dev_Now.Touchkeytrackid[1] = GT911buf[9];
			Dev_Now.X[1] = ((uint16_t)GT911buf[11] << 8) + GT911buf[10];
			Dev_Now.Y[1] = ((uint16_t)GT911buf[13] << 8) + GT911buf[12];
			Dev_Now.S[1] = ((uint16_t)GT911buf[15] << 8) + GT911buf[14];

			Dev_Now.Touchkeytrackid[2] = GT911buf[17];
			Dev_Now.X[2] = ((uint16_t)GT911buf[19] << 8) + GT911buf[18];
			Dev_Now.Y[2] = ((uint16_t)GT911buf[21] << 8) + GT911buf[20];
			Dev_Now.S[2] = ((uint16_t)GT911buf[23] << 8) + GT911buf[22];

			Dev_Now.Touchkeytrackid[3] = GT911buf[25];
			Dev_Now.X[3] = ((uint16_t)GT911buf[27] << 8) + GT911buf[26];
			Dev_Now.Y[3] = ((uint16_t)GT911buf[29] << 8) + GT911buf[28];
			Dev_Now.S[3] = ((uint16_t)GT911buf[31] << 8) + GT911buf[30];

			Dev_Now.Touchkeytrackid[4] = GT911buf[33];
			Dev_Now.X[4] = ((uint16_t)GT911buf[35] << 8) + GT911buf[34];
			Dev_Now.Y[4] = ((uint16_t)GT911buf[37] << 8) + GT911buf[36];
			Dev_Now.S[4] = ((uint16_t)GT911buf[39] << 8) + GT911buf[38];

			for (i = 0; i< Dev_Backup.TouchCount;i++)
			{
				if(Dev_Now.Y[i]<20)Dev_Now.Y[i]=20;
				if(Dev_Now.Y[i]>GT911_MAX_HEIGHT-20)Dev_Now.Y[i]=GT911_MAX_HEIGHT-20;
				if(Dev_Now.X[i]<20)Dev_Now.X[i]=20;
				if(Dev_Now.X[i]>GT911_MAX_WIDTH-20)Dev_Now.X[i]=GT911_MAX_WIDTH-20;
			}
			for (i=0;i<Dev_Now.TouchCount;i++)
			{
				if(Dev_Now.Y[i]<20)Dev_Now.Y[i]=20;
				if(Dev_Now.Y[i]>GT911_MAX_HEIGHT-20)Dev_Now.Y[i]=GT911_MAX_HEIGHT-20;
				if(Dev_Now.X[i]<20)Dev_Now.X[i]=20;
				if(Dev_Now.X[i]>GT911_MAX_WIDTH-20)Dev_Now.X[i]=GT911_MAX_WIDTH-20;

				Dev_Backup.X[i] = Dev_Now.X[i];
				Dev_Backup.Y[i] = Dev_Now.Y[i];
				Dev_Backup.TouchCount = Dev_Now.TouchCount;
			}

			DEBUG_Printf("%d\n%d\n%d\n\n", Dev_Now.X[0], Dev_Now.Y[0], Dev_Now.S[0]);


		}
	}
}

