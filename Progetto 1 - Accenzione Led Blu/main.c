#define RCC_AHBENR      0x40021014    //attivazione periferiche
#define GPIOE_MODER     0x48001000  //abilitazione led
#define GPIOE_ODR       0x48001014    //accendere led PE8

unsigned int* p;

int main()
{
  p = (unsigned int*) RCC_AHBENR;
  *p = 0x00200000;
  p = (unsigned int*) GPIOE_MODER;
  *p = 0x00010000;
  p = (unsigned int*) GPIOE_ODR;
  *p = 1<<8;
  while(1);
}
