#include <stm32f30x.h>

//quetso preogramma crea un contatore che accende (o spegne) tutti i led ogni volta che raggiunge la sua unità di tempo, in questo caso un secondo

short int flag = 0; // controlla se il led è accesso oppure spento

void main()
{
  RCC->AHBENR |= RCC_AHBENR_GPIOEEN;  //Abilita la porta E
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Abilita il timer 2
  GPIOE->MODER = 0X55550000; //I led sono impostati come output
  
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
      
  }
  
}
