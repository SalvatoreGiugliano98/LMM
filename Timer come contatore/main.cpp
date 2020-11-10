#include <stm32f30x.h>
#include <stdio.h>
//creare un timer di tipo contatore che accende i led quando rilacio il pulsante USER e restituisce il valore di conteggio e restituisce il valore del tempo trascorso

float tempo = 0; //il risultatore del tempo trascorso mentre si è premuto il tasto USER

void main()
{
  RCC->AHBENR |= RCC_AHBENR_GPIOEEN | RCC_AHBENR_GPIOAEN;  //Abilita la porta E e la porta A
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Abilita il timer 2
  GPIOE->MODER = 0X55550000; //Tutti i led sono impostati come output
  GPIOA->MODER &= ~GPIO_MODER_MODER0; //Abilita PA0 come input, ovvero il tasto user
  
  int count = 0; // Numero di conteggi effettuati
  int N_count; // Noumero di volte i cui il timer conta
  float Tck = 0.000000125; //Tempo di durata del clock
  
  while(1){
    if((GPIOA->IDR & GPIO_IDR_0) == GPIO_IDR_0){ //controllo se il stato USER è stato premuto
      
      TIM2->CNT = 0; //azzera il conteggio
      TIM2->CR1 |= TIM_CR1_CEN; //abilita il conteggio
      while((GPIOA->IDR & GPIO_IDR_0) == GPIO_IDR_0){
      GPIOE->ODR = (1<<8) | (1<<12); //accende i led
      } // finquando il tasto il premuto non fa niente
      
      
      //nel momento il cui il pulsante user viene rilasciato
      TIM2->CR1 &= ~TIM_CR1_CEN; //disabilita il conteggio
      N_count = TIM2->CNT; // salva il numero di conteggi effettuati
      GPIOE->ODR = 0; //spegne i led
      
      count++;
      tempo = (float)N_count*Tck;
      //Per i Timer-contatori il valore t = N_count * Tck
      printf("conteggio %d: %f secondi\n", count, tempo);
    }
  }
  
}
