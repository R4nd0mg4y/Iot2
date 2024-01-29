#include <stdint.h>
#include <stm32f401re_rcc.h>
#include <stm32f401re_gpio.h>
#include <stdio.h>

//Define Logic GPIO_PIN-
#define GPIO_PIN_SET 1
#define GPIO_PIN_RESET 0
#define GPIO_PIN_LOW 0
#define GPIO_PIN_HIGH 1
#define BUZZER_GPIO_PORT GPIOC
#define BUZZER_GPIO_PIN GPIO_Pin_9
#define BUZZER_PIN9 9
#define BUZZERControl_SetClock RCC_AHB1Periph_GPIOC
#define BUTTON_GPIO_PORT GPIOB
#define BUTTON_GPIO_PIN GPIO_Pin_4
#define BUTTON_PIN4 4
#define BUTTONControl_SetClock RCC_AHB1Periph_GPIOB



#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
static void Buzzer_Init(void)
{

//Declare type variable GPIO strust-
GPIO_InitTypeDef GPIO_InitStructure;
//Enable Clock GPIOA-
RCC_AHB1PeriphClockCmd(BUZZERControl_SetClock, ENABLE);
//Choose Pin Led--
GPIO_InitStructure.GPIO_Pin = BUZZER_GPIO_PIN;
//Choose Pin Led as Out--
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//Choose Speed Pin---
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//Select type--
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//Select status--
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
//The function initializes all of the above values-
GPIO_Init(BUZZER_GPIO_PORT, &GPIO_InitStructure);
}
static void Button_Init(void)
{

//Declare type variable GPIO Strus-
GPIO_InitTypeDef GPIO_InitStructure;
//Enable Clock GPIOC---
RCC_AHB1PeriphClockCmd(BUTTONControl_SetClock, ENABLE);
//Choose Pin BUTTON---
GPIO_InitStructure.GPIO_Pin = BUTTON_GPIO_PIN;
//Choose Pin Led as Input-
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//Choose Speed Pin-----
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//Select status-
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//The function initializes all of the above values--
GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStructure);
}
static void BuzzerRead_SetStatus (GPIO_TypeDef * GPIOx, uint8_t GPIO_PIN, uint8_t Status)
{
//Set bit in BSRR Registers-
if (Status == GPIO_PIN_SET)
{
GPIOx->BSRRL |= 1 << GPIO_PIN;
}
//Reset bit in BSRR Registers--
if (Status == GPIO_PIN_RESET)
{
GPIOx->BSRRH |= 1 << GPIO_PIN;
}

}

static uint8_t ButtonRead_Status (GPIO_TypeDef * GPIOx, uint32_t GPIO_PIN)
{
uint32_t Read_Pin;
//Read bit in IDR Registers-
Read_Pin = (GPIOx->IDR) >> GPIO_PIN;
Read_Pin = Read_Pin & 0x01;
return Read_Pin;
}



int main(void)
{
    /* Loop forever */
	SystemCoreClockUpdate();
	Buzzer_Init();
	Button_Init();

	while(1){
		 uint8_t buttonState = ButtonRead_Status(BUTTON_GPIO_PORT, BUTTON_PIN4);


		 BuzzerRead_SetStatus(BUZZER_GPIO_PORT, BUZZER_PIN9, buttonState);

	}
}
