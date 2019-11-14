/**
 * \file
 *
 * \brief Empty user application template
 *
 */


#include <asf.h>
#include <stdbool.h>
#include "Wire.h"


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
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00

static void SetupTwiLcd( void );
//Cpp functions
static inline bool TWI_FailedAcknowledge( Twi );

static inline bool CPP_TWI_FailedAcknowledge( Twi *pTwi )
{
	bool b = TWI_FailedAcknowledge( *pTwi );
	return b;
}


static void SetupTwiLcd()
{
	//TWI settings, including default speed
	twi_options_t twi_settings;
	twi_settings.speed = I2C_STANDARD_MODE_SPEED;
	twi_settings.chip = I2C_SLAVE_ADDRESS;
	twi_settings.master_clk = CHIP_FREQ_CPU_MAX;
	twi_settings.smbus = 0;

	//Enable the TWI peripheral clock
	PMC->PMC_PCER0 |= (1<<ID_TWI0);
	//Enable TWI PIOs
	PIOA->PIO_ABSR |= PIO_ABSR_P17 | PIO_ABSR_P18;      //Select Peripheral B (TWI) for Peripheral A18, A17
	PIOA->PIO_PER |= PIO_PA17 | PIO_PA18;               //Enable Peripheral on A17, A18
	PIOA->PIO_PUER |= PIO_PA17 | PIO_PA18;		        //Enalble pull-up resistors on our two communication pins
	//Enable TWI master mode by calling twi_enable_master_mode if it is a master on the I2C bus
	twi_enable_master_mode(TWI0);
	//Configure the TWI in master mode by calling twi_master_init
	twi_master_init(TWI0, &twi_settings);
}

int main (void)
{

	SystemInit();
	PMC->PMC_PCER0 = 0x0;
	PMC->PMC_PCER1 = 0x0;

	CPP_TWI_FailedAcknowledge(TWI0);

	SetupTwiLcd();

	while(1)
	{
		;
	}

}
