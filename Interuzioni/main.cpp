#include <stm32f30x.h>
#include <math.h>

bool flag = false; //Controlla se i led sono accessi
int clock = 0;

void main()
{
  clock = 72*pow(10.0,6.0);
  
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //Abilito il timer
  RCC->AHBENR |= RCC_AHBENR_GPIOEEN; //Abilito la porta E
  GPIOE->MODER |= 0x55550000; //Abilito tutti i LED
  
  TIM2->DIER |= TIM_DIER_UIE; //Aibilita le interrupt sul timer
  NVIC->ISER[0] |= (1<<28); //Specifica la ISR
  
  TIM2->ARR = clock / 2;
  TIM2->CNT = 0;
  TIM2->CR1 |= TIM_CR1_CEN;
  
  while(1){
    GPIOE->ODR |= (1<<9);
    for(int i = 0; i<2000000; i++);
    GPIOE->ODR |= ~(1<<9);
    for(int i = 0; i<2000000; i++);
  }
}

void TIM2_IRQHandler(){
  TIM2->SR &= ~1;
  if (flag == false) {
    GPIOE->ODR |= (1<<8);
    flag = true;
  } else {
    GPIOE->ODR |= ~(1<<8);
    flag = false;
  }
}