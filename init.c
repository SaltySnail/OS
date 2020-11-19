/*
   **********************************************
   ***                                        ***
   ***   EOS Init (c) 2020 by Elmer Hoeksema  ***
   ***                                        ***
   **********************************************
  
   Copyright (c) 2020, Elmer Hoeksema
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
       * Redistributions of source code must retain the above copyright
         notice, this list of conditions and the following disclaimer.
       * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
 
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdint.h>

#define EOS_PI3ID        0x0D03
#define EOS_PI4ID        0x0D08
#define EOS_PI3BASE      0x3F000000
#define EOS_PI4BASE      0xFE000000

#define UART0_BASE      eosBase + 0x00201000
#define UART0_DR        (UART0_BASE + 0x00)
#define UART0_FR        (UART0_BASE + 0x18)

#define EOS_ASCII_ESC   0x1B
#define EOS_TERM_CLS    "[2J"
#define EOS_TERM_HOME   "[H"

/*//nieuwe code:
#define GPIO_BASE       (EOS_PI4BASE + 0x200000)

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

int  mem_fd;
void *gpio_map;

volatile unsigned *gpio;

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0

#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH

#define GPIO_PULL *(gpio+37) // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio+38) // Pull up/pull down clock
//einde nieuwe code
*/
#define BUSY_WAIT __asm__ __volatile__("")
#define BUSY_WAIT_N 0x100000

typedef  int32_t  I32;
typedef uint32_t UI32;
typedef  int64_t  I64;
typedef uint64_t UI64;

#define put32(reg, data) (*((UI32 *)(reg)) = ((UI32)(data)))
#define get32(reg)       (*((UI32 *)(reg)))

UI64 eosBase;

void stage2(UI32 piId);
void hang();
void putcs(char c);
char getcs();
void clearsScreen();
void prints(char* str);
void printsln(char* str);
UI32 stringCopy(char *source, char *destination);
void ui32ToHexStr(UI32 data, char *str);
void ui32ToDecStr(UI32 data, char *str);

void printMem(volatile UI32* address); 
void setFSEL(volatile UI32 *address, UI32 value, UI32 offset);

	//void setup_io(); //new
//void traffic_light();
void blink();

/* entry point
   DO NOT USE ANY VARIABLES OR FUNCTION CALLS IN THIS FUNCTION!!!
   If you do, gcc will add a stack adjustment at the top of the function,
   before the stack is initialized. This will result in a hang at boot!!!
*/
void start() {
  asm volatile (
    " mov  sp, #0x00010000     \n " // set stack pointer
    " mrs  x0, midr_el1        \n " // get pi version id
    " and  x0, x0, #0x0000FFF0 \n " // mask out other bits
    " lsr  x0, x0, #4          \n " // shift bits to end
    " b    stage2              \n " // go to stage 2
  );

  // Execution should never reach this line, but just to be sure
  for(;;) asm volatile ( " wfe \n "); // hang
}

void stage2(UI32 piId) {
  // if not pi 3 or pi4 -> hang
  if((piId != EOS_PI3ID) && (piId != EOS_PI4ID)) hang();

  if(piId == EOS_PI3ID) eosBase = EOS_PI3BASE; else eosBase = EOS_PI4BASE;

  clearsScreen();
  printsln("EOS 1.0 (c) 2020 by Elmer Hoeksema \n wtf \n");

  //code by julian:
  printsln("Julian zegt hoi"); 

  //traffic_light();
  blink();

  hang();
}

void hang() {
  for(;;) asm volatile ( " wfe \n "); // hang
}

void putcs(char c) {
  while(get32(UART0_FR) & (1 << 5));
  put32(UART0_DR, c);
}

char getcs() {
  while(get32(UART0_FR) & (1 << 4));

  return get32(UART0_DR);
}

void clearsScreen() {
  // Use VT100 commands to clear screen and move cursor to position 0, 0
  putcs((char)EOS_ASCII_ESC);
  prints(EOS_TERM_CLS);
  putcs((char)EOS_ASCII_ESC);
  prints(EOS_TERM_HOME);
}

void prints(char* str) {
  for (UI32 i = (UI32)0; str[i] != '\0'; i ++) {
    putcs((char)str[i]);
  }
}

void printsln(char* str) {
  prints(str);
  putcs('\r');
  putcs('\n');
}

UI32 stringCopy(char *source, char *destination) {
  UI32 i = 0;

  while(*(source + i)) {
    *(destination + i) = *(source + i);
    i++;
  }

  return i;
}

