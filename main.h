// Copyright (c) 2015-16, Joe Krachey
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
#ifndef __MAIN_H__
#define __MAIN_H__


#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef enum{
  PS2_DIR_UP,
  PS2_DIR_DOWN,
  PS2_DIR_LEFT,
  PS2_DIR_RIGHT,
  PS2_DIR_CENTER,
  PS2_DIR_INIT,
} PS2_DIR_t;


extern volatile PS2_DIR_t PS2_DIR;
extern volatile uint8_t button_pressed;

#include "TM4C123.h"
#include "gpio_port.h"
#include "lcd.h"
#include "lcd_images.h"
#include "timers.h"
#include "ps2.h"
#include "launchpad_io.h"

#include "serial_debug.h"
#include "io_expander.h"
#include "eeprom.h"
#include "ft6x06.h"

#include "project_interrupts.h"
#include "project_hardware_init.h"

#define SCORE_ADDR 256
typedef enum {
	BD_UP,
	BD_DOWN,
	BD_LEFT,
	BD_RIGHT,
	BD_CENTER
} BD_t;

typedef struct {
	BD_t dir;
	uint16_t x;
	uint16_t y;
} bullet_t;

typedef enum 
{
  DEBOUNCE_ONE,
  DEBOUNCE_1ST_ZERO,
  DEBOUNCE_2ND_ZERO,
  DEBOUNCE_PRESSED
} DEBOUNCE_STATES;


#endif
