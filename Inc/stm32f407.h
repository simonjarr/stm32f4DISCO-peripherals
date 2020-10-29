/*
 * stm3f407xx.h
 *
 *  Created on: Oct 24, 2020
 *      Author: goktugsaray
 */

#ifndef INC_STM3F407XX_H_
#define INC_STM3F407XX_H_

#include <stdint.h>
#include <stdio.h>

/* Memory Definitions */

#define SRAM1_BASE					0x20000000U
#define SRAM1_SIZE					((112) * (1024))
#define SRAM2_BASE					((SRAM1_START) + (SRAM1_SIZE))
#define FLASH_BASE					0x08000000U
#define ROM_BASE					0x1FFF0000U

/* Peripheral Bases */

#define PERIPH_BASE					0x40000000U
#define APB1PERIPH_BASE				PERIPH_BASE
#define APB2PERIPH_BASE				0x40010000U
#define AHB1PERIPH_BASE				0x40020000U
#define AHB2PERIPH_BASE				0x50000000U

/* Other */

#define __vo 						volatile 					/* volatile keyword macro */
#define ENABLE						1
#define DISABLE						0
#define SET							ENABLE
#define RESET						DISABLE
#define GPIO_PIN_SET				SET
#define GPIO_PIN_RESET				RESET

/*
RCC
===================================================================
*/

#define RCC_BASE					0x40023800U 				/* RCC base addr. */

/* register structure */
typedef struct
{
	__vo uint32_t CR;				//	RCC clock control register 											+0x00
	__vo uint32_t PLLCFGR;			//	RCC PLL configuration register										+0x04
	__vo uint32_t CFGR;				//	RCC clock configuration register									+0x08
	__vo uint32_t CIR;				//	RCC clock interrupt register										+0x0C
	__vo uint32_t AHB1RSTR;			//	RCC AHB1 peripheral reset register									+0x10
	__vo uint32_t AHB2RSTR;			//	RCC AHB2 peripheral reset register									+0x14
	__vo uint32_t AHB3RSTR;			//	RCC AHB3 peripheral reset register									+0x18
	uint32_t reserved1;		//  reserved															+0x1C
	__vo uint32_t APB1RSTR;			//	RCC APB1 peripheral reset register									+0x20
	__vo uint32_t APB2RSTR;			//	RCC APB2 peripheral reset register									+0x24
	uint32_t reserved2;		//  reserved															+0x28
	uint32_t reserved3;		//  reserved															+0x2C
	__vo uint32_t AHB1ENR;			//	RCC AHB1 peripheral clock enable register							+0x30
	__vo uint32_t AHB2ENR;			//	RCC AHB2 peripheral clock enable register							+0x34
	__vo uint32_t AHB3ENR;			//	RCC AHB3 peripheral clock enable register							+0x38
	uint32_t reserved4;		//  reserved															+0x3C
	__vo uint32_t APB1ENR;			//	RCC APB1 peripheral clock enable register							+0x40
	__vo uint32_t APB2ENR;			//	RCC APB2 peripheral clock enable register							+0x44
	uint32_t reserved5;		//  reserved															+0x48
	uint32_t reserved6;		//  reserved															+0x4C
	__vo uint32_t AHB1LPENR;		//  RCC	AHB1 peripheral clock enable in low power mode register			+0x50
	__vo uint32_t AHB2LPENR;		//	RCC	AHB2 peripheral clock enable in low power mode register			+0x54
	__vo uint32_t AHB3LPENR;		//	RCC	AHB3 peripheral clock enable in low power mode register			+0x58
	uint32_t reserved7;		//  reserved															+0x5C
	__vo uint32_t APB1LPENR;		// 	RCC	APB1 peripheral clock enable in low power mode register			+0x60
	__vo uint32_t APB2LPENR;		//	RCC	APB2 peripheral clock enable in low power mode register			+0x64
	__vo uint32_t reserved8;		//  reserved															+0x68
	uint32_t reserved9;		//  reserved															+0x6C
	__vo uint32_t BDCR;				//	RCC	Backup domain control register									+0x70
	__vo uint32_t CSR;				//	RCC	Clock control and status register								+0x74
	uint32_t reserved10;		//  reserved															+0x78
	uint32_t reserved11;		//  reserved															+0x7C
	__vo uint32_t SSCGR;			//	RCC	spread spectrum clock generation register						+0x80
	__vo uint32_t PLLI2SCFGR;		//	RCC	PLLI2S configuration register									+0x84

} RCC_reg ;

#define RCC							((RCC_reg*)RCC_BASE)

/*
EXTI
===================================================================
*/
#define EXTI_BASE					(APB2PERIPH_BASE + 0x3C00)	/* EXTI base addr. */

