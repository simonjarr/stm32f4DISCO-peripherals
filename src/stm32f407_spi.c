/*
 * stm32f407xx_spi_driver.c
 *
 *  Created on: Oct 29, 2020
 *      Author: goktugsaray
 */

#include "stm32f407_spi.h"

/*
 * @fn				- SPI_PeriClockControl
 *
 * @brief			- This function enables or disabled peripheral clock for the given SPI
 *
 * @param[i]		- Base address of the SPI peripheral
 * @param[i]		- ENABLE or DISABLE macros
 *
 * @return			- none
 *
 * @Note			- none
 *
 */
void SPI_PeriClockControl(SPIx_reg *pSPIx_reg, uint8_t EnorDi)
{
	if(EnorDi)
	{
		if(pSPIx_reg == SPI_1)
		{
			SPI1_PCLK_EN();
		}else if(pSPIx_reg == SPI_2)
		{
			SPI2_PCLK_EN();
		}else
		{
			SPI3_PCLK_EN();
		}

	}else
	{
		if(pSPIx_reg == SPI_1)
		{
			SPI1_PCLK_DI();
		}else if(pSPIx_reg == SPI_2)
		{
			SPI2_PCLK_DI();
		}else
		{
			SPI3_PCLK_DI();
		}
	}
}

/*
 * @fn				- SPI_Init
 *
 * @brief			- This function initilizes the SPIx peripheral
 *
 * @param[i]		- SPI Handler
 *
 * @return			- none
 *
 * @Note			- none
 *
 */
void SPI_Init(SPI_Handle_t *pSPI_Handle)
{
	uint32_t temp;

	// Enable SPI Peripheral Clock
	SPI_PeriClockControl(pSPI_Handle->pSPIx_reg, ENABLE);

	/* Device Mode */
	temp = (pSPI_Handle->SPI_Config.SPI_DeviceMode << SPI_CR1_MSTR);
	pSPI_Handle->pSPIx_reg->CR1 |= temp;
	temp = (pSPI_Handle->SPI_Config.SPI_DeviceMode << SPI_CR1_SSI);
	pSPI_Handle->pSPIx_reg->CR1 |= temp;


	/* Bus Config*/
	if(pSPI_Handle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_FULLD)
	{
		pSPI_Handle->pSPIx_reg->CR1 &= ~(1 << SPI_CR1_BIDIMODE);

	}else if(pSPI_Handle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_HALFD)
	{
		pSPI_Handle->pSPIx_reg->CR1 |= (1 << SPI_CR1_BIDIOE);

	}else
	{
		pSPI_Handle->pSPIx_reg->CR1 &= ~(1 << SPI_CR1_BIDIMODE);
		pSPI_Handle->pSPIx_reg->CR1 |= (1 << SPI_CR1_RXONLY);

	}

	/* SCLK Speed */
	temp = (pSPI_Handle->SPI_Config.SPI_SCLKSpeed << SPI_CR1_BR);
	pSPI_Handle->pSPIx_reg->CR1 |= temp;

	/* DFF */
	temp = (pSPI_Handle->SPI_Config.SPI_DFF << SPI_CR1_DFF);
	pSPI_Handle->pSPIx_reg->CR1 |= temp;

	/* CPOL */
	temp = (pSPI_Handle->SPI_Config.SPI_CPOL << SPI_CR1_CPOL);
	pSPI_Handle->pSPIx_reg->CR1 |= temp;

	/* CPHA*/
	temp = (pSPI_Handle->SPI_Config.SPI_CPHA << SPI_CR1_CPHA);
	pSPI_Handle->pSPIx_reg->CR1 |= temp;

	/* SSM */
	temp = (pSPI_Handle->SPI_Config.SPI_SSM << SPI_CR1_SSM);
	pSPI_Handle->pSPIx_reg->CR1 |= temp;

}

/*
 * @fn				- SPI_DeInit
 *
 * @brief			- This function de-initilizes the SPIx peripheral
 *
 * @param[i]		- SPI Base Register
 *
 * @return			- none
 *
 * @Note			- none
 *
 */
void SPI_DeInit(SPIx_reg *pSPIx_reg)
{
	if(pSPIx_reg == SPI_1)
	{
		GPIOA_PCLK_RESET();

	}else if(pSPIx_reg == SPI_2)
	{
		SPI2_PCLK_RESET();

	}else if(pSPIx_reg == SPI_3)
	{
		SPI3_PCLK_RESET();
	}

	// DISABLE SPI Peripheral Clock
	SPI_PeriClockControl(pSPIx_reg, DISABLE);

}

/*
 * @fn				- SPI_Send
 *
 * @brief			- This function sends data from pTxBuffer of length Len
 *
 * @param[i]		- SPI Base Register
 *
 * @param[i]		- Data to be sent
 *
 * @param[i]		- Length of data
 *
 * @return			- none
 *
 * @Note			- Please note that this is a blocking function
 *
 */
void SPI_Send(SPIx_reg *pSPIx_reg, uint8_t *pTxBuffer, uint32_t Len)
{
	while(Len>0)
	{
		while(!(pSPIx_reg->SR & (1 << 1))); // wait for buffer clear

		if((pSPIx_reg->CR1 >> SPI_CR1_DFF) & 0x00000001)
		{
			// 16 bit
			pSPIx_reg->DR = *((uint16_t*)pTxBuffer);
			Len--;
			(uint16_t*)pTxBuffer++;
		}else
		{
			// 8 bit
			pSPIx_reg->DR = *pTxBuffer;
			pTxBuffer++;
		}

		Len--;
	}

}

/*
 * @fn				- SPI_Receive
 *
 * @brief			- This function receives data of length Len
 *
 * @param[i]		- SPI Base Register
 *
 * @param[i]		- Pointer to hold the data
 *
 * @param[i]		- Length of data
 *
 * @return			- none
 *
 * @Note			- Please note that this is a blocking function
 *
 */
void SPI_Receive(SPIx_reg *pSPIx_reg, uint8_t *pRxBuffer, uint32_t Len)
{
	while(Len>0)
	{
		while(!(pSPIx_reg->SR & (1 << 0))); // wait for buffer clear

		if((pSPIx_reg->CR1 >> SPI_CR1_DFF) & 0x00000001)
		{
			// 16 bit
			*((uint16_t*)pRxBuffer) = pSPIx_reg->DR;
			Len--;
			(uint16_t*)pRxBuffer++;
		}else
		{
			// 8 bit
			*pRxBuffer = pSPIx_reg->DR;
			pRxBuffer++;
		}

		Len--;
	}

}

/*
 * @fn				- SPI_PeripheralControl
 *
 * @brief			- This function enables or disables the peripheral
 *
 * @param[i]		- SPI Base Register
 *
 * @param[i]		- Enable or Disable
 *
 * @return			- none
 *
 * @Note			-
 *
 */
void SPI_PeripheralControl(SPIx_reg *pSPIx_reg, uint8_t EnorDi)
{
	pSPIx_reg->CR1 &= ~(1 << SPI_CR1_SPE);
	pSPIx_reg->CR1 |= (EnorDi << SPI_CR1_SPE);
}
