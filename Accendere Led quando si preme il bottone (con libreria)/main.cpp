#include <stm32f30x.h>

void main () {
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOEEN; // Attivazione PA e PE
  GPIOE->MODER = 0x55550000; //abillito i LED d PE8-PE15 come output;
  GPIOA->MODER &= ~GPIO_MODER_MODER0; //Abilita PA0 come input
 
  while(1){
    if((GPIOA->IDR & GPIO_IDR_0) == GPIO_IDR_0){
      GPIOE->ODR = 0x0000FF00;
    } else {
      GPIOE->ODR = 0;
    }
  }
}