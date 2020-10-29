/*
 * stm32f407xx_spi_driver.h
 *
 *  Created on: Oct 29, 2020
 *      Author: goktugsaray
 */

#ifndef INC_STM32F407_SPI_H_
#define INC_STM32F407_SPI_H_

#include <stm32f407.h>

/* > Device Mode */
#define SPI_DEVICE_MODE_MASTER 		0
#define SPI_DEVICE_MODE_SLAVE 		1


/* > Data Frame Format */
#define SPI_DFF_BYTE					0
#define SPI_DFF_WORD					0

typedef struct{
	uint8_t	SPI_DeviceMode;
	uint8_t	SPI_BusConfig;
	uint8_t	SPI_DFF;
	uint8_t	SPI_CPOL;
	uint8_t	SPI_CPHA;
	uint8_t	SPI_SSM;
}SPI_Config_t;

typedef struct{
	SPIx_reg	*pSPIx_reg;

}SPI_Handle_t;

#endif /* INC_STM32F407_SPI_H_ */
