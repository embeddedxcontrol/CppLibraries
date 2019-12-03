/**
 * \file
 *
 * \brief Empty user application template
 *
 */


#include <asf.h>
#include <stdbool.h>



//For TWI
#define I2C_FAST_MODE_SPEED   400000
#define I2C_STANDARD_MODE_SPEED   100000
#define I2C_SLAVE_ADDRESS	0x27
#define LOW_LEVEL_TIME_LIMIT   384000
#define TWI_CLK_CALC_ARGU   4
#define TWI_CLK_DIV_MAX   0xFF
#define TWI_CLK_DIV_MIN   7
#define TWI_CLK_DIVIDER   2
#define TWI_WP_KEY_VALUE   TWI_WPMR_WPKEY_PASSWD
//For display
//#define LCD_BACKLIGHT 0x08
#define LCD_BACKLIGHT 0x0E
//#define LCD_NOBACKLIGHT 0x00
#define LCD_NOBACKLIGHT 0x08
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00

static void SetupTwiLcd( void );

static void SetupTwiLcd()
{
	//TWI settings, including default speed
	twi_options_t twi_settings;
	twi_settings.speed = I2C_STANDARD_MODE_SPEED;
	twi_settings.chip = I2C_SLAVE_ADDRESS;
	twi_settings.master_clk = CHIP_FREQ_CPU_MAX;
	twi_settings.smbus = 0;

	//Enable the TWI peripheral clock
	PMC->PMC_PCER0 |= (1<<ID_TWI1);
	//Enable TWI PIOs
	PIOB->PIO_PER |= PIO_PB12 | PIO_PB13; //Enable Peripheral on B12, B13
	//PIOA->PIO_ABSR |= PIO_ABSR_P17 | PIO_ABSR_P18;      //Select Peripheral B (TWI) for Peripheral A18, A17
	PIOB->PIO_ABSR |= PIO_ABSR_P12 | PIO_ABSR_P13;  //Select Peripheral B (TWI) for B12, B13
	//Enable TWI master mode by calling twi_enable_master_mode if it is a master on the I2C bus
	//Configure the TWI in master mode by calling twi_master_init
	twi_master_init(TWI1, &twi_settings);
}

int main (void)
{
	twi_packet_t i2cdata;
	uint8_t byteToLcd = 0x0;
	
	SystemInit();
	delay_init(CHIP_FREQ_CPU_MAX);
	
	PMC->PMC_PCER0 = 0x0;
	PMC->PMC_PCER1 = 0x0;
	SetupTwiLcd();

	uint8_t cols = 20;
	uint8_t lines = 4;
	uint8_t dotsize = 0x08;

	i2cdata.chip = I2C_SLAVE_ADDRESS;
	i2cdata.addr[0] = 0x0;
	i2cdata.addr_length = 0;
	i2cdata.length = 1;

	while(1)
	{
		/*
			typedef struct twi_packet {
			//! TWI address/commands to issue to the other chip (node).
			uint8_t addr[3];
			//! Length of the TWI data address segment (1-3 bytes).
			uint32_t addr_length;
			//! Where to find the data to be transferred.
			void *buffer;
			//! How many bytes do we want to transfer.
			uint32_t length;
			//! TWI chip address to communicate with.
			uint8_t chip;
			} twi_packet_t;
		*/
			
		byteToLcd = LCD_NOBACKLIGHT;
		i2cdata.buffer = &byteToLcd;
			
		twi_master_write(TWI1,&i2cdata);

		delay_ms(1000);
						
		byteToLcd = LCD_BACKLIGHT;
		i2cdata.buffer = &byteToLcd;
			
		twi_master_write(TWI1, &i2cdata);
			
		delay_ms(1000);

		byteToLcd = LCD_NOBACKLIGHT;
		i2cdata.buffer = &byteToLcd;

		twi_master_write(TWI1, &i2cdata);

		delay_ms(1000);

		byteToLcd = LCD_BACKLIGHT;
		i2cdata.buffer = &byteToLcd;
		twi_master_write(TWI1, &i2cdata);
			
		delay_ms(1000);
	}

}
