/*
   ********************************************************
   ***                                                  ***
   ***   EOS General Header (c) 2020 by Elmer Hoeksema  ***
   ***                                                  ***
   ********************************************************
  
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

#ifndef EOS_H
#define EOS_H

#include <stdint.h>

typedef       int32_t  I32;
typedef      uint32_t UI32;
typedef       int64_t  I64;
typedef      uint64_t UI64;
typedef unsigned char   UC;

#define put8( reg, data) (*((UC   *)(reg)) = ((UC)(data)))
#define get8(reg)        (*((UC   *)(reg)))
#define put32(reg, data) (*((UI32 *)(reg)) = ((UI32)(data)))
#define get32(reg)       (*((UI32 *)(reg)))
#define put64(reg, data) (*((UI64 *)(reg)) = ((UI64)(data)))
#define get64(reg)       (*((UI64 *)(reg)))

#define BIT(x)           (1 << (x))

typedef struct {
  volatile UI32 basicPending;
  volatile UI32 pending1;
  volatile UI32 pending2;
  volatile UI32 control;
  volatile UI32 enable1;
  volatile UI32 enable2;
  volatile UI32 enableBasic;
  volatile UI32 disable1;
  volatile UI32 diasble2;
  volatile UI32 disableBasic;
} IRQREGS;

//Mijn typedefs:

typedef struct _bit_ {
        unsigned value : 1;
} bit;

typedef struct _letter_ {
	UI32 bitmap[7][5];
} letter;

typedef struct _font_ {
	letter *tekens[95];
}font;

extern UI64 eosBase;

extern void prints(char *str);
extern void printsln(char *str);
extern void ui32ToHexStr(UI32, char *str);
extern void ui32ToDecStr(UI32, char *str);
extern void mailboxCall(UI32 buffer);

#endif
