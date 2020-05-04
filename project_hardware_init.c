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

void configure_io_expander(void)
{
	// set port A pins (LED's) to outputs
	io_expander_write_reg(IO_EXPANDER_I2C_BASE, MCP23017_IODIRA_R, 0x00);
	
	
	// set port B pins (buttons and switches) to inputs
	io_expander_write_reg(IO_EXPANDER_I2C_BASE, MCP23017_IODIRB_R, 0xFF);
	
	// turn on internal pull up for push buttons (pins 3-0)
	io_expander_write_reg(IO_EXPANDER_I2C_BASE, MCP23017_GPPUB_R, 0x0F);
	
	
	// make sure INTB is open drain ~active low~
	io_expander_write_reg(IO_EXPANDER_I2C_BASE, MCP23017_IOCONB_R, (1 << 2));
	
	// configure interrupts to occur via change from previous value, not change from DEFVAL
  io_expander_write_reg(IO_EXPANDER_I2C_BASE, MCP23017_INTCONB_R, 0x00);
	
	// set button pins to interrupt on change
	io_expander_write_reg(IO_EXPANDER_I2C_BASE, MCP23017_GPINTENB_R, 0x0F);
	
	// read to knock down initial high?
	io_expander_read_reg(IO_EXPANDER_I2C_BASE, MCP23017_GPIOB_R, NULL);
}

void configure_gpiof_irq(void)
{
	gpio_enable_port(IO_EXPANDER_IRQ_GPIO_BASE);
  
	gpio_config_digital_enable(IO_EXPANDER_IRQ_GPIO_BASE, IO_EXPANDER_IRQ_PIN_NUM);

	gpio_config_enable_input(IO_EXPANDER_IRQ_GPIO_BASE, IO_EXPANDER_IRQ_PIN_NUM);

  // is this pullup necessary?
	gpio_config_enable_pullup(IO_EXPANDER_IRQ_GPIO_BASE, IO_EXPANDER_IRQ_PIN_NUM);
	//gpio_config_enable_pulldown(IO_EXPANDER_IRQ_GPIO_BASE, IO_EXPANDER_IRQ_PIN_NUM);
	
	// interrupts from part B are received on tiva's GPIOF bit 0
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
	
	lcd_config_gpio();
  lcd_config_screen();
  lcd_clear_screen(LCD_COLOR_BLACK);
	
	
	eeprom_init();
	io_expander_init();
	ps2_initialize();
  ft6x06_init();
	
	// 50000000 ticks is 1s for clock of 50MHz
	gp_timer_config_32(TIMER1_BASE,TIMER_TAMR_TAMR_PERIOD, 50000000, false, true);
	// 500000 ticks is 10ms for 50MHz clock
	// 16 bit timer is too small for 500000 so use prescalar
	// prescalar of 7 -> every 8th tick -> 62500 ticks < 2^16 == 65536
	// prescalar assigned within function
  gp_timer_config_16(TIMER4_BASE,TIMER_TAMR_TAMR_PERIOD, 62500, false, true);
	// fall back to the regular 32 bit timer if not working
	// gp_timer_config_32(TIMER4_BASE,TIMER_TAMR_TAMR_PERIOD, 50000, false, true);
	

	// set up IO expander GPIO pins via I2C
	configure_io_expander();
	#if 0
	// set up interrupts from IO expander on GPIOF
	configure_gpiof_irq();
	// now that GPIOF is up, turn on the blinking light
	gpio_config_digital_enable(GPIOF_BASE, GREEN_M);
	gpio_config_enable_output(GPIOF_BASE, GREEN_M);
	#endif
	
	lp_io_init();
	
	EnableInterrupts();
}
