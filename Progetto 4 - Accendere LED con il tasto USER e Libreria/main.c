#include <stm32f30x.h>

int main()
{
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOEEN;
  GPIOA ->MODER &= ~GPIO_MODER_MODER0;
  GPIOE->MODER = 0x55550000;
  while(1){
    if((GPIOA->IDR & GPIO_IDR_0)== GPIO_IDR_0){
      GPIOE->ODR = 0x0000FF00;
    } else {
      GPIOE->ODR = 0;
    }
  }
}