/* register structure */
typedef struct
{
	__vo uint32_t IMR;				//	EXTI Interrupt mask register										+0x00
	__vo uint32_t RMR;				//	EXTI Event mask register											+0x04
	__vo uint32_t RTSR;				//	EXTI Rising trigger selection register								+0x08
	__vo uint32_t FTSR;				//	EXTI Falling trigger selection register								+0x0C
	__vo uint32_t SWIER;			//	EXTI Software interrupt event register								+0x10
	__vo uint32_t PR;				//	EXTI Pending register												+0x14

} EXTI_reg ;

#define EXTI 						((EXTI_reg*)EXTI_BASE)

/* enable clock commands */
//#define EXTI_PCLK_EN()				(pI2C1->APB2ENR |= (1 << 21))

/* disable clock commands */
//#define EXTI_PCLK_DI()				(pI2C1->APB2ENR |= (1 << 21))

/*
GPIOx
===================================================================
*/

#define GPIOA_BASE					(AHB1PERIPH_BASE + 0x0000)	/* GPIOA base addr. */
#define GPIOB_BASE					(AHB1PERIPH_BASE + 0x0400)	/* GPIOB base addr. */
#define GPIOC_BASE					(AHB1PERIPH_BASE + 0x0800)	/* GPIOC base addr. */
#define GPIOD_BASE					(AHB1PERIPH_BASE + 0x0C00)	/* GPIOD base addr. */
#define GPIOE_BASE					(AHB1PERIPH_BASE + 0x1000)	/* GPIOE base addr. */
#define GPIOF_BASE					(AHB1PERIPH_BASE + 0x1400)	/* GPIOF base addr. */
#define GPIOG_BASE					(AHB1PERIPH_BASE + 0x1800)	/* GPIOG base addr. */
#define GPIOH_BASE					(AHB1PERIPH_BASE + 0x1C00)	/* GPIOH base addr. */
#define GPIOI_BASE					(AHB1PERIPH_BASE + 0x2000)	/* GPIOI base addr. */
#define GPIOJ_BASE					(AHB1PERIPH_BASE + 0x2400)	/* GPIOJ base addr. */
#define GPIOK_BASE					(AHB1PERIPH_BASE + 0x2800)	/* GPIOK base addr. */

/* register structure */
typedef struct
{
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t AFR[2];
} GPIOx_reg ;

/* > GPIOx register base pointers */
#define GPIOA 						((GPIOx_reg*)GPIOA_BASE)
#define GPIOB 						((GPIOx_reg*)GPIOB_BASE)
#define GPIOC 						((GPIOx_reg*)GPIOC_BASE)
#define GPIOD 						((GPIOx_reg*)GPIOD_BASE)
#define GPIOE 						((GPIOx_reg*)GPIOE_BASE)
#define GPIOF 						((GPIOx_reg*)GPIOF_BASE)
#define GPIOG 						((GPIOx_reg*)GPIOG_BASE)
#define GPIOH 						((GPIOx_reg*)GPIOH_BASE)
#define GPIOI 						((GPIOx_reg*)GPIOI_BASE)
#define GPIOJ 						((GPIOx_reg*)GPIOJ_BASE)
#define GPIOK 						((GPIOx_reg*)GPIOK_BASE)

/* enable clock commands */
#define GPIOA_PCLK_EN()				(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()				(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()				(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()				(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()				(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()				(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()				(RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()				(RCC->AHB1ENR |= (1 << 7))
#define GPIOI_PCLK_EN()				(RCC->AHB1ENR |= (1 << 8))

/* disable clock commands */
#define GPIOA_PCLK_DI()				(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()				(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()				(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()				(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()				(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI()				(RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI()				(RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI()				(RCC->AHB1ENR &= ~(1 << 7))
#define GPIOI_PCLK_DI()				(RCC->AHB1ENR &= ~(1 << 8))

/* reset register commands */
#define GPIOA_PCLK_RESET()			do{(RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~((1 << 0)));}while(0)
#define GPIOB_PCLK_RESET()			do{(RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~((1 << 1)));}while(0)
#define GPIOC_PCLK_RESET()			do{(RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~((1 << 2)));}while(0)
#define GPIOD_PCLK_RESET()			do{(RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~((1 << 3)));}while(0)
#define GPIOE_PCLK_RESET()			do{(RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~((1 << 4)));}while(0)
#define GPIOF_PCLK_RESET()			do{(RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~((1 << 5)));}while(0)
#define GPIOG_PCLK_RESET()			do{(RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~((1 << 6)));}while(0)
#define GPIOH_PCLK_RESET()			do{(RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~((1 << 7)));}while(0)
#define GPIOI_PCLK_RESET()			do{(RCC->AHB1RSTR |= (1 << 8)); (RCC->AHB1RSTR &= ~((1 << 8)));}while(0)

