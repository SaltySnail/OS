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
#include "print.h"

#define EOS_DEV_VIDEO_MB_ALLOCATE_BUFFER   0x40001
#define EOS_DEV_VIDEO_MB_SET_PHYSICAL_SIZE 0x48003
#define EOS_DEV_VIDEO_MB_SET_VIRTUAL_SIZE  0x48004
#define EOS_DEV_VIDEO_MB_SET_DEPTH         0x48005
#define EOS_DEV_VIDEO_MB_SET_PIXEL_ORDER   0x48006

void init_character(letter *teken, UI32 bit0, UI32 bit1, UI32 bit2, UI32 bit3, UI32 bit4, UI32 bit5, UI32 bit6, UI32 bit7, UI32 bit8, UI32 bit9, UI32 bit10, UI32 bit11, UI32 bit12, UI32 bit13, UI32 bit14, UI32 bit15, UI32 bit16, UI32 bit17, UI32 bit18, UI32 bit19, UI32 bit20, UI32 bit21, UI32 bit22, UI32 bit23, UI32 bit24, UI32 bit25, UI32 bit26, UI32 bit27, UI32 bit28, UI32 bit29, UI32 bit30, UI32 bit31, UI32 bit32, UI32 bit33, UI32 bit34)
{
 teken->bitmap[0][0] = bit0;
 teken->bitmap[0][1] = bit1;
 teken->bitmap[0][2] = bit2;
 teken->bitmap[0][3] = bit3;
 teken->bitmap[0][4] = bit4;
 teken->bitmap[1][0] = bit5;
 teken->bitmap[1][1] = bit6;
 teken->bitmap[1][2] = bit7;
 teken->bitmap[1][3] = bit8;
 teken->bitmap[1][4] = bit9;
 teken->bitmap[2][0] = bit10;
 teken->bitmap[2][1] = bit11;
 teken->bitmap[2][2] = bit12;
 teken->bitmap[2][3] = bit13;
 teken->bitmap[2][4] = bit14;
 teken->bitmap[3][0] = bit15;
 teken->bitmap[3][1] = bit16;
 teken->bitmap[3][2] = bit17;
 teken->bitmap[3][3] = bit18;
 teken->bitmap[3][4] = bit19;
 teken->bitmap[4][0] = bit20;
 teken->bitmap[4][1] = bit21;
 teken->bitmap[4][2] = bit22;
 teken->bitmap[4][3] = bit23;
 teken->bitmap[4][4] = bit24;
 teken->bitmap[5][0] = bit25;
 teken->bitmap[5][1] = bit26;
 teken->bitmap[5][2] = bit27;
 teken->bitmap[5][3] = bit28;
 teken->bitmap[5][4] = bit29;
 teken->bitmap[6][0] = bit30;
 teken->bitmap[6][1] = bit31;
 teken->bitmap[6][2] = bit32;
 teken->bitmap[6][3] = bit33;
 teken->bitmap[6][4] = bit34;
 teken->bitmap[7][0] = bit15;
 teken->bitmap[7][1] = bit16;
 teken->bitmap[7][2] = bit17;
 teken->bitmap[7][3] = bit18;
 teken->bitmap[7][4] = bit19;
}

