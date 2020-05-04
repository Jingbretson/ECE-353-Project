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





PS2_DIR_t ps2_get_direction(void)
{
  if (PS2_X_DATA > PS2_ADC_HIGH_THRESHOLD)
		return PS2_DIR_LEFT;
	if (PS2_X_DATA < PS2_ADC_LOW_THRESHOLD)
		return PS2_DIR_RIGHT;
	if (PS2_Y_DATA > PS2_ADC_HIGH_THRESHOLD)
		return PS2_DIR_UP;
	if (PS2_Y_DATA < PS2_ADC_LOW_THRESHOLD)
		return PS2_DIR_DOWN;
	return PS2_DIR_CENTER;
}




void TIMER1A_Handler(void)
{	
	// WORKS
	if (lp_io_read_pin(GREEN_BIT)){
		lp_io_clear_pin(GREEN_BIT);
	} else {
		lp_io_set_pin(GREEN_BIT);
	}
	
  // Clear the interrupt
	TIMER1->ICR |= TIMER_ICR_TATOCINT;
}

void TIMER4A_Handler(void)
{	
	ADC0->PSSI |= ADC_PSSI_SS2;
 
    // Clear the interrupt
	TIMER4->ICR |= TIMER_ICR_TATOCINT;
}

//*****************************************************************************
// ADC0 SS2 ISR
//*****************************************************************************
void ADC0SS2_Handler(void)
{
	PS2_X_DATA = ADC0->SSFIFO2;
	PS2_Y_DATA = ADC0->SSFIFO2;
	PS2_DIR = ps2_get_direction();
  // Clear the interrupt
  ADC0->ISC |= ADC_ISC_IN2;
}

// NOT WORKING?
void GPIOF_Handler(void)
{
	button_pressed = true;
	// clear interrupt
	GPIOF->ICR |= GPIO_ICR_GPIO_M;
}




