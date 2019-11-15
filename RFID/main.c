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
	//Saved card
	uint8_t card[8] = {208, 166, 96, 37, 51, 0, 0, 0};
	UartInit();
	char buffer[150];
	uint8_t byte;
	uint8_t str[MAX_LEN];
	
	//Initialize the SPI configuration
	spi_init();
	
	//Initialize display, cursor on
	lcd_init(LCD_DISP_ON);

	//Clear display and home cursor
	lcd_clrscr();
	
	//Initialize the RFID reader
	mfrc522_init();
	
	//check version of the reader
	//Version numbers can be found in the Readme.
	byte = mfrc522_read(VersionReg);
		
	//Version number is read from the Version register as shown above.
	switch (byte)
	{
		case 0x92:
			printf("MIFARE RC522v2\r\n");
			printf("Detected\r\n");
			lcd_gotoxy(0,0);
			lcd_puts("MIFARE RC522v2");
			lcd_gotoxy(0,1);
			lcd_puts("Detected");
			break;
		case 0x91:
			printf("MIFARE RC522v1\r\n");
			printf("Detected\r\n");
			lcd_puts("MIFARE RC522v1");
			lcd_gotoxy(0,1);
			lcd_puts("Detected");
			break;
		case 0x90:
			printf("MIFARE RC522v0\r\n");
			printf("Detected\r\n");
			lcd_puts("MIFARE RC522v0");
			lcd_gotoxy(0,1);
			lcd_puts("Detected");
			break;
		case 0x88:
			printf("RFID-RC522 Clone\r\n");
			printf("Detected\r\n");
			lcd_puts("RFID-RC522 Clone");
			lcd_gotoxy(0,1);
			lcd_puts("Detected");
			break;
		default:
			printf("No reader found\r\n");
			break;
	}
	
	while(1){
		//The mcu checks to se if a card is found.
		byte = mfrc522_request(PICC_REQALL,str);		
		if(byte == CARD_FOUND)
		{			
			int position = 0; //Defines the position in the char array that the byte will be writen to.			
			byte = mfrc522_get_card_serial(str);
			if(byte == CARD_FOUND) //The mcu checks again after getting more information about the card.
			{	
				if (Validate_Card(&card, &str)) //Validates the card read to the card saved.
				{					
					printf("Authorized\r\nID:");
					for(byte=0;byte<8;byte++) //Convertes the value of the card to a char array so it can be printed to the LCD/Terminal.
					{
						//Takes the last position of where the char array and saves it in the position variable.
						position += sprintf(&buffer[position], "%i", str[byte]);
						printf("%i", str[byte]);
					}
					lcd_clrscr();
					lcd_gotoxy(0,0);
					lcd_puts("Authorized");
					lcd_gotoxy(0,1);
					lcd_puts(buffer);
				}
				else
				{
					printf("Unauthorized\r\n");
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
		//Delay so there cant be read cards more than once pr 500ms.
		//If this delay is removed the program cant keep up with the data read from the card.
		_delay_ms(500);
	}
}