void init_character_set(font *font)
{
	init_character(font->tekens[0],
	0, 0, 0, 0, 0,
    	0, 0, 0, 0, 0,
    	0, 0, 0, 0, 0,
    	0, 0, 0, 0, 0,
    	0, 0, 0, 0, 0,
    	0, 0, 0, 0, 0,
    	0, 0, 0, 0, 0);
/*
	init_character(font->tekens[1],
    0  , 0  , 1  , 0  , 0  ,
    0  , 0  , 1  , 0  , 0  ,
    0  , 0  , 1  , 0  , 0  ,
    0  , 0  , 1  , 0  , 0  ,
    0  , 0  , 1  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 1  , 0  , 0 );

	init_character(font->tekens[2],
    0  , 0  , 1  , 0  , 1  ,
    0  , 0  , 1  , 0  , 1  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0 );
    
	init_character(font->tekens[3],
    0  , 1  , 0  , 1  , 0  ,
    0  , 1  , 0  , 1  , 0  ,
    1  , 1  , 1  , 1  , 1  ,
    0  , 1  , 0  , 1  , 0  ,
    1  , 1  , 1  , 1  , 1  ,
    0  , 1  , 0  , 1  , 0  ,
    0  , 1  , 0  , 1  , 0);

	init_character(font->tekens[4],
    0  , 0  , 1  , 0  , 0  ,
    0  , 1  , 1  , 1  , 1  ,
    1  , 0  , 1  , 0  , 0  ,
    0  , 1  , 1  , 1  , 0  ,
    0  , 0  , 1  , 0  , 1  ,
    1  , 1  , 1  , 1  , 0  ,
    0  , 0  , 1  , 0  , 0);
 
     init_character(font->tekens[4],      
    0  , 0  , 1  , 0  , 0  ,
    0  , 1  , 1  , 1  , 1  ,
    1  , 0  , 1  , 0  , 0  ,
    0  , 1  , 1  , 1  , 0  ,
    0  , 0  , 1  , 0  , 1  ,
    1  , 1  , 1  , 1  , 0  ,
    0  , 0  , 1  , 0  , 0);
  
     init_character(font->tekens[5],      
    1  , 1  , 0  , 0  , 0  ,
    1  , 1  , 0  , 0  , 1  ,
    0  , 0  , 0  , 1  , 0  ,
    0  , 0  , 1  , 0  , 0  ,
    0  , 1  , 0  , 0  , 0  ,
    0  , 0  , 0  , 1  , 1  ,
    0  , 0  , 0  , 1  , 1);
  
     init_character(font->tekens[6],      
    0  , 1  , 1  , 1  , 0  ,
    1  , 0  , 0  , 1  , 0  ,
    1  , 0  , 1  , 0  , 0  ,
    0  , 1  , 0  , 0  , 0  ,
    1  , 0  , 1  , 0  , 1  ,
    1  , 0  , 0  , 1  , 0  ,
    0  , 1  , 1  , 0  , 1);
    
     init_character(font->tekens[7],      
  
    0  , 0  , 0  , 1  , 0  ,
    0  , 0  , 0  , 1  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 );
   
     init_character(font->tekens[8],      
    0  , 0  , 1  , 0  , 0  ,
    0  , 1  , 0  , 0  , 0  ,
    1  , 0  , 0  , 0  , 0  ,
    1  , 0  , 0  , 0  , 0  ,
    1  , 0  , 0  , 0  , 0  ,
    0  , 1  , 0  , 0  , 0  ,
    0  , 0  , 1  , 0  , 0);
   
     init_character(font->tekens[9],      

    0  , 0  , 1  , 0  , 0  ,
    0  , 0  , 0  , 1  , 0  ,
    0  , 0  , 0  , 0  , 1  ,
    0  , 0  , 0  , 0  , 1  ,
    0  , 0  , 0  , 0  , 1  ,
    0  , 0  , 0  , 1  , 0 ,
    0  , 0  , 1  , 0  , 0);

     init_character(font->tekens[10],      
  
    1  , 0  , 1  , 0  , 1  ,
    0  , 1  , 1  , 1  , 0  ,
    1  , 1  , 1  , 1  , 1  ,
    0  , 1  , 1  , 1  , 0  ,
    1  , 0  , 1  , 0  , 1  ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 );

     init_character(font->tekens[11],      
  
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 1  , 0  , 0  ,
    0  , 0  , 1  , 0  , 0  ,
    1  , 1  , 1  , 1  , 1  ,
    0  , 0  , 1  , 0  , 0  ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 );

     init_character(font->tekens[12],      
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 1  , 0  , 0  ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 1  , 0  , 0  , 0 );  
 
     init_character(font->tekens[13],      
  
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    1  , 1  , 1  , 1  , 1  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 );    
 
     init_character(font->tekens[14],      
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 1  , 0  , 0  );
  
     init_character(font->tekens[15],      
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 1  ,
    0  , 0  , 0  , 1  , 0  ,
    0  , 0  , 1  , 0  , 0  ,
    0  , 1  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0 );     

     init_character(font->tekens[16],      
  
    0  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 1  , 1 ,
    1  , 0  , 1  , 0  , 1 ,
    1  , 1  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 0 );

     init_character(font->tekens[17],      
  
    0  , 0  , 1  , 0  , 0 ,
    0  , 1  , 1  , 0  , 0 ,
    1  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    1  , 1  , 1  , 1  , 1);
  
     init_character(font->tekens[18],      
    0  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 1  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 1  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 1);

     init_character(font->tekens[19],      
    0  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 0  , 1  , 1  , 0 ,
    0  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 0);

     init_character(font->tekens[20],      
    0  , 0  , 1  , 1  , 0 ,
    0  , 1  , 0  , 1  , 0 ,
    1  , 0  , 0  , 1  , 0 ,
    1  , 1  , 1  , 1  , 1 ,
    0  , 0  , 0  , 1  , 0 ,
    0  , 0  , 0  , 1  , 0 ,
    0  , 0  , 0  , 1  , 0 );
 
     init_character(font->tekens[21],       
    1  , 1  , 1  , 1  , 1 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 0 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    1  , 1  , 1  , 1  , 0);

     init_character(font->tekens[22],      
   0  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 0);

     init_character(font->tekens[23],      
    1  , 1  , 1  , 1  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 1  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 );

     init_character(font->tekens[24],      
    0  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 0);
  
     init_character(font->tekens[25],      
    0  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 0);
  
     init_character(font->tekens[26],      
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0);

     init_character(font->tekens[27],        
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 1  , 0  , 0  , 0 );
 
     init_character(font->tekens[28],      
    0  , 0  , 0  , 1  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 1  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    0  , 1  , 0  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 0  , 1  , 0 );
      
     init_character(font->tekens[29],      
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 1 ,
    0  , 0  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 1 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0);

     init_character(font->tekens[30],      
    0  , 1  , 0  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 0  , 1  , 0 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 1  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 1  , 0  , 0  , 0);
  
     init_character(font->tekens[31],      
    0  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 1  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 );

     init_character(font->tekens[32],      
    0  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 1  , 1  , 1 ,
    1  , 0  , 1  , 0  , 1 ,
    1  , 0  , 1  , 1  , 1 ,
    1  , 0  , 0  , 0  , 0 ,
    0  , 1  , 1  , 1  , 0 );

     init_character(font->tekens[33],      
    0  , 1  , 1  , 1  , 0 , 
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 1  , 1  , 1  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1);
  
    init_character(font->tekens[34],      
    1  , 1  , 1  , 1  , 0 , 
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 1  , 1  , 1  , 0);
  
    init_character(font->tekens[35],      
    0  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 0 );

    init_character(font->tekens[36],      
    1  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 1  , 1  , 1  , 0 ); 

    init_character(font->tekens[37],      
    1  , 1  , 1  , 1  , 1 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 1);

    init_character(font->tekens[38],      
    1  , 1  , 1  , 1  , 1 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 );
    
    init_character(font->tekens[39],      
    0  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 1  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 0);
  
    init_character(font->tekens[40],      
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 1  , 1  , 1  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1);
  
    init_character(font->tekens[41],      
    1  , 1  , 1  , 1  , 1 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    1  , 1  , 1  , 1  , 1 );

    init_character(font->tekens[42],      
    1  , 1  , 1  , 1  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 0);

    init_character(font->tekens[43],      
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 1  , 0 ,
    1  , 1  , 1  , 0  , 0 ,
    1  , 0  , 0  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 );
 
    init_character(font->tekens[44],      
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 1  );

    init_character(font->tekens[45],      
    1  , 0  , 0  , 0  , 1 ,
    1  , 1  , 0  , 1  , 1 ,
    1  , 0  , 1  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 );

    init_character(font->tekens[46],      
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 1  , 0  , 0  , 1 ,
    1  , 0  , 1  , 0  , 1 ,
    1  , 0  , 0  , 1  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1);
  
    init_character(font->tekens[47],
    0  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 0 );

    init_character(font->tekens[48],      
    1  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 );
  
    init_character(font->tekens[49],      
    0  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 1  , 0  , 1 ,
    1  , 0  , 0  , 1  , 0 ,
    0  , 1  , 1  , 0  , 1 );

    init_character(font->tekens[50],      
    1  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 );
    
    init_character(font->tekens[51],      
    0  , 1  , 1  , 1  , 1 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    0  , 1  , 1  , 1  , 0 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    1  , 1  , 1  , 1  , 0 ); 

    init_character(font->tekens[52],      
    1  , 1  , 1  , 1  , 1 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 );
    
    init_character(font->tekens[53],      
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 0 );

    init_character(font->tekens[54],      
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 0  , 1  , 0 ,
    0  , 0  , 1  , 0  , 0 );
 
    init_character(font->tekens[55],      
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 1  , 0  , 1 ,
    1  , 1  , 0  , 1  , 1 ,
    1  , 0  , 0  , 0  , 1 );

    init_character(font->tekens[56],      
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 0  , 1  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 1  , 0  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 );
  
    init_character(font->tekens[57],      
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 0  , 1  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0);
  
    init_character(font->tekens[58],      
    1  , 1  , 1  , 1  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 1  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 1  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 1);
  
    init_character(font->tekens[59],      
    1  , 1  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 1  , 0  , 0  , 0);
  
    init_character(font->tekens[60],      
    0  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    0  , 1  , 0  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 0  , 1  , 0 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 0  , 0 );
  
     init_character(font->tekens[61],      
    0  , 0  , 0  , 0  , 0 , 
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 );
  
     init_character(font->tekens[62],      
    0  , 0  , 1  , 0  , 0 ,
    0  , 1  , 0  , 1  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0);
    
    init_character(font->tekens[63],      
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 1);

    init_character(font->tekens[64],      
    0  , 1  , 0  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0);

    init_character(font->tekens[65],      
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 1  , 1  , 1  , 0 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 1);

    init_character(font->tekens[66],      
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 1  , 1  , 1  , 0);

    init_character(font->tekens[67],      
    0  , 0  , 0  , 0  , 0 ,
    0  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 0);

    init_character(font->tekens[68],      
    0  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 1 );

     init_character(font->tekens[69],     
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 1  , 1  , 1  , 1 ,
    1  , 0  , 0  , 0  , 0 ,
    0  , 1  , 1  , 1  , 1 );
  
     init_character(font->tekens[70],      
    0  , 0  , 1  , 1  , 0 ,
    0  , 1  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 1 ,
    0  , 1  , 0  , 0  , 0 ,
    0  , 1  , 0  , 0  , 0 ,
    0  , 1  , 0  , 0  , 0 ,
    0  , 1  , 0  , 0  , 0 );

     init_character(font->tekens[71],        
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 1  , 1  , 1  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 0 );

     init_character(font->tekens[72],      
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 );

     init_character(font->tekens[73],      
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 1  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 1  , 1  , 1  , 1 );

     init_character(font->tekens[74],      
    0  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 1  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 0 );
  
     init_character(font->tekens[75],      
   1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 1  , 0 ,
    1  , 1  , 1  , 0  , 0 ,
    1  , 0  , 0  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 );

     init_character(font->tekens[76],      
  
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    0  , 1  , 1  , 1  , 0 );
  
     init_character(font->tekens[77],      
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    1  , 1  , 0  , 1  , 0 ,
    1  , 0  , 1  , 0  , 1 ,
    1  , 0  , 1  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 );
    
     init_character(font->tekens[78],      
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 );

     init_character(font->tekens[79],      
  
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 0 ); 
  
     init_character(font->tekens[80],      
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 1  , 1  , 1  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 );
  
 

     init_character(font->tekens[81],      
  
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 1  , 1  , 1  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 0  , 1 );
  
     init_character(font->tekens[82],      
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    1  , 0  , 1  , 1  , 0 ,
    1  , 1  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 );

     init_character(font->tekens[83],      
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 1  , 1  , 1  , 1 ,
    1  , 0  , 0  , 0  , 0 ,
    0  , 1  , 1  , 1  , 0 ,
    0  , 0  , 0  , 0  , 1 ,
    1  , 1  , 1  , 1  , 0 );

     init_character(font->tekens[84],      
    0  , 1  , 0  , 0  , 0 ,
    0  , 1  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 0 ,
    0  , 1  , 0  , 0  , 0 ,
    0  , 1  , 0  , 0  , 0 ,
    0  , 1  , 0  , 0  , 1 ,
    0  , 0  , 1  , 1  , 0 );
  
     init_character(font->tekens[85],      
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 1 );
  
     init_character(font->tekens[86],      
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 0  , 1  , 0 ,
    0  , 0  , 1  , 0  , 0 );
  
     init_character(font->tekens[87],      
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 1  , 0  , 1 ,
    0  , 1  , 0  , 1  , 0 );
 
     init_character(font->tekens[88],      
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 0  , 1  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 1  , 0  , 1  , 0 ,
    1  , 0  , 0  , 0  , 1 );

     init_character(font->tekens[89],      
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 1 ,
    1  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 1 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 1  , 1  , 1  , 0 );
   
     init_character(font->tekens[90],      
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 1 ,
    0  , 0  , 0  , 1  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 1  , 0  , 0  , 0 ,
    1  , 1  , 1  , 1  , 1 );

     init_character(font->tekens[91],      
    0  , 0  , 1  , 0  , 0 ,
    0  , 1  , 0  , 0  , 0 ,
    0  , 1  , 0  , 0  , 0 ,
    1  , 0  , 0  , 0  , 0 ,
    0  , 1  , 0  , 0  , 0 ,
    0  , 1  , 0  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 );

     init_character(font->tekens[92],      
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 1  , 0  , 0 );

     init_character(font->tekens[93],      
    0  , 0  , 1  , 0  , 0 ,
    0  , 0  , 0  , 1  , 0 ,
    0  , 0  , 0  , 1  , 0 ,
    0  , 0  , 0  , 0  , 1 ,
    0  , 0  , 0  , 1  , 0 ,
    0  , 0  , 0  , 1  , 0 ,
    0  , 0  , 1  , 0  , 0 );

    init_character(font->tekens[94],      
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 1  , 0  , 0  , 1 ,
    1  , 0  , 1  , 1  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 ,
    0  , 0  , 0  , 0  , 0 );
    */
}

