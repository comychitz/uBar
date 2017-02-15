#include <p18f4321.h>
#include <stdio.h>
#pragma config OSC = INTIO2
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config BOR = OFF
#pragma interrupt chk_isr

#define RIGHT PORTBbits.RB7 //pin 38 
#define LEFT PORTBbits.RB6 //pin 37

//Phototransistors
#define pos1 PORTDbits.RD0 //pin 19
#define pos2 PORTDbits.RD1 //pin 20
#define pos3 PORTDbits.RD2 //pin 21
#define pos4 PORTDbits.RD3 //pin 22
#define pos0 PORTEbits.RE2  //pin 10

//Order Buttons 
#define start PORTAbits.RA0 	//start
#define ice PORTAbits.RA1 		//ice
#define drink1 PORTAbits.RA2	//drink1
#define drink2 PORTAbits.RA3	//drink2
#define drink3 PORTAbits.RA4	//drink3
#define drink4 PORTAbits.RA5	//drink4

//Output for valves
#define cupDispensor PORTBbits.RB0 	//cup dispensor
#define iceDispensor PORTBbits.RB1 	//ice dispensor
#define valve1 PORTBbits.RB2		//valve 1
#define valve2 PORTBbits.RB3		//valve 2
#define valve3 PORTBbits.RB4		//valve 3
#define valve4 PORTBbits.RB5		//valve 4

//reset all the latches on the LCD
#define LCDreset PORTEbits.RE0

//Percent value of duty cycle. CCPR1L = 50 will result in 50% duty cycle
#define PWM CCPR1L //RC2 pin 17

void init(void);
void chk_sir(void);
void setOrder(char);
int readOrder(void);
void openValve(char);
void closeValve(char);
void goHome(void);
void goToDrink(int, int);
void wait(void);
void pourDrink(int, int);

//Global Variables
int currPos = 0;
int drinkOrder[5] = {6,6,6,6,6};  //Array holds the position number for the selected drink. 
int i, j, drink, timer = 0, timer2 = 0, counter = 0;
int k;
int drinkNumber = 0, totalNumberOfDrinks = 0;

//Interrupt service routine for Timer2
void chk_isr()
{ 
	PIR1bits.TMR2IF = 0; //clear Timer2 flag	
}

#pragma code My_HiPriority_int = 0x08
void My_HiPrio_int()
{
    _asm
    GOTO chk_isr
    _endasm
}
#pragma code

//Initializer
void init()
{
	//Initialize Clock
	OSCCON = 0x70;
	
	//Initialize I/O
	TRISC = 0;
	TRISD = 0xFF;
	TRISA = 0xBF;
	TRISB = 0x00;
	TRISE = 0x06;
	
	//Initialize ADC
	ADCON0 = 0x00;	//ADC off
	ADCON1 = 0x0F;	
	
	//Initialize Interrupts
	INTCONbits.GIE = 1;	
	INTCONbits.PEIE = 1;
	INTCONbits.INT0IE = 1;
	INTCONbits.INT0IF = 0;
	INTCON2 = 0xE0;
	
	//Initialze PWM and Timer2
	CCP1CON = 0x0C;
	PR2 = 0x63;
	T2CONbits.TMR2ON = 1;
	PIE1bits.CCP1IE = 1;
	PIE1bits.TMR2IE = 1;
	CCP1CONbits.DC1B = 0x00;
	CCPR1L = 0x12;
	
	valve1 = 1;
	valve2 = 1;
	valve3 = 1;
	valve4 = 1;
	
	PWM = 75;	
	RIGHT = 0;
	LEFT = 0;
	LCDreset = 0;	
	k = 0;
}

void goHome()
{
	while(pos0 != 1)
	{
		LEFT = 1;	
	}
	
	currPos = 0;
	LEFT = 0;
   RIGHT = 0;
}	

void goToDrink(int drink, int NumberOfDrinks)
{
	if(drink == 1)
	{	
		while(pos1 != 1)
		{
			if(currPos < 1)
			{
				RIGHT = 1;
			}	
			else
			{
				LEFT = 1;
			}		
		}		
		currPos = 1;
	}
	
	if(drink == 2)
	{
		while(pos2 != 1)
		{
			if(currPos < 2)
			{
				RIGHT = 1;
			}	
			else
			{
				LEFT = 1;
			}	
		}	
		currPos = 2;
	}
	
	if(drink == 3)
	{
		while(pos3 != 1)
		{
			if(currPos < 3)
			{
				RIGHT = 1;
			}	
			else
			{
				LEFT = 1;
			}		
		}	
		currPos = 3;
	}
	
	if(drink == 4)
	{
		while(pos4 != 1)
		{
			if(currPos < 4)
			{
				RIGHT = 1;
			}	
			else
			{
				LEFT = 1;
			}		
		}	
		currPos = 4;
	}
    
    RIGHT = 0;
    LEFT = 0;
    pourDrink(NumberOfDrinks, currPos);
	
}	

void pourDrink(int delay, int position)
{
	RIGHT = 0;
	LEFT = 0;
	timer = 0;
	
	if(position == 1)
	{
		valve1 = 0;
	}
    
	if(position == 2)
	{
		valve2 = 0;
	}
	
	if(position == 3)
	{
		valve3 = 0;
	}
    
	if(position == 4)
	{
		valve4 = 0;
	}				
	
	while(timer < 10000/delay)
	{
		while(timer2 < 150)
		{
			timer2 = timer2 + 1;	
		}	
		timer2 = 0;
		timer = timer + 1;	
	}
	
	valve1 = 1;
	valve2 = 1;
	valve3 = 1;
	valve4 = 1;
}		

void wait()
{
	RIGHT = 0;
	LEFT = 0;
	timer = 0;
	while(timer < 500)
	{
		while(timer2 < 150)
		{
			timer2 = timer2 + 1;	
		}	
		timer2 = 0;
		timer = timer + 1;	
	}
}	

int readOrder()
{

	if(drink4 == 1)
	{
		drinkOrder[counter] = 4;
		counter = counter + 1;
	}
    
	if(drink3 == 1)
	{
		drinkOrder[counter] = 3;
		counter = counter + 1;	
	}
    
	if (drink2 == 1)
	{
		drinkOrder[counter] = 2;
		counter = counter + 1;	
	}
    
	if(drink1 == 1)
	{
		drinkOrder[counter] = 1;
		counter = counter + 1;	
	}
	
	return counter;
}	

void main ()
{
	init();	
	goHome();
    while(1) {
    	while(start == 0){}
		drinkOrder[0] = 6;
		drinkOrder[1] = 6;
		drinkOrder[2] = 6;
		drinkOrder[3] = 6;
		drinkOrder[4] = 6;

		counter = 0;
        totalNumberOfDrinks = readOrder();

        k = 0;
        while(drinkOrder[k] != 6)
        {
            goToDrink(drinkOrder[k],totalNumberOfDrinks);
			wait();
            k++;
        }
		
		goHome();
    }
	
}