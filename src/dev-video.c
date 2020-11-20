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

#include "eos.h"

#define EOS_DEV_VIDEO_MB_ALLOCATE_BUFFER   0x40001
#define EOS_DEV_VIDEO_MB_SET_PHYSICAL_SIZE 0x48003
#define EOS_DEV_VIDEO_MB_SET_VIRTUAL_SIZE  0x48004
#define EOS_DEV_VIDEO_MB_SET_DEPTH         0x48005
#define EOS_DEV_VIDEO_MB_SET_PIXEL_ORDER   0x48006

void splash_screen(UI32 *frameBuffer, UI32 virtualWidth, UI32 virtualHeight)
{
  UI32 index = virtualHeight * virtualWidth;
  for(; index > (virtualHeight * virtualWidth / 3)*2; index--) { //groen
	  //blauw
    frameBuffer[index] = 0x000000FF;
  }
  for(; index > (virtualHeight * virtualWidth / 3); index--) { 
	  //groen
    frameBuffer[index] = 0x0000FF00;
  }
  for(; index > 0; index--) { 
	  //rood
    frameBuffer[index] = 0x00FF0000;
  }
  
  index = virtualHeight * virtualWidth;
  //for(; index < (virtualHeight * virtualWidth / 3); index++) { //rood
  //for(; index < (virtualHeight * virtualWidth / 3)*2; index++) { //groen
  for(; index > (virtualHeight * virtualWidth / 3)*2; index--) { //groen
  //for(; index < virtualHeight * virtualWidth; index++) { 
	  //blauw
    frameBuffer[index] = 0x0000FF00;
  }
  for(; index > (virtualHeight * virtualWidth / 3); index--) { 
	  //groen
    frameBuffer[index] = 0x00FF0000;
  }
  for(; index > 0; index--) { 
	  //rood
    frameBuffer[index] = 0x000000FF;
  }
  for(; index < (virtualHeight * virtualWidth / 3); index++) { //rood
	if (frameBuffer[index] % 2)
	{
    		frameBuffer[index] = 0x00F0F0F0;
	}
	else
	{
    		frameBuffer[index] = 0x00FF00FF;
	}
  }
  for(; index < (virtualHeight * virtualWidth / 3)*2; index++) { //groen
	
	if (frameBuffer[index] % 2)
	{
    		frameBuffer[index] = 0x000F0F0F;
	}
	else
	{
    		frameBuffer[index] = 0x00FFFFFF;
	}
  }
  for(; index < virtualHeight * virtualWidth; index++) { 
  
	if (frameBuffer[index] % 2)
	{
    		frameBuffer[index] = 0x007F7F7F;
	}
	else
	{
    		frameBuffer[index] = 0x003F3F3F;
	}
  }
  for(; index > 0; index--) { 
    frameBuffer[index] = 0x00000000;
  }
	
}

void devVideoInit(UI32 width, UI32 height) {
  UI32 mailboxBuffer[100] __attribute__((aligned(16)));

  mailboxBuffer[0]  = 26 * 4;   // Size of mailbox buffer in bytes
  mailboxBuffer[1]  = 0;        // Request

  mailboxBuffer[2]  = EOS_DEV_VIDEO_MB_SET_PHYSICAL_SIZE;
  mailboxBuffer[3]  = 8;        // Size of response values in bytes
  mailboxBuffer[4]  = 8;        // Size of request values in bytes
  mailboxBuffer[5]  = width;    // Width
  mailboxBuffer[6]  = height;   // height

  mailboxBuffer[7]  = EOS_DEV_VIDEO_MB_SET_VIRTUAL_SIZE;
  mailboxBuffer[8]  = 8;        // Size of response values in bytes
  mailboxBuffer[9]  = 8;        // Size of request values in bytes
  mailboxBuffer[10] = width;    // Width
  mailboxBuffer[11] = height;   // height

  mailboxBuffer[12] = EOS_DEV_VIDEO_MB_SET_DEPTH;
  mailboxBuffer[13] = 4;        // Size of response values in bytes
  mailboxBuffer[14] = 4;        // Size of request values in bytes
  mailboxBuffer[15] = 32;       // 32 bits per pixel

  mailboxBuffer[16] = EOS_DEV_VIDEO_MB_SET_PIXEL_ORDER;
  mailboxBuffer[17] = 4;        // Size of response values in bytes
  mailboxBuffer[18] = 4;        // Size of request values in bytes
  mailboxBuffer[19] = 1;        // RGB

  mailboxBuffer[20] = EOS_DEV_VIDEO_MB_ALLOCATE_BUFFER;
  mailboxBuffer[21] = 8;        // Size of response values in bytes
  mailboxBuffer[22] = 4;        // Size of request values in bytes
  mailboxBuffer[23] = 4096;     // Page aligned
  mailboxBuffer[24] = 0;        // reserved for response

  mailboxBuffer[25] = 0;        // End of messages

  mailboxCall((UI32)((UI64)mailboxBuffer));

  if((mailboxBuffer[1] & 0x7FFFFFFF) != 0) {
    printsln("ERROR: Could not initialize screen");
    return;
  }

  UI32 index = 2;
  while(mailboxBuffer[index] != EOS_DEV_VIDEO_MB_ALLOCATE_BUFFER) index = index + 3 + (mailboxBuffer[index + 1] / 4);
  UI32 *frameBuffer = (UI32*)((UI64)(mailboxBuffer[index + 3] & 0x3FFFFFFF));

  index = 2;
  while(mailboxBuffer[index] != EOS_DEV_VIDEO_MB_SET_PHYSICAL_SIZE) index = index + 3 + (mailboxBuffer[index + 1] / 4);
  UI32 physicalWidth  = mailboxBuffer[index + 3];
  UI32 physicalHeight = mailboxBuffer[index + 4];

  index = 2;
  while(mailboxBuffer[index] != EOS_DEV_VIDEO_MB_SET_VIRTUAL_SIZE) index = index + 3 + (mailboxBuffer[index + 1] / 4);
  UI32 virtualWidth  = mailboxBuffer[index + 3];
  UI32 virtualHeight = mailboxBuffer[index + 4];

  char str[50];
  prints("Physical screen size is ");
  ui32ToDecStr(physicalWidth, str);
  prints(str);
  prints("x");
  ui32ToDecStr(physicalHeight, str);
  printsln(str);
  prints("Virtual screen size is ");
  ui32ToDecStr(virtualWidth, str);
  prints(str);
  prints("x");
  ui32ToDecStr(virtualHeight, str);
  printsln(str);

  splash_screen(frameBuffer, virtualWidth, virtualHeight);

}

void gfx_print(char *string)
{
	UI32 index = 0;
	char current_char;
	while(1)
	{
		current_char = string[index]
		 	if (current_char == \0)
		 	{
				index--;
				current_char = string[index]; 
				break;
		 	}
		
	}
	

}