void ui32ToHexStr(UI32 data, char *str) {
  char c;
  str[0]  = '0';
  str[1]  = 'x';
  for(UI32 i = 0; i < 8; i++) {
    str[2 + i] = (c = (char)((data & (0x0000000F << ((7 - i) << 2))) >> ((7 - i) << 2))) < (char)10 ? c + '0' : c + 'A' - (char)10;
  }
  str[10] = '\0';
}

void ui32ToDecStr(UI32 data, char *str) {
  int i = 0;
  while(data > 0) {
    str[i] = '0' + (char)(data % 10);
    data = data / 10;
    i++;
  }
  for(UI32 j = 0; (i > 0) && (j < i / 2); j++) {
    char c = str[j];
    str[j] = str[i - j - 1];
    str[i - j - 1] = c;
  }
  if(i == 0) {
    str[0] = '0';
    i++;
  }
  str[i] = '\0';
}
/*
void setup_io()
{
   // open /dev/mem 
   if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printsln("can't open /dev/mem \n");
      //exit(-1);
      hang();
   }

   // mmap GPIO 
   gpio_map = mmap(
      NULL,             //Any adddress in our space will do
      BLOCK_SIZE,       //Map length
      PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
      MAP_SHARED,       //Shared with other processes
      mem_fd,           //File to map
      GPIO_BASE         //Offset to GPIO peripheral
   );

   close(mem_fd); //No need to keep mem_fd open after mmap

   if (gpio_map == MAP_FAILED) {
      printsln("mmap error");//errno also set!
      //exit(-1);
      hang();
   }

   // Always use volatile pointer!
   gpio = (volatile unsigned *)gpio_map;


}

void traffic_light()


{
  int g, rep;
  for (g=7; g<=11; g++)
  {
    INP_GPIO(g); // must use INP_GPIO before we can use OUT_GPIO
    OUT_GPIO(g);
  }

  for (rep=0; rep<10; rep++)
  {
     for (g=7; g<=11; g++)
     {
       GPIO_SET = 1<<g;
       sleep(1);
     }
     for (g=7; g<=11; g++)
     {
       GPIO_CLR = 1<<g;
       sleep(1);
     }
  }	
}*/

