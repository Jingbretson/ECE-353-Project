#include "io_expander.h"


i2c_status_t io_expander_write_reg(
	uint32_t i2c_base,
	uint8_t reg,
	uint8_t data
)
{
	i2c_status_t status;
  
  // Before doing anything, make sure the I2C device is idle
  while (I2CMasterBusy(i2c_base)) {};

  // Set the I2C address to be the IO expander
	status = i2cSetSlaveAddr(i2c_base, MCP23017_DEV_ID, I2C_WRITE);
		
	// Send the register address
  status = i2cSendByte(i2c_base, reg, I2C_MCS_START | I2C_MCS_RUN);
  // Send the data to write
  status = i2cSendByte( i2c_base, data, I2C_MCS_RUN | I2C_MCS_STOP);

  return status;
}

i2c_status_t io_expander_read_reg(
	uint32_t i2c_base,
	uint8_t reg,
	uint8_t *data
)
{
	i2c_status_t status;
	
  // Before doing anything, make sure the I2C device is idle
  while (I2CMasterBusy(i2c_base)) {};

  // Set the I2C address to be the IO expander
	status = i2cSetSlaveAddr(i2c_base, MCP23017_DEV_ID, I2C_WRITE);
		
	// Send the register address
  status = i2cSendByte(i2c_base, reg, I2C_MCS_START | I2C_MCS_RUN);
		
	// Switch to read
	status = i2cSetSlaveAddr(i2c_base, MCP23017_DEV_ID, I2C_READ);
  // Read the data
  status = i2cGetByte(i2c_base, data, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);

  return status;
}

//*****************************************************************************
// Initialize the I2C peripheral
//*****************************************************************************
bool io_expander_init(void)
{
  
  if(gpio_enable_port(IO_EXPANDER_GPIO_BASE) == false)
  {
    return false;
  }
  
  // Configure SCL 
  if(gpio_config_digital_enable(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SCL_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_alternate_function(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SCL_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_port_control(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SCL_PCTL_M, IO_EXPANDER_I2C_SCL_PIN_PCTL)== false)
  {
    return false;
  }
    

  
  // Configure SDA 
  if(gpio_config_digital_enable(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_open_drain(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_alternate_function(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_port_control(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PCTL_M, IO_EXPANDER_I2C_SDA_PIN_PCTL)== false)
  {
    return false;
  }
    
  //  Initialize the I2C peripheral
  if( initializeI2CMaster(IO_EXPANDER_I2C_BASE)!= I2C_OK)
  {
    return false;
  }
  
  return true;
  
}
