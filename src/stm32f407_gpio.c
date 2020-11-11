
#include <stm32f407_gpio.h>


/*
 * @fn				- GPIO_PeriClockControl
 *
 * @brief			- This function enables or disabled peripheral clock for the given GPIO port
 *
 * @param[i]		- Base address of the gpio peripheral
 * @param[i]		- ENABLE or DISABLE macros
 *
 * @return			- none
 *
 * @Note			- none
 *
 */
void GPIO_PeriClockControl(GPIOx_reg *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_PCLK_EN();
		}
	}
	else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DI();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_DI();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_PCLK_DI();
		}

	}
}

/*
 * @fn				- GPIO_Init
 *
 * @brief			- This function initilizes the given GPIO port structure
 *
 * @param[i]		- GPIO Handler
 *
 * @return			- none
 *
 * @Note			- none
 *
 */
void GPIO_Init(GPIO_handle_t* pGPIO_handle_t)
{
	uint32_t temp = 0;

	// 1. Configure the mode

	if(pGPIO_handle_t->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANLG)
	{
		temp = ( pGPIO_handle_t->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber) );
		pGPIO_handle_t->pGPIOx->MODER &= ~(3 << (2 * pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber) );
		pGPIO_handle_t->pGPIOx->MODER |= temp;

	}
	else // IRQ
	{
		if(pGPIO_handle_t->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			EXTI->FTSR |= (1 << pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR &= ~(1 << pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber);

		}else if(pGPIO_handle_t->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			EXTI->RTSR |= (1 << pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR &= ~(1 << pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber);
		}else if(pGPIO_handle_t->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			EXTI->FTSR |= (1 << pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR |= (1 << pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber);
		}

		SYSCFG_PCLK_EN();

		int temp1 = pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber / 4;
		int temp2 = pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber % 4;
		int port = GPIO_PORT_INTO_CODE(pGPIO_handle_t->pGPIOx);


		SYSCFG->EXTICR[temp1] = (port << temp2 * 4);

		EXTI->IMR |= 0x1;
	}

	temp = 0;

	// 2. Configure the speed

	temp = ( pGPIO_handle_t->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIO_handle_t->pGPIOx->OSPEEDR &= ~(3 << (2 * pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIO_handle_t->pGPIOx->OSPEEDR |= temp;

	//3. configure the pupd settings

	temp = ( pGPIO_handle_t->GPIO_PinConfig.GPIO_PinPupdControl << (2 * pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIO_handle_t->pGPIOx->PUPDR &= ~(3 << (2 * pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIO_handle_t->pGPIOx->PUPDR |= temp;

	//4. Configure output type

	temp = ( pGPIO_handle_t->GPIO_PinConfig.GPIO_PinOPType << (pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIO_handle_t->pGPIOx->OTYPER &= ~(1 << (2 * pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIO_handle_t->pGPIOx->OTYPER |= temp;

	//5. Configure alternate functionality mode

	if(pGPIO_handle_t->GPIO_PinConfig.GPIO_PinAltFunMode == GPIO_MODE_ALT)
	{
		uint8_t temp1, temp2;
		temp1 = pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber % 8;
		temp = ( pGPIO_handle_t->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber) );
		pGPIO_handle_t->pGPIOx->AFR[temp1] &= ~(15 << (2 * pGPIO_handle_t->GPIO_PinConfig.GPIO_PinNumber) );
		pGPIO_handle_t->pGPIOx->AFR[temp1] |= temp;
	}

}

/*
 * @fn				- GPIO_DeInit
 *
 * @brief			- This function de-initilizes the given GPIO port structure
 *
 * @param[i]		- GPIO Handler
 *
 * @return			- none
 *
 * @Note			- none
 *
 */
void GPIO_DeInit(GPIOx_reg *pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_PCLK_RESET();
	}else if(pGPIOx == GPIOB)
	{
		GPIOB_PCLK_RESET();
	}else if(pGPIOx == GPIOC)
	{
		GPIOC_PCLK_RESET();
	}else if(pGPIOx == GPIOD)
	{
		GPIOD_PCLK_RESET();
	}else if(pGPIOx == GPIOE)
	{
		GPIOE_PCLK_RESET();
	}else if(pGPIOx == GPIOF)
	{
		GPIOF_PCLK_RESET();
	}else if(pGPIOx == GPIOG)
	{
		GPIOG_PCLK_RESET();
	}else if(pGPIOx == GPIOH)
	{
		GPIOH_PCLK_RESET();
	}else if(pGPIOx == GPIOI)
	{
		GPIOI_PCLK_RESET();
	}

}

/*
 * @fn				- GPIO_ReadFromInputPin
 *
 * @brief			- This function returns the pin signal
 *
 * @param[i]		- GPIO port base address
 * @param[i]		- Pin number
 *
 * @return			- return the read value
 *
 * @Note			- none
 *
 */
uint8_t GPIO_ReadFromInputPin(GPIOx_reg *pGPIOx, uint8_t PinNumber)
{
	return (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
}

/*
 * @fn				- GPIO_ReadFromInputPort
 *
 * @brief			- This function returns the port pin signals
 *
 * @param[i]		- GPIO port base address
 *
 * @return			- return the read value
 *
 * @Note			- none
 *
 */
uint16_t GPIO_ReadFromInputPort(GPIOx_reg *pGPIOx)
{
	return (uint16_t)(pGPIOx->IDR);
}

/*
 * @fn				- GPIO_WriteToOutputPin
 *
 * @brief			- This function writes to pin
 *
 * @param[i]		- GPIO port base address
 * @param[i]		- GPIO port pin number
 * @param[i]		- GPIO port pin value
 *
 * @return			- none
 *
 * @Note			- none
 *
 */
void GPIO_WriteToOutputPin(GPIOx_reg *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	pGPIOx->ODR &= ~( 1 << PinNumber );
	pGPIOx->ODR |= ( 1 << PinNumber );
}

/*
 * @fn				- GPIO_WriteToOutputPort
 *
 * @brief			- This function writes to port
 *
 * @param[i]		- GPIO port base address
 * @param[i]		- GPIO port pin value
 *
 * @return			- none
 *
 * @Note			- none
 *
 */
void GPIO_WriteToOutputPort(GPIOx_reg *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value;
}

/*
 * @fn				- GPIO_TogleOutputPin
 *
 * @brief			- This function toggles the pin
 *
 * @param[i]		- GPIO port base address
 * @param[i]		- GPIO port pin number
 *
 * @return			- none
 *
 * @Note			- none
 *
 */
void GPIO_TogleOutputPin(GPIOx_reg *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= ( 1 << PinNumber);
}

/*
 * @fn				- GPIO_IRQConfig
 *
 * @brief			- This function configures the IRQ
 *
 * @param[i]		- IRQ Number
 * @param[i]		- IRQ Priority
 * @param[i]		- Enable or Disable
 *
 * @return			- none
 *
 * @Note			- none
 *
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi)
{

	uint32_t _addr = IRQNumber / 32;
	uint32_t _bit = IRQNumber % 32;

	// enable interrupt
	if(EnorDi)
	{
		uint32_t *pISER = (uint32_t*)(NVIC_ISER + _addr * 4);
		*pISER |= (EnorDi << _bit);
	}
	else
	{
		uint32_t *pICER = (uint32_t*)(NVIC_ICER + _addr * 4);
		*pICER |= (EnorDi << _bit);
	}

	// configure priority
	_addr = IRQNumber / 4;
	_bit = IRQNumber % 4;

	uint32_t *pIPR = (uint32_t*)(NVIC_IPR + _addr * 4);
	*pIPR |= (IRQPriority << _bit);


}

/*
 * @fn				- GPIO_IRQHandling
 *
 * @brief			- This function handles IRQ
 *
 * @param[i]		- Pin number for IRQ
 *
 * @return			- none
 *
 * @Note			- none
 *
 */
void GPIO_IRQHandling(uint8_t PinNumber)
{
	if(EXTI->PR & (1 << PinNumber))
	{
		EXTI->PR |= (1 << PinNumber);
	}
}
