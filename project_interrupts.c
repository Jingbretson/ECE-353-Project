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
#include "project_interrupts.h"


static volatile uint16_t PS2_X_DATA = 0;
static volatile uint16_t PS2_Y_DATA = 0;
static volatile PS2_DIR_t PS2_DIR = PS2_DIR_CENTER;




PS2_DIR_t ps2_get_direction(void)
{
	
		if (PS2_X_DATA > 2.4){
        return PS2_DIR_LEFT;
		}
    if (PS2_X_DATA < 0.85){
        return PS2_DIR_RIGHT;
		}
    if (PS2_Y_DATA > 2.4){
        return PS2_DIR_UP;
		}
    if (PS2_Y_DATA < 0.85){
        return PS2_DIR_DOWN;
		}
    return PS2_DIR_CENTER;
	
	
  
}




void TIMER1A_Handler(void)
{	
	
	if (lp_io_read_pin(RED_M)){
		lp_io_set_pin(RED_M);
	} else {
		lp_io_clear_pin(RED_M);
	}
	
    // Clear the interrupt
	TIMER1->ICR |= TIMER_ICR_TATOCINT;
}

void TIMER4A_Handler(void)
{	
	
	// sets ps2 data
		PS2_X_DATA = ADC0->SSFIFO2;
		PS2_Y_DATA = ADC0->SSFIFO2;
    PS2_DIR = ps2_get_direction();
 
    // Clear the interrupt
	TIMER4->ICR |= TIMER_ICR_TATOCINT;
}






