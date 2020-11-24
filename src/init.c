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

#include "eos.h"
#include "dev-video.h"
#include "print.h"

#define EOS_PI3ID         0x0D03
#define EOS_PI4ID         0x0D08
#define EOS_PI3BASE       0x3F000000
#define EOS_PI4BASE       0xFE000000

#define EOS_UART0_BASE    eosBase + 0x00201000
#define EOS_UART0_DR      (EOS_UART0_BASE + 0x00)
#define EOS_UART0_FR      (EOS_UART0_BASE + 0x18)

#define EOS_MBOX_BASE     eosBase + 0x0000B880
#define EOS_MBOX_READ     (EOS_MBOX_BASE + 0x00)
#define EOS_MBOX_STATUS   (EOS_MBOX_BASE + 0x18)
#define EOS_MBOX_WRITE    (EOS_MBOX_BASE + 0x20)

#define EOS_MBOX_EMPTY    BIT(30)
#define EOS_MBOX_FULL     BIT(31)

#define EOS_ASCII_ESC     0x1B
#define EOS_TERM_CLS      "[2J"
#define EOS_TERM_HOME     "[H"

UI64 eosBase;

void stage2(UI32 piId);
void hang();
//void putcs(char c);
char getcs();
void clearsScreen();
//void prints(char* str);
//void printsln(char* str);
UI32 stringCopy(char *source, char *destination);
void ui32ToHexStr(UI32 data, char *str);
void ui32ToBinStr(UI32 data, char *str);
void ui32ToDecStr(UI32 data, char *str);

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
  printsln("EOS 1.0 (c) 2020 by Elmer Hoeksema");

  devVideoInit(1920, 1080);

  hang();
}

void hang() {
  for(;;) asm volatile ( " wfe \n "); // hang
}
/*
void putcs(char c) {
  while(get32(EOS_UART0_FR) & BIT(5));
  put32(EOS_UART0_DR, c);
}
*/
char getcs() {
  while(get32(EOS_UART0_FR) & BIT(4));

  return get32(EOS_UART0_DR);
}

void clearsScreen() {
  // Use VT100 commands to clear screen and move cursor to position 0, 0
  putcs((char)EOS_ASCII_ESC);
  prints(EOS_TERM_CLS);
  putcs((char)EOS_ASCII_ESC);
  prints(EOS_TERM_HOME);
}
/*
void prints(char* str) {
  for (UI32 i = (UI32)0; str[i] != '\0'; i ++) {
    putcs((char)str[i]);
  }
}

void printsln(char* str) {
  prints(str);
  putcs('\r');
  putcs('\n');
}*/

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

void ui32ToBinStr(UI32 data, char *str) {
  char c;
  str[0]  = '0';
  str[1]  = 'b';
  for(UI32 i = 0; i < 32; i++) {
    str[2 + i] = (data & BIT(31 - i)) ? '1' : '0';
  }
  str[34] = '\0';
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

void mailboxCall(UI32 buffer) {
  UI32 data = buffer | 0x08;   // Mailbox channel 8 is VideoCore GPU
  while(get32(EOS_MBOX_STATUS) & EOS_MBOX_FULL);
  put32(EOS_MBOX_WRITE, data);
  do {
    while(get32(EOS_MBOX_STATUS) & EOS_MBOX_EMPTY);
    data = get32(EOS_MBOX_READ);
  } while((data & 0x0F) != 0x08);
}
