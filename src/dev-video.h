/*
   ***********************************************
   ***                                         ***
   ***   EOS Video (c) 2020 by Elmer Hoeksema  ***
   ***                                         ***
   ***********************************************

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

#ifndef EOS_DEV_VIDEO_H
#define EOS_DEV_VIDEO_H

#include "eos.h"


extern void gfx_print(char *string, font *font, UI32 virtualWidth, UI32 virtualHeight, UI32 *frameBuffer);
extern void init_character_set(font *font);
extern void init_character(letter *teken, UI32 bit0, UI32 bit1, UI32 bit2, UI32 bit3, UI32 bit4, UI32 bit5, UI32 bit6, UI32 bit7, UI32 bit8, UI32 bit9, UI32 bit10, UI32 bit11, UI32 bit12, UI32 bit13, UI32 bit14, UI32 bit15, UI32 bit16, UI32 bit17, UI32 bit18, UI32 bit19, UI32 bit20, UI32 bit21, UI32 bit22, UI32 bit23, UI32 bit24, UI32 bit25, UI32 bit26, UI32 bit27, UI32 bit28, UI32 bit29, UI32 bit30, UI32 bit31, UI32 bit32, UI32 bit33, UI32 bit34);
extern void splash_screen(UI32 *frameBuffer, UI32 virtualWidth, UI32 virtualHeight);

extern void devVideoInit(UI32 width, UI32 height);

#endif
