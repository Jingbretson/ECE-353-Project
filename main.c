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


volatile uint8_t button_pressed = false;
volatile PS2_DIR_t PS2_DIR = PS2_DIR_CENTER;

const uint8_t one[] =
{
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
};

const uint8_t zero[] = // colors reversed
{
	0x00, 0x00, 0x00, 0x00, //          
	0x00, 0x00, 0x00, 0x00, //          
	0x00, 0x00, 0x00, 0x00, //          
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x00, 0x00, 0x00, //          
	0x00, 0x00, 0x00, 0x00, //          
	0x00, 0x00, 0x00, 0x00, //          
};



const uint8_t target1_bitmap[] =
{
	0x0F, 0xFF, 0xFF, 0x00, //     ####################
	0x0F, 0xFF, 0xFF, 0x00, //     ####################
	0x0F, 0xFF, 0xFF, 0x00, //     ####################
};

const uint8_t target2_bitmap[] =
{
	0x00, 0x00, 0x00, 0x00, //   
	0x00, 0x0F, 0x00, 0x00, //            ####    
	0x00, 0x0F, 0x00, 0x00, //            ####    
	0x00, 0x0F, 0x00, 0x00, //            ####     
	0x00, 0x0F, 0x00, 0x00, //            #### 	
	0x00, 0x0F, 0x00, 0x00, //            ####    
	0x00, 0x0F, 0x00, 0x00, //            ####    
	0x00, 0x0F, 0x00, 0x00, //            ####     
	0x00, 0x0F, 0x00, 0x00, //            #### 
	0x00, 0x0F, 0x00, 0x00, //            ####    
	0x00, 0x0F, 0x00, 0x00, //            ####    
	0x00, 0x0F, 0x00, 0x00, //            ####     
	0x00, 0x0F, 0x00, 0x00, //            #### 
	0x00, 0x00, 0x00, 0x00, //   
};



const uint8_t bullet_bitmap[] =
{
	0x00, 0x00, 0x00, 0x00, //                    
	0x00, 0x0F, 0x00, 0x00, //            ####    
	0x00, 0x0F, 0x00, 0x00, //            ####    
	0x00, 0x0F, 0x00, 0x00, //            ####     
	0x00, 0x0F, 0x00, 0x00, //            ####  
	0x00, 0x00, 0x00, 0x00, //                    
  
};


const uint8_t invader_bitmap[] =
{													// 0   0   0   0   0   0   0   
	0x00, 0x00, 0x00, 0x00, //                            
	0x00, 0x00, 0x00, 0x00, //                              
	0x00, 0x01, 0x80, 0x00, //              ##              
	0x00, 0x01, 0x80, 0x00, //              ##                  
	0x00, 0x07, 0xE0, 0x00, //            ######
	0x00, 0x0F, 0xF0, 0x00, //           ########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x3F, 0xFC, 0x00, //         ############
	0x00, 0x3F, 0xFC, 0x00, //         ############
	0x00, 0x3F, 0xFC, 0x00, //         ############
	0x00, 0x3F, 0xFE, 0x00, //        ##############
	0x0F, 0xFF, 0xFF, 0xF0, //   ########################
	0x0F, 0xFF, 0xFF, 0xF0, //   ########################
	0x00, 0x3F, 0xFE, 0x00, //        ##############
	0x00, 0x3F, 0xFC, 0x00, //         ############
	0x00, 0x3F, 0xFC, 0x00, //         ############
	0x00, 0x3F, 0xFC, 0x00, //         ############
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x1F, 0xF8, 0x00, //          ##########
	0x00, 0x0F, 0xF0, 0x00, //           ########
	0x00, 0x07, 0xE0, 0x00, //            ######
	0x00, 0x01, 0x80, 0x00, //              ##              
	0x00, 0x01, 0x80, 0x00, //              ##   
	0x00, 0x01, 0x80, 0x00, //              
	0x00, 0x00, 0x00, 0x00, //                                 
};

// write to the red LED's near the four buttons
// param led: which led to write to (0 is bottom, 7 is top)
// param value: 1 is on, 0 is off
void write_shots(uint8_t shots)
{
	io_expander_write_reg(IO_EXPANDER_I2C_BASE, MCP23017_GPIOA_R, (1 << shots) - 1);
}

