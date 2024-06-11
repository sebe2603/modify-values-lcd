/*-------------------------------------------------------------------------
					Technika Mikroprocesorowa 2 - projekt
					Modyfikacja wartosci wybranej pozycji na wyswietlaczu
					autor: Sebastian Gawlak
					wersja: 19.01.2024r.
----------------------------------------------------------------------------*/
	
#include "MKL05Z4.h"
#include "frdm_bsp.h"
#include "lcd1602.h"
#include "tsi.h"
#include "klaw.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


volatile uint8_t S2_press=0;	// "1" - klawisz zostal wcisniety "0" - klawisz "skonsumowany"
volatile uint8_t S3_press=0;
volatile uint8_t S4_press=0;

void PORTA_IRQHandler(void)	// Podprogram obslugi przerwania od klawiszy S2 i S4 z minimalizacja drgan zestykow
{
	uint32_t buf;
	buf=PORTA->ISFR & (S2_MASK | S4_MASK);

	switch(buf)
	{
		case S2_MASK:	DELAY(10)
									if(!(PTA->PDIR&S2_MASK))
									{
										if(!(PTA->PDIR&S2_MASK))
										{
											if(!S2_press)
											{
												S2_press=1;
											}
										}
									}
									break;
		case S4_MASK:	DELAY(10)
									if(!(PTA->PDIR&S4_MASK))
									{
										if(!(PTA->PDIR&S4_MASK))
										{
											if(!S4_press)
											{
												S4_press=1;
											}
										}
									}
									break;
		default:			break;
	}	
	PORTA->ISFR |=  S2_MASK | S4_MASK;	// Kasowanie wszystkich bitów ISF
	NVIC_ClearPendingIRQ(PORTA_IRQn);
}

int main (void) 
{
	uint8_t w=0;
	char display[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20}; // Pusty wyswietlacz
	int wybrana_wartosc = 0; 
	int dotyk = 0;
	
	Klaw_Init();
	Klaw_S2_4_Int();
	LCD1602_Init();		 					// Inicjalizacja LCD
	LCD1602_Backlight(TRUE);  	// Wlaczenie podswietlenia
	TSI_Init();									// Inicjalizacja panelu dotykowego
	
	LCD1602_ClearAll();					// Wyczysc ekran
	LCD1602_SetCursor(wybrana_wartosc,0);			// Wyswietl stan poczatkowy pola dotykowego
	LCD1602_Print("0000000000");
	
  while(1)		// Poczatek petli glównej
	{
		w=TSI_ReadSlider();		// Odczytaj pozycje panelu dotykowego
		if(S4_press)	// Czy klawisz S4 wcisniety?
		{
			LCD1602_SetCursor(wybrana_wartosc,1); // Czyszczenie kursora
			if(wybrana_wartosc == 9) // Powrot na poczatek
			{
				wybrana_wartosc = 0;
			}
			else // Zmiana pozycji do przodu
			{
				wybrana_wartosc = wybrana_wartosc + 1;
			}
			sprintf(display,"%c",0x20);
			LCD1602_Print(display);
			S4_press = 0;
		}
		if(S2_press)	// Czy klawisz S2 wcisniety?
		{
			LCD1602_SetCursor(wybrana_wartosc,1); // Czyszczenie kursora
			if(wybrana_wartosc == 0) // Powrot na koniec
			{
				wybrana_wartosc = 9;
			}
			else // Zmiana pozycji do tylu
			{
				wybrana_wartosc = wybrana_wartosc - 1;
			}
			sprintf(display,"%c",0x20);
			LCD1602_Print(display);
			S2_press = 0;
		}
		LCD1602_SetCursor(wybrana_wartosc,1);
		sprintf(display,"%c",0x5E);
		LCD1602_Print(display);
		if(w!=0)							// Wyswietl pozycje palca, jezeli dotknieto pola
		{
			if(w <= 10)
			{
				dotyk = 0;
			}
			if(w > 10 && w <= 20)
			{
				dotyk = 1;
			}
			if(w > 20 && w <= 30)
			{
				dotyk = 2;
			}
			if(w > 30 && w <= 40)
			{
				dotyk = 3;
			}
			if(w > 40 && w <= 50)
			{
				dotyk = 4;
			}
			if(w > 50 && w < 60)
			{
				dotyk = 5;
			}
			if(w > 60 && w <= 70)
			{
				dotyk = 6;
			}
			if(w > 70 && w <= 80)
			{
				dotyk = 7;
			}
			if(w > 80 && w <= 90)
			{
				dotyk = 8;
			}
			if(w > 90 && w <= 100)
			{
				dotyk = 9;
			}
			// Kazdy fragment pola dotykowego odpowiada innej cyfrze
			LCD1602_SetCursor(wybrana_wartosc,0);
			sprintf(display,"%d",dotyk);
			LCD1602_Print(display);
		}
	}
}
