
#ifndef INC_STM32F407_GPIO_H_
#define INC_STM32F407_GPIO_H_


#include <stm32f407.h>



typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;					/* Possible values from @GPIO_PIN_MODES */
	uint8_t GPIO_PinSpeed;					/* Possible values from @GPIO_PIN_SPEED */
	uint8_t GPIO_PinPupdControl;			/* Possible values from @GPIO_PIN_PUPD */
	uint8_t GPIO_PinOPType;					/* Possible values from @GPIO_PIN_OPTYPE */
	uint8_t GPIO_PinAltFunMode;				/* Possible values from @GPIO_PIN_ALTFUN_MODES */
}GPIOx_PinConfig_t;

typedef struct
{

	GPIOx_reg *pGPIOx;						/* This holds the base address of the GPIO port to which the pin belongs */
	GPIOx_PinConfig_t GPIO_PinConfig;		/* This holds the configuration of the GPIO port pin */

}GPIO_handle_t;

/* @GPIO_PIN_NOS
 * GPIO Pin Possible Numbers
 */

#define GPIO_PIN_NO_0			0
#define GPIO_PIN_NO_1			1
#define GPIO_PIN_NO_2			2
#define GPIO_PIN_NO_3			3
#define GPIO_PIN_NO_4			4
#define GPIO_PIN_NO_5			5
#define GPIO_PIN_NO_6			6
#define GPIO_PIN_NO_7			7
#define GPIO_PIN_NO_8			8
#define GPIO_PIN_NO_9			9
#define GPIO_PIN_NO_10			10
#define GPIO_PIN_NO_11			11
#define GPIO_PIN_NO_12			12
#define GPIO_PIN_NO_13			13
#define GPIO_PIN_NO_14			14
#define GPIO_PIN_NO_15			15

/* @GPIO_PIN_MODES
 * GPIO Pin Possible Modes
 */

#define GPIO_MODE_IN			0
#define GPIO_MODE_OUT			1
#define GPIO_MODE_ALT			2
#define GPIO_MODE_ANLG			3
#define GPIO_MODE_IT_FT			4
#define GPIO_MODE_IT_RT			5
#define GPIO_MODE_IT_RFT		6

/* @GPIO_PIN_OPTYPE
 * GPIO Output Mode Types
 */

#define GPIO_OP_TYPE_PP			0
#define GPIO_OP_TYPE_OD			1

/* @GPIO_PIN_SPEED
 * GPIO Possible output speed
 */

#define GPIO_OP_SP_LOW			0
#define GPIO_OP_SP_MED			1
#define GPIO_OP_SP_HI			2
#define GPIO_OP_SP_VHI			3

/* @GPIO_PIN_PUPD
 * Pull-Up AND Pull-Down Config.
 */

#define GPIO_NO_PUPD			0
#define GPIO_PU					1
#define GPIO_PD					2

/* @GPIO_PIN_ALTFUN_MODES
 * Alt. Functionality Modes
 */

#define GPIO_ALT_FUN_MODE_0		0
#define GPIO_ALT_FUN_MODE_1		1
#define GPIO_ALT_FUN_MODE_2		2
#define GPIO_ALT_FUN_MODE_3		3
#define GPIO_ALT_FUN_MODE_4		4
#define GPIO_ALT_FUN_MODE_5		5
#define GPIO_ALT_FUN_MODE_6		6
#define GPIO_ALT_FUN_MODE_7		7
#define GPIO_ALT_FUN_MODE_8		8
#define GPIO_ALT_FUN_MODE_9		9
#define GPIO_ALT_FUN_MODE_10	10
#define GPIO_ALT_FUN_MODE_11	11
#define GPIO_ALT_FUN_MODE_12	12
#define GPIO_ALT_FUN_MODE_13	13
#define GPIO_ALT_FUN_MODE_14	14
#define GPIO_ALT_FUN_MODE_15	15


/*
 * Peripheral Clock Setup
 */
void GPIO_PeriClockControl(GPIOx_reg *pGPIOx, uint8_t EnorDi);

/*
 * Init De-init
 */
void GPIO_Init(GPIO_handle_t* pGPIO_handle_t);
void GPIO_DeInit(GPIOx_reg *pGPIOx);

/*
 * Read-Write to Pin-Port
 */
uint8_t GPIO_ReadFromInputPin(GPIOx_reg *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIOx_reg *pGPIOx);
void GPIO_WriteToOutputPin(GPIOx_reg *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIOx_reg *pGPIOx, uint16_t Value);
void GPIO_TogleOutputPin(GPIOx_reg *pGPIOx, uint8_t PinNumber);

/*
 * IRQ Config-Handling
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);

#endif /* INC_STM32F407_GPIO_H_ */
