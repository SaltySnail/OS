
#include"eos.h"

#define EOS_UART0_BASE    eosBase + 0x00201000
#define EOS_UART0_DR      (EOS_UART0_BASE + 0x00)
#define EOS_UART0_FR      (EOS_UART0_BASE + 0x18)

void putcs(char c) {
  while(get32(EOS_UART0_FR) & BIT(5));
  put32(EOS_UART0_DR, c);
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

