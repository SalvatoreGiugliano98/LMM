#define RCC_AHEBNR      0x40021014
#define GPIOA_MODER     0x48000000
#define GPIOA_IDR       0x48000010
#define GPIOE_MODER     0x48001000
#define GPIOE_ODR       0x48001014

unsigned int* p;

int main()
{
  p = (unsigned int*) RCC_AHEBNR;
  *p = (1<<21) | (1<<17);
  p = (unsigned int*) GPIOA_MODER;
  *p &= 0xFFFFFFFC;
  p = (unsigned int*) GPIOE_MODER;
  *p= 0x55550000;
 
  while(1){
    p = (unsigned int*) GPIOA_IDR;
    if((*p&1)==1){
      p = (unsigned int*) GPIOE_ODR;
      *p = 0x0000FF00;
    }
    else {
      p = (unsigned int*) GPIOE_ODR;
      *p = 0x00000000;
    }
  }
}