// poll buttons. only for testing, will use interrupts
uint8_t io_exp_button_poll()
{
	uint8_t current;
	io_expander_read_reg(IO_EXPANDER_I2C_BASE, MCP23017_GPIOB_R, &current);
	return current;
}

uint16_t load_score()
{
	uint8_t score_low;
	uint8_t score_high;
	eeprom_byte_read(EEPROM_I2C_BASE, SCORE_ADDR, &score_low);
	eeprom_byte_read(EEPROM_I2C_BASE, SCORE_ADDR + 1, &score_high);
	return (uint16_t)(score_high << 8 | score_low);
}

void save_score(uint16_t score)
{
	eeprom_byte_write(EEPROM_I2C_BASE, SCORE_ADDR, score & 0xFF);
	eeprom_byte_write(EEPROM_I2C_BASE, SCORE_ADDR + 1, score >> 8);
}

bool button_debounce_fsm(void)
{
  static DEBOUNCE_STATES state = DEBOUNCE_ONE;
  bool pin_logic_level;
  
  pin_logic_level = lp_io_read_pin(SW2_BIT);
  
  switch (state)
  {
    case DEBOUNCE_ONE:
    {
      if(pin_logic_level)
      {
        state = DEBOUNCE_ONE;
      }
      else
      {
        state = DEBOUNCE_1ST_ZERO;
      }
      break;
    }
    case DEBOUNCE_1ST_ZERO:
    {
      if(pin_logic_level)
      {
        state = DEBOUNCE_ONE;
      }
      else
      {
        state = DEBOUNCE_2ND_ZERO;
      }
      break;
    }
    case DEBOUNCE_2ND_ZERO:
    {
      if(pin_logic_level)
      {
        state = DEBOUNCE_ONE;
      }
      else
      {
        state = DEBOUNCE_PRESSED;
      }
      break;
    }
    case DEBOUNCE_PRESSED:
    {
      if(pin_logic_level)
      {
        state = DEBOUNCE_ONE;
      }
      else
      {
        state = DEBOUNCE_PRESSED;
      }
      break;
    }
    default:
    {
      while(1){};
    }
  }
  
  if(state == DEBOUNCE_2ND_ZERO )
  {
    return true;
  }
  else
  {
    return false;
  }
}


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
	#if 1

	bool gameTime = true;
	uint8_t bulletDir [8];
	uint16_t bullets [8][2];
	uint8_t targetHit [4];
	uint16_t targets [4][2];
	int shots = 8;
	uint8_t shipX = 120;
	uint8_t shipY = 160;
	uint8_t bulletNum = -1;
	uint8_t button_data;
	uint16_t endScore[4][2];
	int j = 0;
	int dir0 =1;
	int dir1 = 1;
	int dir2 = 1;
	int dir3 = 1;
	int score = 0;
	uint8_t touch_event;
	int x = 0;
	int colors[5];
	int color = LCD_COLOR_GREEN;
	
	colors[0] = LCD_COLOR_GREEN;
	colors[1] = LCD_COLOR_BLUE;
	colors[2] = LCD_COLOR_RED;
	colors[3] = LCD_COLOR_CYAN;
	colors[4] = LCD_COLOR_YELLOW;
	
	
	for (j = 0; j<8; j++) bulletDir[j] = 0;
	for (j = 0; j<4; j++) targetHit[j] = 0;
	j = 0;
	
	targets[0][0] = 25;
	targets[0][1] = 25;
	targets[1][0] = 220;
	targets[1][1] = 25;
	targets[2][0] = 220;
	targets[2][1] = 300;
	targets[3][0] = 25;
	targets[3][1] = 300;
	
	
	
	
	initializeBoard();
	
	lcd_draw_image(shipX, 32, shipY, 26, invader_bitmap, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
	
	while (gameTime){
		
		touch_event = ft6x06_read_td_status();
		
		if (touch_event > 1){
			x++;
			if (x>=5) x=0;
		}
		
		color = colors[x];
		
		write_shots(shots);
		
		lcd_draw_image(shipX, 32, shipY, 26, invader_bitmap, color, LCD_COLOR_BLACK);

		
		// if button is pressed send bullet out in correct direction
		if (button_pressed && shots > 0) {
			// clear flag first. if interrupt happens between
			// io_exp_poll and clearing the flag, bad state entered
			button_pressed = false;
			
		button_debounce_fsm();
			// mask for buttons
			button_data = io_exp_button_poll() & 0x0F;
			
		switch(button_data)
		{
			case 0xb: // left
			{
				bulletNum++;
				bullets[bulletNum][0] = shipX-16;
				bullets[bulletNum][1] = shipY;
				bulletDir[bulletNum] = 1;
				lcd_draw_image(bullets[bulletNum][0], 32, bullets[bulletNum][1], 6, bullet_bitmap, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
				write_shots(shots--);
				break;
			}
			case 0xd: // bottom
			{
				bulletNum++;
				bullets[bulletNum][0] = shipX+2;
				bullets[bulletNum][1] = shipY+15;
				bulletDir[bulletNum] = 2;
				lcd_draw_image(bullets[bulletNum][0], 32, bullets[bulletNum][1], 6, bullet_bitmap, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
				write_shots(shots--);
				break;
			}
			case 0x7: // right
			{
					bulletNum++;
				bullets[bulletNum][0] = shipX+20;
				bullets[bulletNum][1] = shipY;
				bulletDir[bulletNum] = 3;
				lcd_draw_image(bullets[bulletNum][0], 32, bullets[bulletNum][1], 6, bullet_bitmap, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
				write_shots(shots--);
				break;
			}
			case 0xe: // top
			{
				bulletNum++;
				bullets[bulletNum][0] = shipX+2;
				bullets[bulletNum][1] = shipY-15;
				bulletDir[bulletNum] = 4;
				lcd_draw_image(bullets[bulletNum][0], 32, bullets[bulletNum][1], 6, bullet_bitmap, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
				write_shots(shots--);
				break;
			}
			default:
			{
				break;
			}
		}
		}

	
		
		//move bullets
		
		for (j=0; j < 8; j++){
			switch(bulletDir[j]){
				case 1:
				{
					bullets[j][0]--;
					if(bullets[j][0] <= 10) {
						bulletDir[j] = 0;
					  lcd_draw_image(bullets[j][0], 32, bullets[j][1], 6, bullet_bitmap, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
						bullets[j][0] = 0;
					  bullets[j][1] = 0;
						if (shots <= 0) gameTime = false;
					}
					if (targetHit[3] == 0 && bullets[j][0] == 25 && (targets[3][1] + 12) >= bullets[j][1] && (targets[3][1] - 12) <= bullets[j][1]){
						targetHit[3] = 1;
						score++;
					}
						
					lcd_draw_image(bullets[j][0], 32, bullets[j][1], 6, bullet_bitmap, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
					break;
				}
				case 2:
				{
					bullets[j][1]++;
					if(bullets[j][1] >= 310) {
						bulletDir[j] = 0;
					  lcd_draw_image(bullets[j][0], 32, bullets[j][1], 6, bullet_bitmap, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
						bullets[j][0] = 0;
					  bullets[j][1] = 0;
						if (shots <= 0) gameTime = false;
					}
					if (targetHit[2] == 0 && bullets[j][1] == 300 && (targets[2][0] + 12) >= bullets[j][0] && (targets[2][0] - 12) <= bullets[j][0]){
						targetHit[2] = 1;
						score++;
					}
					lcd_draw_image(bullets[j][0], 32, bullets[j][1], 6, bullet_bitmap, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
					break;
				}
				case 3:
				{
					bullets[j][0]++;
					if(bullets[j][0] >= 230) {
						bulletDir[j] = 0;
					  lcd_draw_image(bullets[j][0], 32, bullets[j][1], 6, bullet_bitmap, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
						bullets[j][0] = 0;
					  bullets[j][1] = 0;
						if (shots <= 0) gameTime = false;
					}
					if (targetHit[1] == 0 &&bullets[j][0] == 220 && (targets[1][1] + 12) >= bullets[j][1] && (targets[1][1] - 12) <= bullets[j][1]){
						targetHit[1] = 1; 
						score++;
					}
					lcd_draw_image(bullets[j][0], 32, bullets[j][1], 6, bullet_bitmap, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
					break;
				}
				case 4:
				{
					bullets[j][1]--;
					if(bullets[j][1] <= 10){
						bulletDir[j] = 0;
					  lcd_draw_image(bullets[j][0], 32, bullets[j][1], 6, bullet_bitmap, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
						bullets[j][0] = 0;
					  bullets[j][1] = 0;
						if (shots <= 0) gameTime = false;
					}
					if (targetHit[0] == 0 && bullets[j][1] == 25 && (targets[0][0] + 12) >= bullets[j][0] && (targets[0][0] - 12) <= bullets[j][0]){
						targetHit[0] = 1;
						score++;
					}
					lcd_draw_image(bullets[j][0], 32, bullets[j][1], 6, bullet_bitmap, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
					break;
				}
				default:
				{
					break;
				}
			}
				lcd_draw_image(bullets[j][0], 32, bullets[j][1], 6, bullet_bitmap, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
		}
		
		
		
		
		// move ship in direction stick is moved
		
		
		 switch (PS2_DIR)												
    {
      case PS2_DIR_RIGHT:													
			{
				if(shipX+1 <= 180){
					shipX++;
				}
					
        break;
      }
      case PS2_DIR_LEFT:
      {
				if (shipX-1 >= 50){
					shipX--;
				}
        
        break;
      }
      case PS2_DIR_DOWN:
      {
				if (shipY+1 <= 250){
					shipY++;
				}
        break;
      }
      case PS2_DIR_UP:
      {
				if (shipY-1 >= 50){
					shipY--;
				}
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
		
		
	// move targets
	
	if (targetHit[0] == 0){
	lcd_draw_image(targets[0][0], 32, targets[0][1], 3, target1_bitmap, LCD_COLOR_RED, LCD_COLOR_BLACK);
	} else {
			lcd_draw_image(targets[0][0], 32, targets[0][1], 3, target1_bitmap, LCD_COLOR_BLACK, LCD_COLOR_BLACK);

	}
	if (targetHit[1] == 0){
	lcd_draw_image(targets[1][0], 32, targets[1][1], 14, target2_bitmap, LCD_COLOR_RED, LCD_COLOR_BLACK);
	} else {
			lcd_draw_image(targets[1][0], 32, targets[1][1], 14, target2_bitmap, LCD_COLOR_BLACK, LCD_COLOR_BLACK);

	}
	if (targetHit[2] == 0){
	lcd_draw_image(targets[2][0], 32, targets[2][1], 3, target1_bitmap, LCD_COLOR_RED, LCD_COLOR_BLACK);
	} else {
			lcd_draw_image(targets[2][0], 32, targets[2][1], 3, target1_bitmap, LCD_COLOR_BLACK, LCD_COLOR_BLACK);

	}
	if (targetHit[3] == 0){
	lcd_draw_image(targets[3][0], 32, targets[3][1], 14, target2_bitmap, LCD_COLOR_RED, LCD_COLOR_BLACK);
	} else {
			lcd_draw_image(targets[3][0], 32, targets[3][1], 14, target2_bitmap, LCD_COLOR_BLACK, LCD_COLOR_BLACK);

	}
	
	if (targets[0][0] >= 220) dir0 = -1;
	if (targets[0][0] <= 20) dir0 = 1;
	if (targets[1][1] >= 300) dir1 = -1;
	if (targets[1][1] <= 20) dir1 = 1;
	if (targets[2][0] >= 220) dir2 = -1;
	if (targets[2][0] <= 20) dir2 = 1;
	if (targets[3][1] >= 300) dir3 = -1;
	if (targets[3][1] <= 20) dir3 = 1;
	
	targets[0][0] += dir0;
	targets[1][1] += dir1;
	targets[2][0] += dir2;
	targets[3][1] += dir3;
	
	
	if((targetHit[0] == 1 && targetHit[1] == 1 && targetHit[2] == 1 && targetHit[3] == 1)){
		gameTime = false;
	}
	
	write_shots(shots);

	}
	lcd_clear_screen(LCD_COLOR_BLACK);
	
	endScore[0][0] = 100;
	endScore[0][1] = 160;
	endScore[1][0] = 130;
	endScore[1][1] = 160;
	endScore[2][0] = 160;
	endScore[2][1] = 160;
	endScore[3][0] = 70;
	endScore[3][1] = 160;
	
	if (score == 0){
		lcd_draw_image(endScore[0][0], 32, endScore[0][1], 22, zero, LCD_COLOR_BLACK, LCD_COLOR_RED);
	} else {	
	for (j = 0; j < score; j++){
		lcd_draw_image(endScore[j][0], 32, endScore[j][1], 22, one, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
	}
}
	
	
	
	#endif
}
