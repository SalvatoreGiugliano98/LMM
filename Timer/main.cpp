#include <stm32f30x.h>

//quetso preogramma crea un contatore che accende (o spegne) tutti i led ogni volta che raggiunge la sua unità di tempo, in questo caso un secondo

short int flag = 0; // controlla se il led è accesso oppure spento
bool enable = false;
void main()
{
  RCC->AHBENR |= RCC_AHBENR_GPIOEEN | RCC_AHBENR_GPIOAEN;  //Abilita la porta E e la porta A
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Abilita il timer 2
  GPIOE->MODER = 0X55550000; //I led sono impostati come output
  GPIOA->MODER &= ~GPIO_MODER_MODER0; //Abilita PA0 come input, ovvero il tasto user
  
  TIM2->CR1 |= TIM_CR1_CEN; //Abilita il conteggio
  TIM2->ARR = 8000000; //importa sa durata t = 1 secondo; N = t*8MHz (8MHz è la frequenza della Schedina)
  TIM2->CNT = 0; //azzera il conteggio
  
  while(1){
    if((TIM2->SR & TIM_SR_UIF)==TIM_SR_UIF && !flag) { //Controlla se il timer ha raggiunto la prossima unità di tempo ed è spento il led
      GPIOE->ODR = 0x0000FF00; //accende i led
      TIM2->SR &= ~TIM_SR_UIF; //azzera l'UIF
      flag = 1; //Segnale che il led è acceso
    }
    if ((TIM2->SR & TIM_SR_UIF)==TIM_SR_UIF && flag) { //Controlla se il timer ha raggiunto la prossima unità di tempo ed è acceso il led
      GPIOE->ODR = 0; //spegne i led
      TIM2->SR &= ~TIM_SR_UIF; // azzerla l'uif
      flag = 0; //segnala che i led sono spenti
    }
    
    //AGGIUNTA ALL'ESERCIZIO: se si preme per almeno 1 secondo il tasto USERil Timer si blocca
    
    if((GPIOA->IDR & GPIO_IDR_0) == GPIO_IDR_0){ //controllo se il stato USER è stato premuto
      while((GPIOA->IDR & GPIO_IDR_0) == GPIO_IDR_0){} // finquando il tasto il premuto non fa niente
      enable = !enable; //segnala se il timer è abilitato o no
      if(enable == false){ //se non è abilitato allora entra qui per abilitarlo
        TIM2->CR1 &= ~TIM_CR1_UDIS; //riabilita il timer, mettendo a 0 il bit UDIS
        flag = 0; //segnale che il led sono spenti
      } else {
        TIM2->CR1 |= TIM_CR1_UDIS; //Disabilita il conteggio al possimo update mettendo a 1 il bit UDIS
        flag = 1; // segnale che il led sono accessi, in questo modo nell'ultimo ciclo, se sono spenti, rimangono tali altimenti li spegne
      }
    } 
  }
  
}
