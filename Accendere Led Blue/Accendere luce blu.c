
unsigned int* puntatore;
void main(){
  puntatore = (unsigned int*) 0x40021014; //abilito il clock sul registro AHB metendo ad 1 il bit 21
  *puntatore = 0x00200000;
  
  puntatore = (unsigned int*) 0x48001000; //imposto la linea pe8 come output digitale (01)
  *puntatore = 0x00010000; //abilito il primo led
  
  puntatore = (unsigned int*) 0x48001014; // accendo il primo led (metto 1 sull'8 bit dell'ODR)
  *puntatore = 1<<8; // alza il bit 8 dell'ODR
  
  puntatore = (unsigned int*) 0x48001000; //imposto nel moder che le linea pe9 si output digitale, ovvero abilito il secondo led
  *puntatore |= (1<<18); // alzo il bit 18 dell'ODR, lasciando tutto il resto come era (|= questo è il simbolo OR e poi assegna)
   
  puntatore = (unsigned int*) 0x48001014; //accendo il secondo led matenendo il primo attovo con iìl'istruzione OR
  *puntatore |= (1<<9);
  
  puntatore = (unsigned int*) 0x48001014; //accendo il secondo led matenendo il primo attovo con iìl'istruzione OR
  *puntatore &= ~(1<<8);
  
  while(1);
}