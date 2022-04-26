#include <stm32f30x.h>

int cont = 0;

int main()
{
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOEEN;
  GPIOE->MODER = 0x55550000;
  GPIOA->MODER &= ~GPIO_MODER_MODER0;
  while (1){
    if((GPIOA->IDR & GPIO_IDR_0) == GPIO_IDR_0){
      while((GPIOA->IDR & GPIO_IDR_0) == GPIO_IDR_0);
      cont++;
      GPIOE->ODR = (cont<<8);
    }
  }
}