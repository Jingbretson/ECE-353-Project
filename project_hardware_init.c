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
#include "project_hardware_init.h"

void configure_gpiof_irq(void)
{
	gpio_enable_port(IO_EXPANDER_GPIO_BASE);
  
	gpio_config_digital_enable(IO_EXPANDER_IRQ_GPIO_BASE, IO_EXPANDER_IRQ_PIN_NUM);

	gpio_config_enable_input(IO_EXPANDER_IRQ_GPIO_BASE, IO_EXPANDER_IRQ_PIN_NUM);

  // is this pullup necessary?
	gpio_config_enable_pullup(IO_EXPANDER_IRQ_GPIO_BASE, IO_EXPANDER_IRQ_PIN_NUM);
	
	gpio_config_falling_edge_irq(IO_EXPANDER_IRQ_GPIO_BASE, IO_EXPANDER_IRQ_PIN_NUM);

  // Set the Priority
  NVIC_SetPriority(GPIOF_IRQn, 1);

  // Enable the Interrupt in the NVIC
  NVIC_EnableIRQ(GPIOF_IRQn);
}

void initializeBoard(void)
{
  DisableInterrupts();
  init_serial_debug(true, true);
  EnableInterrupts();
	
	io_expander_init();
	// to use IO expander features, we need to configure it
	
	
	
	lp_io_init();
	//ft6x06_init();
	
	
	gp_timer_config_32(TIMER1_BASE,TIMER_TAMR_TAMR_PERIOD, 50000000, false);
  gp_timer_config_32(TIMER4_BASE,TIMER_TAMR_TAMR_PERIOD, 500000, false);
	
	
	
	
	// turn on internal pull up for push  buttons (pins 3-0 of 7)
	io_expander_write_reg(IO_EXPANDER_I2C_BASE, MCP23017_GPPUB_R, 0x0F);
	// set buttons to inputs
	io_expander_write_reg(IO_EXPANDER_I2C_BASE, MCP23017_IODIRB_R, 0x0F);
	// set button pins to interrupt on change
	io_expander_write_reg(IO_EXPANDER_I2C_BASE, MCP23017_GPINTENB_R, 0x0F);
	// configure interrupts to occur via change from previous value, not change from DEFVAL
	io_expander_write_reg(IO_EXPANDER_I2C_BASE, MCP23017_INTCONB_R, 0x00);
	// interrupts from part B are received on tiva's GPIOF bit 0
	configure_gpiof_irq();
	gpio_config_falling_edge_irq(IO_EXPANDER_IRQ_GPIO_BASE, IO_EXPANDER_IRQ_PIN_NUM);
}
