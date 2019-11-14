#define F_CPU 16000000UL
#define BAUD 9600
#define BAUD_TOL 2



#include <stdio.h>
#include <avr/io.h>
#include "stdio_setup.h"
#include "util/delay.h"
#include <util/setbaud.h>
#include "spi/spi.h"
#include "mfrc522/mfrc522.h"
#include "lcd/lcd.h"


int main()
{
	uint8_t card[8] = {208, 166, 96, 37, 51, 0, 0, 0};
	UartInit();
	char buffer[150];
	uint8_t byte;
	uint8_t str[MAX_LEN];
	_delay_ms(50);
	
	spi_init();
	/* initialize display, cursor on */
	lcd_init(LCD_DISP_ON);

	/* clear display and home cursor */
	lcd_clrscr();
	_delay_ms(1000);
	
	//init reader
	mfrc522_init();
	
	//check version of the reader
	byte = mfrc522_read(VersionReg);
	
	//printf("%d", byte);
	
	//Version numbers can be found in the Readme
	if(byte == 0x92)
	{
		printf("MIFARE RC522v2\r\n");
		printf("Detected\r\n");
	}else if(byte == 0x91 || byte==0x90)
	{
		printf("MIFARE RC522v1\r\n");
		printf("Detected\r\n");
	}else if(byte == 0x88)
	{
		printf("RFID-RD522\r\n");
		printf("Detected\r\n");
	}
	else
	{
		printf("No reader found\r\n");
	}
	
	_delay_ms(1500);	
	
	while(1){
		byte = mfrc522_request(PICC_REQALL,str);
		
		if(byte == CARD_FOUND)
		{
			int position = 0;
			byte = mfrc522_get_card_serial(str);
			if(byte == CARD_FOUND)
			{	
				if (Validate_Card(&card, &str))
				{					
					printf("Authorized\r\n");
					for(byte=0;byte<8;byte++)
					{
						position += sprintf(&buffer[position], "%i", str[byte]);
					}
					lcd_clrscr();
					lcd_gotoxy(0,0);
					lcd_puts("Authorized");
					lcd_gotoxy(0,1);
					lcd_puts(buffer);
				}
				else
				{
					lcd_clrscr();
					lcd_gotoxy(0,0);
					lcd_puts("Unauthorized");
				}						
			}
			else
			{
				printf("Error");
			}
		}		
		_delay_ms(500);
	}
}