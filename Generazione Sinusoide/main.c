#include <stm32f30x.h>
#include <math.h>
#include <stdio.h>
#define N 100
#define pi 3.1415

short int sinusoide[N];
int clock;

void generaSinusiode (float ampiezza);

void main()
{
  generaSinusiode(1.5);
  clock = 72*(int)(pow(10.0,6.0));
  
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //Abilito il timer
  RCC->APB1ENR |= RCC_APB1ENR_DACEN; //Abilito il DAC
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN; //Abilito la Porta PA
  
  GPIOA->MODER |= GPIO_MODER_MODER4; // Imposta la porta PA4 in modalità analogica
  
  DAC->CR |= DAC_CR_TSEL1_0; // Abilito il Trigger
  DAC->CR |= DAC_CR_TSEL1_1; // Abilito il Trigger su TIM2
  DAC->CR |= DAC_CR_TEN1;
  DAC->CR |= DAC_CR_EN1; //abilito il canale 1;
  
  TIM2->ARR = (clock/100)/N; // 1 ms / 100
  TIM2->DIER |= TIM_DIER_UIE; //Abilito l'interruzione 
  NVIC->ISER[0] |= (1<<28);
  TIM2->CR1 |= TIM_CR1_CEN; //Avvio il timer
  
  while(1);
}

void generaSinusiode (float ampiezza) {
  float Vsin;
  for (int i = 0; i < N; i++) {
    Vsin = 1.5 + (ampiezza * sin(2*pi*i/N));
    sinusoide[i] = (short int)(Vsin*4095.0/3.0);
  }
}

int j = 0;

void TIM2_IRQHandler(){
  TIM2->SR = 0;
  if (j == N) j = 0;
  DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1;
  for(int i = 0; i < 1000;i++); //attesa di 10 µs per la generazione della tensione
  DAC->DHR12R1 = sinusoide[j];
  printf("il valore del DAC è: %d",DAC->DHR12R1);
  j++;
}


