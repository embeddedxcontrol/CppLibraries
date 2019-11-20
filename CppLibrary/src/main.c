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
	PIOA->PIO_PUER |= PIO_PA17 | PIO_PA18;		        //Enable pull-up resistors on our two communication pins
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

	//CPP_TWI_FailedAcknowledge(TWI0);

	SetupTwiLcd();

	uint8_t cols = 20;
	uint8_t lines = 4;
	uint8_t dotsize = 0x08;

	delay_ms(50);

	twi_write_byte(TWI0, LCD_NOBACKLIGHT);

	delay_ms(5000);

	twi_write_byte(TWI0, LCD_BACKLIGHT);

	delay_ms(5000);

	twi_write_byte(TWI0, LCD_NOBACKLIGHT);

	delay_ms(5000);

	twi_write_byte(TWI0, LCD_BACKLIGHT);

	////void LiquidCrystal_I2C::begin(uint8_t cols, uint8_t lines, uint8_t dotsize) {
//
//
		//// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
		//// according to datasheet, we need at least 40ms after power rises above 2.7V
		//// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
		//delay(50);
		//
		//// Now we pull both RS and R/W low to begin commands
		//expanderWrite(_backlightval);	// reset expanderand turn backlight off (Bit 8 =1)
		//delay(1000);
//
		////put the LCD into 4 bit mode
		//// this is according to the hitachi HD44780 datasheet
		//// figure 24, pg 46
		//
		//// we start in 8bit mode, try to set 4 bit mode
		//write4bits(0x03 << 4);
		//delayMicroseconds(4500); // wait min 4.1ms
		//
		//// second try
		//write4bits(0x03 << 4);
		//delayMicroseconds(4500); // wait min 4.1ms
		//
		//// third go!
		//write4bits(0x03 << 4);
		//delayMicroseconds(150);
		//
		//// finally, set to 4-bit interface
		//write4bits(0x02 << 4);
//
//
		//// set # lines, font size, etc.
		//command(LCD_FUNCTIONSET | _displayfunction);
		//
		//// turn the display on with no cursor or blinking default
		//_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
		//display();
		//
		//// clear it off
		//clear();
		//
		//// Initialize to default text direction (for roman languages)
		//_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
		//
		//// set the entry mode
		//command(LCD_ENTRYMODESET | _displaymode);
		//
		//home();
		
	



	while(1)
	{
		;
	}

}
