// Si vogliono accendere tutti i LED se il pulsante USER viene premuto

#define RCC_AHBENR 0x40021014 //attivazione clock
#define GPIOA_MODER 0x48000000 // Pulsante USER - PA0
#define GPIOA_IDR 0x48000010 // lettura input
#define GPIOE_MODER 0x48001000 // abilitazione LED PE8-PE15
#define GPIOE_ODR 0x48001014 //Accensione LED

unsigned int * p;

void main () {
  //abilitazione Clock su PA e PE
  p = (unsigned int*) RCC_AHBENR; 
  *p = (1<<21)|(1<<17);
  
  //abilitazione del LED (PE8-P15) come Output
  p = (unsigned int*) GPIOE_MODER;
  *p = 0x55550000; //Mettiamo (01) su tutte le linee per abilitare tutti i LED
  
  //abilitazione PA0 come input
  p = (unsigned int *) GPIOA_MODER;
  *p &= 0xFFFFFFFC; // facciamo in modo che solo i due bit meno significativi diventino (00), e gli alti rimangano invariati
  
  while(1) {
    //lettura input
    p = (unsigned int*) GPIOA_IDR;
    
    if((*p&1) == 1) {
      p = (unsigned int *) GPIOE_ODR;
      *p = 0x0000FF00;
    }
    else {
      p = (unsigned int *) GPIOE_ODR;
      *p = 0x00000000;
    }
  }
}