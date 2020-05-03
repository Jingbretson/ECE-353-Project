// Copyright (c) 2015-19, Joe Krachey
// All rights reserved.
//
// Redistribution and use in source or binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in source form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "main.h"


const uint8_t target_bitmap[] =
{
	0x00, 0x7F, 0xE0, 0x00, //          ##########
	0x01, 0xFF, 0xF8, 0x00, //        ##############
	0x07, 0xFF, 0xFE, 0x00, //      ##################
	0x0F, 0xFF, 0xFF, 0x00, //     ####################
	0x07, 0xFF, 0xFE, 0x00, //      ##################
	0x01, 0xFF, 0xF8, 0x00, //        ##############
	0x00, 0x7F, 0xE0, 0x00, //          ##########
};



const uint8_t bullet_bitmap[] =
{
	0x00, 0x06, 0x00, 0x00, //              ##
	0x00, 0x0F, 0x00, 0x00, //             ####
	0x00, 0x1F, 0x80, 0x00, //            ######     
  0x00, 0x06, 0x00, 0x00, //              ##
  0x00, 0x06, 0x00, 0x00, //              ##
  0x00, 0x06, 0x00, 0x00, //              ## 
  0x00, 0x06, 0x00, 0x00, //              ## 	
};


const uint8_t invader_bitmap[] =
{													// 0   0   0   0   0   0   0   
	0x00, 0x06, 0x00, 0x00, //              ##              
	0x00, 0x06, 0x00, 0x00, //              ##              
	0x00, 0x1F, 0x80, 0x00, //            ######
	0x00, 0x3F, 0xA0, 0x00, //           ########
	0x00, 0x7F, 0xE0, 0x00, //          ##########
	0x00, 0x7F, 0xE0, 0x00, //          ##########
	0x00, 0x7F, 0xE0, 0x00, //          ##########
	0x00, 0x7F, 0xE0, 0x00, //          ##########
	0x00, 0xFF, 0xF0, 0x00, //         ############
	0x00, 0xFF, 0xF0, 0x00, //         ############
	0x00, 0xFF, 0xF0, 0x00, //         ############
	0x01, 0xFF, 0xF8, 0x00, //        ##############
	0x01, 0xFF, 0xF8, 0x00, //        ##############
	0x03, 0xFF, 0xFD, 0x00, //       ################
	0x07, 0xFF, 0xFE, 0x00, //      ##################
	0x0F, 0xFF, 0xFF, 0x00, //     ####################
	0x1F, 0xFF, 0xFF, 0x80, //    ######################
	0x3F, 0xFF, 0xFF, 0xC0, //   ########################
	0x3F, 0xFF, 0xFF, 0xC0, //   ########################
	0x3F, 0xFF, 0xFF, 0xC0, //   ########################
	0x3F, 0xFF, 0xFF, 0xC0, //   ########################
	0x3F, 0xFF, 0xFF, 0xC0, //   ########################
	0x3F, 0xFF, 0xFF, 0xC0, //   ########################
	0x3F, 0xFF, 0xFF, 0xC0, //   ########################
	0xFF, 0xFF, 0xFF, 0xF0, // ############################              
	0xFF, 0xFF, 0xFF, 0xF0, // ############################                      
};



//*****************************************************************************
//*****************************************************************************
void DisableInterrupts(void)
{
  __asm {
         CPSID  I
  }
}

//*****************************************************************************
//*****************************************************************************
void EnableInterrupts(void)
{
  __asm {
    CPSIE  I
  }
}


//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
	initializeBoard();
	while(1){
	}
	
	bool gameTime = true;
	uint16_t bullets [20][2];
	bool moveBullet [20];
	
	
	
	
	lcd_draw_image(210, 32, 300, 24, invader_bitmap, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
	
	while (gameTime){
		
		
		// if button is pressed send bullet out in correct direction
		
		
		// move ship in direction stick is moved
		 switch (1)												
    {
      case PS2_DIR_RIGHT:													
			{
				lcd_draw_image(210, 32, 300, 24, bullet_bitmap, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
        break;
      }
      case PS2_DIR_LEFT:
      {
        lcd_draw_image(210, 32, 300, 24, bullet_bitmap, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
        
        break;
      }
      case PS2_DIR_DOWN:
      {
				lcd_draw_image(210, 32, 300, 24, bullet_bitmap, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
        break;
      }
      case PS2_DIR_UP:
      {
				lcd_draw_image(210, 32, 300, 24, bullet_bitmap, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
        break;
      }
      case PS2_DIR_CENTER:
      {
        // Do nothing
        break;
      }
      default:
      {
        break;
      }
    }
		
		// check if a target is hit
		
		// check if ship is hit by a target
		
		// remove bullets that hit end of screen
		
		// removing hit targets
		
		
		
		
	}
	
	

	
	
}
