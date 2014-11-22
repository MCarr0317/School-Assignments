#include <reg932.h>
#include "uart.h"


//bit addressable ports 
sbit Spkr = P1^7;
sbit LED3 = P2^5;
sbit LED3SW	= P2^1;
sbit LED6 = P0^7;
sbit LED6SW = P0^3; 
sbit LED9 = P2^6;
sbit LED9SW  = P2^2;
sbit LED1 = P2^4;
sbit LED1SW = P2^0;
sbit LED4 = P0^5;
sbit LED4SW =P0^1;
sbit LED5 = P1^6;
sbit LED5SW = P1^4;
sbit LED2 = P0^6;
sbit LED2SW = P0^2;
sbit BoardLED1 = P1^7;
sbit BoardLED2 = P3^0;

//The commented code is meant for the LCD display, we kept it to show 
//that we tried our best despite our hardware problems.
/*
sbit RW = P1^0;
sbit EN = P1^1;
sbit RS = P1^2;
sbit ON = P1^3;
sbit BLON = P1^4;
sbit dbg_led = P1^7;

#define LCD_DATA  P0
*/

unsigned char MODE = 0; //variable for current mode

//ODE TO JOY
unsigned char ODEdur[17] = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,5,10,10}; //note durations
unsigned char ODEhigh[17] = {0xF1, 0xF1, 0xF2, 0xF3, 0xF3, 0xF2, 0xF1, 0xEF, 0xED, 0xED, 0xEF, 0xF1, 0xF1, 0xF1, 0xEF, 0xEF, 0xEF}; //high nibbles
unsigned char ODElow[17] =  {0x6D, 0x6D, 0x43, 0xC1, 0xC1, 0x43, 0x6D, 0xA3, 0xA2, 0xA2, 0xA3, 0x6D, 0x6D, 0x6D, 0xA3, 0xA3, 0xA3}; //low nibbles
	
//THIS OLD MAN
#define MANdur 10 //all notes in this song can be played with a constant duration
unsigned char MANhigh[16] = {0xED, 0xEA, 0xED, 0xED, 0xED, 0xEA, 0xED, 0xED, 0xEF, 0xED, 0xEB, 0xEA, 0xE7, 0xEA, 0xEB, 0xEB}; //high nibbles
unsigned char MANlow[16] =  {0xA2, 0x2F, 0xA2, 0xA2, 0xA2, 0x2F, 0xA2, 0xA2, 0xA3, 0xA2, 0x6E, 0x2F, 0x83, 0x2F, 0x6E, 0x6E}; //low nibbles

//STARTUP JINGLE - this uses MANdur as its durations also
unsigned char JINhigh[8] =  {0xED, 0xEF, 0xF1, 0xF3, 0xF3, 0xF1, 0xF3, 0xF3};
unsigned char JINlow[8] =   {0xA2, 0xA3, 0x6D, 0xC1, 0xC1, 0x6D, 0xC1, 0xC1};	
	
//delimiter for for-loops
unsigned char n = 0;

//command line prompt strings
unsigned char Titles[53] = "The songs available are Ode To Joy and This Old Man. ";
unsigned char Welcome[81] = "Welcome to the Pandora Keyboard! Here you can play notes or pre-recorded tunes. ";
unsigned char strMODE0[32] = "Mode 0 - Play individual notes. ";
unsigned char strMODE1[32] = "Mode 1 - Play individual tunes. ";



/*
void lcd_clear(void);
void lcd_on(void);
void lcd_fn_set(void);
void lcd_mode_set(void);
void write_data_to_lcd(char dat);	
*/

//PROTOTYPES
void PlayNote(unsigned char ,unsigned char,unsigned char); //plays a note
void delay(unsigned char);	//performs a delay inbetween notes, also checks/updates mode using checkMODE
void MODEchangeLED();	//changes mode LED
unsigned char checkMODE();	//checks and updates MODE
void sendTitles();
void sendWelcome();
void sendMode();

void timer1(void) interrupt 3	//interrupt ISR for changing mode in the middle of a song
	{
		TF1 = 0;
		TR1 = 0;
	}
	