/* port code */
#define GPIO_PORT_INTO_CODE(port)	((port == GPIOA) ? 0 :\
									(port == GPIOB) ? 1 :\
									(port == GPIOC) ? 2 :\
									(port == GPIOD) ? 3 :\
									(port == GPIOE) ? 4 :\
									(port == GPIOF) ? 5 :\
									(port == GPIOG) ? 6 :\
									(port == GPIOH) ? 7 :\
									(port == GPIOI) ? 8:0 )
/*
I2C
===================================================================
*/

#define I2C1_BASE					(APB1PERIPH_BASE + 0x5400)	/* I2C1 base addr. */
#define I2C2_BASE					(APB1PERIPH_BASE + 0x5800)	/* I2C2 base addr. */
#define I2C3_BASE					(APB1PERIPH_BASE + 0x5C00)	/* I2C3 base addr. */

/* register structure */
typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t OAR2;
	__vo uint32_t DR;
	__vo uint32_t SR1;
	__vo uint32_t SR2;
	__vo uint32_t CCR;
	__vo uint32_t TRISE;
	__vo uint32_t FLTR;
}I2Cx_reg;

#define I2C1 						((I2Cx_reg*)I2C1_BASE)
#define I2C2 						((I2Cx_reg*)I2C2_BASE)
#define I2C3 						((I2Cx_reg*)I2C3_BASE)

/* enable clock commands */
#define I2C1_PCLK_EN()				(I2C1->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()				(I2C2->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()				(I2C3->APB1ENR |= (1 << 23))

/* disable clock commands */
#define I2C1_PCLK_DI()				(I2C1->APB1ENR |= ~(1 << 21))
#define I2C2_PCLK_DI()				(I2C2->APB1ENR |= ~(1 << 22))
#define I2C3_PCLK_DI()				(I2C3->APB1ENR |= ~(1 << 23))

/*
SPI1-3
===================================================================
*/

#define SPI1_BASE					(APB2PERIPH_BASE + 0x3000)	/* SPI1 base addr. */
#define SPI2_BASE					(APB1PERIPH_BASE + 0x3800)	/* SPI2 base addr. */
#define SPI3_BASE					(APB1PERIPH_BASE + 0x3C00)	/* SPI3 base addr. */

/* register structure */
typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t OAR2;
	__vo uint32_t DR;
	__vo uint32_t SR1;
	__vo uint32_t SR2;
	__vo uint32_t CCR;
	__vo uint32_t TRISE;
	__vo uint32_t FLTR;
}SPIx_reg;

/* > SPI x register base pointers */
#define SPI_1						(SPIx_reg*)(SPI1_BASE)
#define SPI_2						(SPIx_reg*)(SPI2_BASE)
#define SPI_3						(SPIx_reg*)(SPI3_BASE)

/*
USART1-6
===================================================================
*/

#define USART1_BASE					(APB2PERIPH_BASE + 0x1000)	/* USART1 base addr. */
#define USART2_BASE					(APB1PERIPH_BASE + 0x4400)	/* USART2 base addr. */
#define USART3_BASE					(APB1PERIPH_BASE + 0x4800)	/* USART3 base addr. */
#define UART4_BASE					(APB1PERIPH_BASE + 0x4C00)	/* UART4 base addr. */
#define UART5_BASE					(APB1PERIPH_BASE + 0x5000)	/* UART5 base addr. */
#define USART6_BASE					(APB2PERIPH_BASE + 0x1400)	/* USART6 base addr. */

/*
SYSCFG
===================================================================
*/

#define SYSCFG_BASE					(APB2PERIPH_BASE + 0x3800)	/* SYSCFG base addr. */

/* register structure */
typedef struct
{
	__vo uint32_t MEMRMP;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR[4];
	__vo uint32_t CMPCR;
}SYSCFG_reg;

#define SYSCFG 						((SYSCFG_reg*)SYSCFG_BASE)
/* enable SYSCFG clock */
#define SYSCFG_PCLK_EN()			(RCC->APB2ENR |= (1 << 14));

/* disable SYSCFG clock */
#define SYSCFG_PCLK_DI()			(RCC->APB2ENR &= ~(1 << 14));

/* reset SYSCFG registers */
#define SYSCFG_PCLK_RESET()			do{(RCC->APB2ENR |= (1 << 14)); (RCC->APB2ENR &= ~((1 << 14)));}while(0)

/*
NVIC(to be edited later)
===================================================================
*/

#define NVIC_ISER					0xE000E100
#define NVIC_ICER					0XE000E180
#define NVIC_IPR					0xE000E400

#define IRQ_NO_EXTI0				6
#define IRQ_NO_EXTI1				7
#define IRQ_NO_EXTI2				8
#define IRQ_NO_EXTI3				9
#define IRQ_NO_EXTI4				10
#define IRQ_NO_EXTI9_5				23
#define IRQ_NO_EXTI15_10			40


/*
===================================================================
*/

#include <stm32f407_gpio.h>
#include <stm32f407_spi.h>

#endif /* INC_STM3F407XX_H_ */
