#include <stm32f30x.h>
/* crea un contatore da 8 bit che si incremente ogni volta che il tatso User viene premuto (Al rilascio del tasto).
  Ogni bit del contatore indica un led che deve essere accesso; esempio: 00000001 accende il ledo PE8, 00000011 anncende il led PE8 e il led PE9.
*/

void main()
{
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOEEN; // Attivazione PA e PE
  GPIOE->MODER = 0x55550000; //abillito i LED d PE8-PE15 come output;
  GPIOA->MODER &= ~GPIO_MODER_MODER0; //Abilita PA0 come input
  
  int count = 0;
  
  while(1){
    if((GPIOA->IDR & GPIO_IDR_0) == GPIO_IDR_0){ //controllo se il stato USER è stato premuto
      while((GPIOA->IDR & GPIO_IDR_0) == GPIO_IDR_0){} // finquando il tasto il premuto non fa niente
      count++; // incrementa il contatore una volta che il tasto è rilasciato
      GPIOE->ODR = (count<<8); //modifico i bit del MODER a seconda del valore di count
    }
  }
  
}
