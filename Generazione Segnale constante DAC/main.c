#include <stm32f30x.h>
#include <math.h>
#include <stdio.h>
#define NGEN 3

int Vdda = 3; // 3.0 V
float Tsett = 0.000004; // 4 µs
int clock = 0;
short int vettDAC[NGEN];
int j = 0;
void main()
{
  vettDAC[0] = 0;
  vettDAC[1] = 2048;
  vettDAC[2] = 4095;
  
  clock = 72*(int)pow(10.0,6.0);
  
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //Abilito il timer
  RCC->APB1ENR |= RCC_APB1ENR_DACEN; //Abilito il DAC
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  
  GPIOA->MODER |= GPIO_MODER_MODER4;
  
  DAC->CR |= DAC_CR_TSEL1_2;
  DAC->CR |= DAC_CR_TSEL1_1;
  DAC->CR |= DAC_CR_TSEL1_0;
  
  DAC->CR |= DAC_CR_EN1;
  
  TIM2->ARR = clock/100; // 1 ms
  TIM2->DIER |= TIM_DIER_UIE;
  NVIC->ISER[0] |= (1<<28);
  TIM2->CR1 |= TIM_CR1_CEN;
  
  while(1);
}

void TIM2_IRQHandler(){
  TIM2->SR = 0;
  
  if(j == NGEN) {j = 0;}
  DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1;
  DAC->DHR12R1 = vettDAC[j];
 
  printf("Il valore della funzione è:%d \n",vettDAC[j]);
  j++;
}