void gfx_print(char *string, font *font, UI32 virtualWidth, UI32 virtualHeight, UI32 *frameBuffer)
{
	printsln("Now printing");
	(void)virtualHeight;
	UI32 index = 0, cursor = virtualWidth + 1, y, x;
	char current_char;
	while(*(string+index))
	{
		current_char = string[index];
		 if (&current_char == "\0")
		 {
				//index--;
				//current_char = string[index]; 
				break;
		 }
		//print (maar check eerst welk teken het om gaat)
		if (&current_char == " ")
		{
			for (y = 0; y < 7; y++)
			{
				for (x = 0; x < 5; x++)
				{
					if (font->tekens[0]->bitmap[y][x] == 1)
					{
						printsln("Teken 0: ");
					/*	prints("x: ");
						prints((char *)x);
						prints("y: ");
						prints((char *)y);
						printsln((char *)font->tekens[0]->bitmap[y][x]);*/

						frameBuffer[cursor+x+y*virtualWidth] = 0x00FFFFFF;
					}
				}
			}
		}	
		if (&current_char == "!")
		{	
			for (y = 0; y < 7; y++)
			{
				for (x = 0; x < 5; x++)
				{
					if (font->tekens[1]->bitmap[y][x] == 1)
					{
						printsln("Teken 1: ");
					/*	prints("x: ");
						prints(&x);
						prints("y: ");
						prints(&y);
						printsln(&font->tekens[1]->bitmap[y][x]);*/
						frameBuffer[cursor+x+y*virtualWidth] = 0x00FFFFFF;
					}
				}
			}
		}
		index++;
		cursor += 6;

	}
	

}

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
  for(; index > (virtualHeight * virtualWidth / 3)*2; index--) { //groen
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
	if (index % 2)
	{
    		frameBuffer[index] = 0x00F0F0F0;
	}
	else
	{
    		frameBuffer[index] = 0x00FF00FF;
	}
  }
  for(; index < (virtualHeight * virtualWidth / 3)*2; index++) { //groen
	
	if (index % 2)
	{
    		frameBuffer[index] = 0x000F0F0F;
	}
	else
	{
    		frameBuffer[index] = 0x00FFFFFF;
	}
  }
  for(; index < virtualHeight * virtualWidth; index++) { 
  
	if (index % 2)
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
  font font;
  //init_character_set(&font);
  prints("Joehoe \n");
  
  init_character(font->tekens[1],
    0  , 0  , 1  , 0  , 0  ,
    0  , 0  , 1  , 0  , 0  ,
    0  , 0  , 1  , 0  , 0  ,
    0  , 0  , 1  , 0  , 0  ,
    0  , 0  , 1  , 0  , 0  ,
    0  , 0  , 0  , 0  , 0  ,
    0  , 0  , 1  , 0  , 0 );



  char my_string[] = "! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !  ! ! ! ! !  !! !  ! ! ! !  !!!!! ! ! ! ! ! !!!!!!!!!!!!!!!!!!!!!!!!!!";
  gfx_print(my_string, &font, virtualWidth, virtualHeight, frameBuffer);
}