void main()
{
	uart_init(); //initialize serial communication UART
	TMOD = 0x11; //Set both timers into mode 1
	EA = 1;		//
	ET0 = 1;	//set IE 
	ET1 = 1;	//
	
	//make ports bi-directional
	P0M1 = 0;
	P0M2 = 0;
	P2M1 = 0;
	P2M2 = 0;
	P1M1 = 0;
	P1M2 = 0;

	/*
  //initializations
	ON=1;
	BLON=1;
    
    //configure the LCD
	lcd_fn_set();
	lcd_mode_set();
	lcd_clear();
	lcd_on();
	delay(20000);

    //write first char to lcd
	write_data_to_lcd(0x50);
	*/

	sendWelcome();//start with the welcome prompt
	BoardLED1 = 0;
	BoardLED2 = 1;
	//play the startup jingle
	for (n = 0;n < 8;n++)
	{
		//BoardLED1 = !BoardLED1;
		//BoardLED2 = !BoardLED2;
		PlayNote(MANdur,JINhigh[n], JINlow[n]);
		if (n !=3  && n !=6) 
			delay(50);
	}
	
	//state the mode on startup
	sendMode();
	
	
	//main loop
	while(1)
	{
		//this allows us to change the mode 
		checkMODE();
		
		//MODE 0 performance code
		if (MODE == 0)
		{
			MODEchangeLED();	//display the mode in binary
			
			if(LED3SW==0) //if we press LED3, transmit a G4, light the LED, and play the sound
			{
				uart_transmit('G');
				uart_transmit('4');
				uart_transmit(' ');
				while(LED3SW==0)
				{	
					LED3 = 0;
					PlayNote(10, 0xF6, 0xD1);  //Plays G4 Note
				
				};
			
				LED3 = 1; //turn the LED off when we lift up on the switch
			}
			if(LED6SW==0)//if we press LED6, transmit a C4, light the LED, and play the sound
			{
				uart_transmit('C');
				uart_transmit('4');
				uart_transmit(' ');
				while(LED6SW==0)
					{
					LED6 = 0;
					PlayNote(10, 0xF2, 0x43);  //Plays C4 Note
					};
				LED6 = 1; //turn it off when we are done
			}
			if(LED9SW==0) //if we press LED9, transmit an E4, light the LED, and play the sound
			{
				uart_transmit('E');
				uart_transmit('4');
				uart_transmit(' ');
				while(LED9SW==0)
					{
					LED9 = 0;
					PlayNote(10, 0xF5, 0x18);  //Plays E4 Note
					};
				LED9 = 1;
			}
		}
		
		//MODE 1 code
		if (MODE == 1)
		{
			LED1 = 1;
			LED4 = 1;
			MODEchangeLED(); //display the mode in binary
			
			if(LED1SW==0) //IF USER SELECTS "ODE TO JOY"
			{	
				LED1 = 0;
				uart_transmit('\f'); //clear the screen
				sendMode();					// and update the mode
				
				//play Ode to joy
				for (n = 0;n < 17;n++)
				{
					PlayNote(ODEdur[n],ODEhigh[n], ODElow[n]);
					if (MODE != 1){break;}
					if (n !=12  && n !=15) 
						delay(125);
				}
				
			}
			
			if(LED4SW==0)		//IF USER SELECTS "THIS OLD MAN"
			{
				LED4 = 0;
				uart_transmit('\f');	//clear the screen and update the mode
				sendMode();
				
				//Play This Old Man
				for (n = 0;n < 16;n++)
				{
					PlayNote(MANdur,MANhigh[n], MANlow[n]);
					if (MODE != 1){break;}
					if (n !=2  && n !=6 && n != 14) 
						delay(125);
				}
			}
	  }
		if (MODE == 2) //IF USER WANTS TO DISPLAY SONG LISTING
		{
			MODEchangeLED();	//display the mode in binary
			sendTitles(); //display song titles
			MODE = 0; //there is no point in staying in this mode, switch back to mode 0
			sendMode(); //display mode
		}
		

	}

}

void PlayNote(unsigned char dur,unsigned char high,unsigned char low)			 //Plays a note with given timer values
{
	unsigned char i;
	for(i=0;i<dur*25;i++)
	{
		TH0 =  high;
		TL0 = low;
		TR0 = 1;
		while(TF0==0); //repeat until overflow
		TF0 = 0;	//reset the flag
		Spkr = ~Spkr; //complent the speaker to send a square wave
		MODEchangeLED(); //update the mode
	}
}

unsigned char checkMODE()
{
	if (LED5SW == 0)
	{
		  TF1 = 1; //immediately overflow
			TR1 = 1;
			while(LED5SW==0); //debounce
			
		//the following code changes the mode and sends it to the screen if switch 5 is pressed
			if (MODE == 0)
			{
				MODE = 1;
				uart_transmit('\f');
				sendMode();
			}
			else if (MODE == 1)
			{
				MODE = 2;
			}
			else if (MODE == 2)
			{
				sendTitles();
				MODE = 0;
				sendMode();
			}
			
	}
	return MODE;
}
void MODEchangeLED()
{
	if (checkMODE() == 0)
	{
		LED2 = 1;
		LED5 = 1;
	}
	else if (checkMODE() == 1)
	{
		LED5 = 0;
		LED2 = 1;
	}
	else if (checkMODE() == 2)
	{
		LED2 = 0;
		LED5 = 1;
	}
	
	
}
	
void delay(unsigned char dur)					//Delay used inbetween the notes
{
	unsigned char i, j;

	for(i=0; i<	dur; i++){
		MODEchangeLED();
		for(j=0; j<	dur; j++);
	}

}
void sendTitles()
{
	uart_transmit('\f');
	for (n = 0;n < 53;n++)
		uart_transmit(Titles[n]);
}
void sendWelcome()
{
	uart_transmit('\f');
	for (n = 0;n < 81;n++)
		uart_transmit(Welcome[n]);
}
void sendMode()
{
	
	for (n = 0;n < 32;n++)
		if (MODE == 0)
			uart_transmit(strMODE0[n]);
		else if (MODE == 1)
			uart_transmit(strMODE1[n]);
			
}
	
	
		  
	 /*  
void lcd_clear(void)
{
	RS=0;
	RW=0;
	EN=1;
	delay(10000);
	LCD_DATA=0x01;
	delay(10000);
	EN=0;
}


void lcd_on(void)
{
	RS=0;
	RW=0;
	EN=1;
	delay(10000);
	LCD_DATA=0x0E;
	delay(10000);
	EN=0;
}


void lcd_fn_set(void)
{
	RS=0;
	RW=0;
	EN=1;
	delay(10000);
	LCD_DATA=0x38;
	delay(10000);
	EN=0;
}


void lcd_mode_set(void)
{
	RS=0;
	RW=0;
	EN=1;
	delay(10000);
	LCD_DATA=0x06;
	delay(10000);
	EN=0;
}


void write_data_to_lcd(char dat)
{
	RS=1;
	RW=0;
	EN=1;
	delay(10000);
	LCD_DATA=dat;
	delay(10);
	EN=0;
}
	*/		
