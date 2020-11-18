#ifndef INC_STM32F407_SPI_H_
#define INC_STM32F407_SPI_H_

#include <stm32f407.h>

/* > Device Mode */
#define SPI_DEVICE_MODE_MASTER 				1
#define SPI_DEVICE_MODE_SLAVE 				0

/* > Comm. Type/Bus Co */
#define SPI_BUS_CONFIG_FULLD				0
#define SPI_BUS_CONFIG_HALFD				1
#define SPI_BUS_CONFIG_S_RX				2

/* > Data Frame Format */
#define SPI_DFF_BYTE					0
#define SPI_DFF_WORD					1


/* > Edge select for data transfer */
#define SPI_CPHA_RESET					RESET
#define SPI_CPHA_SET					SET

/* > Idle state select */
#define SPI_CPOL_RESET					RESET
#define SPI_CPOL_SET					SET

/* Software Slave enable */
#define SPI_SSM_DISABLE					DISABLE
#define SPI_SSM_ENABLE					ENABLE

/* Internal Slave select */
#define SPI_SSI_DISABLE					DISABLE
#define SPI_SSI_ENABLE					ENABLE

/* SCLK Speed */
#define SPI_SPEED_DIV_2					0
#define SPI_SPEED_DIV_4					1
#define SPI_SPEED_DIV_8					2
#define SPI_SPEED_DIV_16				3
#define SPI_SPEED_DIV_32				4
#define SPI_SPEED_DIV_64				5
#define SPI_SPEED_DIV_128				6
#define SPI_SPEED_DIV_256				7


typedef struct{
	uint8_t	SPI_DeviceMode;
	uint8_t	SPI_BusConfig;
	uint8_t SPI_SCLKSpeed;
	uint8_t	SPI_DFF;
	uint8_t	SPI_CPOL;
	uint8_t	SPI_CPHA;
	uint8_t	SPI_SSM;
}SPI_Config_t;

typedef struct{
	SPI_Config_t SPI_Config;
	SPIx_reg	*pSPIx_reg;

}SPI_Handle_t;


/*
 * Peripheral Clock Setup
 */
void SPI_PeriClockControl(SPIx_reg *pSPIx_reg, uint8_t EnorDi);

/*
 * Init and De-Init
 */
void SPI_Init(SPI_Handle_t *pSPI_Handle);
void SPI_DeInit(SPIx_reg *pSPIx_reg);

/*
 * Data Send and Receive
 */
void SPI_Send(SPIx_reg *pSPIx_reg, uint8_t *pTxBuffer, uint32_t Len);
void SPI_Receive(SPIx_reg *pSPIx_reg, uint8_t *pRxBuffer, uint32_t Len);

/*
 * Other Peripheral Control APIs
 */
void SPI_PeripheralControl(SPIx_reg *pSPIx_reg, uint8_t EnorDi);

/*
 * IRQ config.
 */
void SPI_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void SPI_IRQHandling(SPI_Handle_t *pHandle);

#endif /* INC_STM32F407_SPI_H_ */
