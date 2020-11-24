//Creare un progetto, usando le interruzioni, che ogni 10 secodni accenda o spenga tutti i LED; ma se si clicca il tasto USER il LED PE8 cambia stato (da acceso a spento e vic.)

#include <stm32f30x.h>
#include <math.h>

short int statoLED = 0; //Controlla se i led sono accesi
short int statoLED8 = 0; //Controlla se il led 8 è acceso
int clock = 0;


void EXTI0_IRQHandler(){
  EXTI->PR |= EXTI_PR_PR0;
  if(statoLED8 == 0){
      GPIOE->ODR |= (1<<8);
      statoLED8 = 1;
    } else {
      GPIOE->ODR &= ~(1<<8);
      statoLED8 = 0;
    }
}

void TIM2_IRQHandler(){
  TIM2->SR &= ~TIM_SR_UIF;
  if (statoLED == 0) {
    GPIOE->ODR = 0x0000FF00;
    statoLED = !statoLED;
    statoLED8 = statoLED;
  } else {
    GPIOE->ODR = 0;
    statoLED = !statoLED;
    statoLED8 = statoLED;
  }
}


void main()
{
  
  clock = 72*(int)pow(10.0,6.0);
  
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //Abilito il timer
  RCC->AHBENR |= RCC_AHBENR_GPIOEEN; //Abilito la porta E
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN; //Abilito la porta A
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  
  GPIOE->MODER |= 0x55550000; //Abilito tutti i LED
  GPIOA->MODER &= ~GPIO_MODER_MODER0; //Abilito la Porta PA0(USER button) come input
  
  TIM2->DIER |= TIM_DIER_UIE; //Aibilita le interrupt sul timer
  NVIC->ISER[0] |= (1<<28); //Specifica la ISR per il Timer
  
  SYSCFG->EXTICR[0] &= SYSCFG_EXTICR1_EXTI0_PA; //EXTI0 = 000; porta A 
  EXTI->IMR |= EXTI_IMR_MR0; //machera disabilitata per la linea 0
  EXTI->RTSR |= EXTI_RTSR_TR0; //Fronte di salita
  NVIC->ISER[0] |= (1<<6); //ISR per l'exit0
  
  TIM2->ARR = 10*clock;
  TIM2->CNT = 0;
  TIM2->CR1 |= TIM_CR1_CEN;
  
  while(1);
}