void blink()
{
	char *temp;
     uint32_t i;
     UI32 gpset0, gpclr0, tmp;
    /* At the low level, everything is done by writing to magic memory addresses.
    The device tree files (dtb / dts), which are provided by hardware vendors,
    tell the Linux kernel about those magic values. */
     //rpi3b+
  //  volatile uint32_t * const GPFSEL4 = (uint32_t *)0x7E200010;
  //  volatile uint32_t * const GPFSEL3 = (uint32_t *)0x7E20000C;
  //  volatile uint32_t * const GPSET1  = (uint32_t *)0x7E200020;
 //   volatile uint32_t * const GPCLR1  = (uint32_t *)0x7E20002C;   
    
    //volatile uint32_t * const GPFSEL5 = (uint32_t *)0x3F200014;
    //volatile uint32_t * const GPFSEL4 = (uint32_t *)0x3F200010;
    //volatile uint32_t * const
    volatile UI32 * const GPFSEL1 = (uint32_t *)0x3F200004;

    //volatile uint32_t * const GPFSEL3 = (uint32_t *)0x3F20000C;
    volatile uint32_t * const GPFSEL2 = (uint32_t *)0x3F200008;
    //volatile uint32_t * const GPSET1  = (uint32_t *)0x3F200020;
    //volatile uint32_t * const GPCLR1  = (uint32_t *)0x3F20002C;   
    volatile uint32_t * const GPSET0  = (uint32_t *)0x3F20001C;
    volatile uint32_t * const GPCLR0  = (uint32_t *)0x3F200028;   
    
   // volatile uint32_t * const GPFSEL4 = (uint32_t *)0x7E200010;
    //volatile uint32_t * const GPFSEL3 = (uint32_t *)0x3F20000C;
   // volatile uint32_t * const GPFSEL2 = (uint32_t *)0x7E200008;
    //volatile uint32_t * const GPSET1  = (uint32_t *)0x3F200020;
    //volatile uint32_t * const GPCLR1  = (uint32_t *)0x3F20002C;   
   // volatile uint32_t * const GPSET0  = (uint32_t *)0x7E20001C;
   // volatile uint32_t * const GPCLR0  = (uint32_t *)0x7E200028;   
   //rpi2
   // volatile uint32_t * const GPFSEL4 = (uint32_t *)0x3F200010;
   // volatile uint32_t * const GPFSEL3 = (uint32_t *)0x3F20000C;
   // volatile uint32_t * const GPSET1  = (uint32_t *)0x3F200020;
  //  volatile uint32_t * const GPCLR1  = (uint32_t *)0x3F20002C;

    //*GPFSEL4 = (*GPFSEL4 & ~(7 << 21)) | (1 << 21);
    //*GPFSEL3 = (*GPFSEL3 & ~(7 << 15)) | (1 << 15);
    //stoplicht 1 
     setFSEL(GPFSEL1, 0b001, 7); //gpio 17 rood 
     setFSEL(GPFSEL2, 0b001, 7); //gpio 27 oranje
     setFSEL(GPFSEL2, 0b001, 2); //gpio 22 groen
	//stoplicht 2
     setFSEL(GPFSEL2, 0b001, 5); //gpio 25 groen
     setFSEL(GPFSEL2, 0b001, 4); //gpio 24 oranje
     setFSEL(GPFSEL2, 0b001, 3); //gpio 23 rood

	   gpclr0 = get32(GPCLR0);
           gpclr0 ^= 0b11111111111111111111111111111111;
	   //clear stoplicht 1 rood en 2 groen  0x0BC20000
	   put32(GPCLR0, gpclr0);

     //setFSEL(GPFSEL1, 0b001, 8); //actled
    while (1) 
    {
	   gpset0 = get32(GPSET0);
           gpset0 &= (~0b00001011110000100000000000000000); //reset set register
           gpset0 |= 0b00000000000000100000000000000000; //gpio 17
           //0b00000001000000100000000000000000; //stoplicht 1 op rood 2 op oranje 0x01020000
	   put32(GPSET0, gpset0);

     	   //for (i = 0; i < 5000000; ++i)
	   //{ //BUSY_WAIT; }
    	   //}
	printsln("1");
	   for (i = 0; i < 2000000; ++i) { BUSY_WAIT; }
	   
	   gpclr0 = get32(GPCLR0);
           //gpclr0 |= 0b11110100001111011111111111111111;
           gpclr0 |= 0b00001011110000100000000000000000;
	   put32(GPCLR0, gpclr0);
	   
	   gpset0 = get32(GPSET0);
           gpset0 &= (~0b00001011110000100000000000000000);
           gpset0 |= 0b00001000000000000000000000000000; //gpio 27 oranje 1
           //0b00000001000000100000000000000000; //stoplicht 1 op rood 2 op oranje 0x01020000
	   put32(GPSET0, gpset0);
	   
	
	   printsln("2");
	   for (i = 0; i < 2000000; ++i) { BUSY_WAIT; }
	   
	   gpclr0 = get32(GPCLR0);
           //gpclr0 |= 0b11110100001111011111111111111111;
           gpclr0 |= 0b00001011110000100000000000000000;
	   put32(GPCLR0, gpclr0);
	   
	   gpset0 = get32(GPSET0);
           gpset0 &= (~0b00001011110000100000000000000000);
           gpset0 |= 0b00000000010000000000000000000000; //gpio 22
           //0b00000001000000100000000000000000; //stoplicht 1 op rood 2 op oranje 0x01020000
	   put32(GPSET0, gpset0);
	    
	printsln("3");
	   for (i = 0; i < 2000000; ++i) { BUSY_WAIT; }

	   gpclr0 = get32(GPCLR0);
           //gpclr0 |= 0b11110100001111011111111111111111;
           gpclr0 |= 0b00001011110000100000000000000000;
	   put32(GPCLR0, gpclr0);
	   
	   gpset0 = get32(GPSET0);
           gpset0 &= (~0b00001011110000100000000000000000);
           gpset0 |= 0b00000000100000000000000000000000; //gpio 23
           //0b00000001000000100000000000000000; //stoplicht 1 op 
	   //rood 2 op oranje 0x01020000
	   put32(GPSET0, gpset0);
	   
	   
	printsln("4");
	   for (i = 0; i < 2000000; ++i) { BUSY_WAIT; }
	   
	   gpclr0 = get32(GPCLR0);
           //gpclr0 |= 0b11110100001111011111111111111111;
           gpclr0 |= 0b00001011110000100000000000000000;
	   put32(GPCLR0, gpclr0);
	   
	   gpset0 = get32(GPSET0);
           gpset0 &= (~0b00001011110000100000000000000000);
           gpset0 |= 0b00000001000000000000000000000000; //gpio 24
           //0b00000001000000100000000000000000; //stoplicht 1 op rood 2 op oranje 0x01020000
	   put32(GPSET0, gpset0);
	   
	printsln("5");
	   for (i = 0; i < 2000000; ++i) { BUSY_WAIT; }
	   
	   gpclr0 = get32(GPCLR0);
           //gpclr0 |= 0b11110100001111011111111111111111;
           gpclr0 |= 0b00001011110000100000000000000000;
	   put32(GPCLR0, gpclr0);
	   
	   gpset0 = get32(GPSET0);
           gpset0 &= (~0b00001011110000100000000000000000);
           gpset0 |= 0b00000010000000000000000000000000; //gpio 25 groen 2
           //0b00000001000000100000000000000000; //stoplicht 1 op rood 2 op oranje 0x01020000
	   put32(GPSET0, gpset0);
	   
	printsln("6");
	   for (i = 0; i < 2000000; ++i) { BUSY_WAIT; }
	   
	   gpclr0 = get32(GPCLR0);
           //gpclr0 |= 0b11110100001111011111111111111111;
           gpclr0 |= 0b00001011110000100000000000000000;
	   put32(GPCLR0, gpclr0);
	   for (i = 0; i < 2000000; ++i) { BUSY_WAIT; }
		   //0b00001011110000100000000000000000;
	   //clear stoplicht 1 rood en 2 groen  0x0BC20000
	   //put32(GPCLR0, gpclr0);
	   
	   /*
     	   gpclr0 = get32(GPCLR0);
           gpclr0 |= 0x0BC20000;//0b00001011110000100000000000000000; //clear stoplicht 1 rood en 2 groen 
	   put32(GPCLR0, gpclr0);
     	   
	   gpset0 = get32(GPSET0);
	   //tmp = 1 << 17;
	   //gpset0 |= tmp;
           gpset0 ^= 0x02020000;// 0b00000010000000100000000000000000; //stoplicht 1 op rood 2 op groen
	   put32(GPSET0, gpset0);
	   printsln("1: Rood 2: Groen");
	   printMem(GPSET0);
        
	   for (i = 0; i < 5000000; ++i) { BUSY_WAIT; }
     	   gpclr0 = get32(GPCLR0);
           //gpclr0 |= 0b00001011110000100000000000000000; //clear stoplicht 1 rood en 2 groen 
           gpclr0 |= 0x0BC20000;//0b00001011110000100000000000000000; //clear stoplicht 1 rood en 2 groen 
	   put32(GPCLR0, gpclr0);
	   //printMem(GPCLR0);
	   
	   gpset0 = get32(GPSET0);
           gpset0 ^= 0x01020000;//0b00000001000000100000000000000000; //stoplicht 1 op rood 2 op oranje
	   put32(GPSET0, gpset0);
	   printsln("1: Rood 2: Oranje");

        for (i = 0; i < 5000000; ++i) { BUSY_WAIT; }	
		
     	   gpclr0 = get32(GPCLR0);
           gpclr0 |= 0x0BC20000;//0b00001011110000100000000000000000; //clear stoplicht 1 rood en 2 groen 
           //gpclr0 |= 0b00000001000000100000000000000000; //clear stoplicht 1 rood en 2 oranje	
	   put32(GPCLR0, gpclr0);

     	   gpset0 = get32(GPSET0);
           gpset0 ^= 0x00C00000;//0b00000000110000000000000000000000; //stoplicht 1 op groen 2 op rood
	   put32(GPSET0, gpset0);
	   printsln("1: Groen 2: Rood");

        for (i = 0; i < 5000000; ++i) { BUSY_WAIT; }
	
     	   gpclr0 = get32(GPCLR0);
           gpclr0 |= 0x0BC20000;//0b00001011110000100000000000000000; //clear stoplicht 1 rood en 2 groen 
           //gpclr0 |= 0b00000000110000000000000000000000; //clear stoplicht 1 groen	
	   put32(GPCLR0, gpclr0);
     	   
	   gpset0 = get32(GPSET0);
           gpset0 ^= 0x08800000;//0b00001000100000000000000000000000; //stoplicht 1 op oranje 2 op rood
	   put32(GPSET0, gpset0);
	   printsln("1: Oranje 2: Rood");
	//printsln(" Blink");
	//printMem(GPFSEL1);
        for (i = 0; i < 5000000; ++i) { BUSY_WAIT; }
    	*/
    }
}

void setFSEL(volatile UI32 *address, UI32 value, UI32 offset)
{
  value <<= offset * 3;
  UI32 mask = 0b111 << offset * 3;
  UI32 temp = get32(address);
  temp &= (~mask);
  put32(address, (temp | value));
}
  
void printMem(volatile UI32* address) 
{
    UI32 data = get32(address);
    char data_string[40];
    prints("HEX DATA: ");
    ui32ToHexStr(data, data_string);
    printsln(data_string);
}
