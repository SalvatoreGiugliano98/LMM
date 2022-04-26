#define RCC_AHBENR      0x40021014
#define GPIOE_MODER     0x48001000
#define GPIO_ODR        0x48001014

unsigned int* p;

int main()
{
  p = (unsigned int*) RCC_AHBENR;
  *p = (1<<21);
  p = (unsigned int*) GPIOE_MODER;
  *p = (1<<16) | (1<<22);
  p = (unsigned int*) GPIO_ODR;
  *p = 1<<8 | 1<<11;
  
  
  while(1);
}
