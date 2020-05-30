#include "stdint.h"
#include "MCAL_GPIO_UART_interface.h"
#include "C:/Keil_v5/Labware/inc/tm4c123gh6pm.h"


#define UART0_TXFF 5
#define UART0_RXFE 4

#define CLR_BIT(VAR,BIT)     VAR&=~(1<<BIT)
#define SET_BIT(VAR,BIT)     VAR|=(1<<BIT)
#define GET_BIT(VAR,BIT)     (VAR>>BIT)&1
#define TOGGLE_BIT(VAR,BIT)  VAR^=(1<<BIT)


void GPIO_voidPortF_Init(void)
{
  SYSCTL_RCGCGPIO_R|=0X20;
  while((SYSCTL_PRGPIO_R&0X20)==0){}
  GPIO_PORTF_DEN_R=0XE;
	GPIO_PORTF_CR_R=0XE;
  GPIO_PORTF_AMSEL_R=0;
	GPIO_PORTF_AFSEL_R=0;
	GPIO_PORTF_PCTL_R=0;
	GPIO_PORTF_DIR_R=0XE;	
}

void GPIO_voidPortB_Init(void)
{
  SYSCTL_RCGCGPIO_R|=0X2;
  while((SYSCTL_PRGPIO_R&0X2)==0){}
  GPIO_PORTB_DEN_R=0XFF;
	GPIO_PORTB_CR_R=0XFF;
  GPIO_PORTB_AMSEL_R=0;
	GPIO_PORTB_AFSEL_R=0;
	GPIO_PORTB_PCTL_R=0;
	GPIO_PORTB_PUR_R=0XF0;
	GPIO_PORTB_DIR_R=0X0F;
  GPIO_PORTB_DATA_R|=0XF;		
}


//func to set value of specific pin 
void  GPIO_voidSetPinValue(GPIO_PORTS enuPortIdx_cpy, GPIO_PINS enuPinIdx_cpy,GPIO_Pin_Value enuValue_cpy)
{
  switch(enuPortIdx_cpy)
	 {
		 case GPIO_PORT_A:
			 if(enuValue_cpy ==GPIO_LOW) //clear
			 {
				 CLR_BIT(GPIO_PORTA_DATA_R,enuPinIdx_cpy);
			 }
			 else if(enuValue_cpy==GPIO_HIGH)
			 {
				 SET_BIT(GPIO_PORTB_DATA_R,enuPinIdx_cpy);
			 }
		 break;

		 case  GPIO_PORT_B:
				 if(enuValue_cpy ==GPIO_LOW) //clear
				 {
					 CLR_BIT(GPIO_PORTB_DATA_R,enuPinIdx_cpy);
				 }
				 else if(enuValue_cpy==GPIO_HIGH)
				 {
					 SET_BIT(GPIO_PORTB_DATA_R,enuPinIdx_cpy);
				 }	  
		 break;

		 case  GPIO_PORT_C:
				 if(enuValue_cpy ==GPIO_LOW) //clear
				 {
					 CLR_BIT(GPIO_PORTC_DATA_R,enuPinIdx_cpy);
				 }
				 else if(enuValue_cpy==GPIO_HIGH)
				 {
					 SET_BIT(GPIO_PORTC_DATA_R,enuPinIdx_cpy);
				 }	  
		 break;

		 case  GPIO_PORT_D:
				 if(enuValue_cpy ==GPIO_LOW) //clear
				 {
					 CLR_BIT(GPIO_PORTD_DATA_R,enuPinIdx_cpy);
				 }
				 else if(enuValue_cpy==GPIO_HIGH)
				 {
					 SET_BIT(GPIO_PORTD_DATA_R,enuPinIdx_cpy);
				 }
		 break;
				 
		 case  GPIO_PORT_E:
				 if(enuValue_cpy ==GPIO_LOW) //clear
				 {
					 CLR_BIT(GPIO_PORTE_DATA_R,enuPinIdx_cpy);
				 }
				 else if(enuValue_cpy==GPIO_HIGH)
				 {
					 SET_BIT(GPIO_PORTE_DATA_R,enuPinIdx_cpy);
				 }	  
		 break;
				 
		 case  GPIO_PORT_F:
				 if(enuValue_cpy ==GPIO_LOW) //clear
				 {
					 CLR_BIT(GPIO_PORTF_DATA_R,enuPinIdx_cpy);
				 }
				 else if(enuValue_cpy==GPIO_HIGH)
				 {
					 SET_BIT(GPIO_PORTF_DATA_R,enuPinIdx_cpy);
				 }  
		 break;
	 } 
}

//get value of specifin pin in any port 
GPIO_Pin_Value GPIO_enuGetPinValue(GPIO_PORTS enuPortIndx_cpy  ,GPIO_PINS enuPinIndx_cpy)
{
	GPIO_Pin_Value enuPinValue_loc;
     switch(enuPortIndx_cpy)
     {
         case GPIO_PORT_A:
        	 enuPinValue_loc=GET_BIT(GPIO_PORTA_DATA_R ,enuPinIndx_cpy);
    	      break;
				 
         case GPIO_PORT_B:
        	 enuPinValue_loc=GET_BIT(GPIO_PORTB_DATA_R ,enuPinIndx_cpy);
            	 break;

         case GPIO_PORT_C:
        	 enuPinValue_loc=GET_BIT(GPIO_PORTC_DATA_R,enuPinIndx_cpy);
            	 break;

         case GPIO_PORT_D:
        	 enuPinValue_loc=GET_BIT(GPIO_PORTD_DATA_R,enuPinIndx_cpy);
            	 break;
				 case GPIO_PORT_E:
        	 enuPinValue_loc=GET_BIT(GPIO_PORTE_DATA_R,enuPinIndx_cpy);
            	 break;
				 case GPIO_PORT_F:
        	 enuPinValue_loc=GET_BIT(GPIO_PORTF_DATA_R,enuPinIndx_cpy);
            	 break;
     }
 	return  enuPinValue_loc;
}



//UART works @baudeRate 115200 -clk:80MHZ
void UART0_voidInit()
{
	SYSCTL_RCGCGPIO_R |= 0X0001;
	SYSCTL_RCGCUART_R |= 0X0001;
  while((SYSCTL_PRGPIO_R&0X1)==0){}
  UART0_CTL_R &=0;
	UART0_IBRD_R=43;
	UART0_FBRD_R=26;	
	UART0_LCRH_R=0X70;//8bitlength-1bit-stop-noParity
  UART0_CTL_R=0X301;
	GPIO_PORTA_AFSEL_R|=0X3;
	GPIO_PORTA_PCTL_R|=0X11;
	GPIO_PORTA_AMSEL_R&=~0x03;
	GPIO_PORTA_DEN_R|=0X3;
}
char UART0_charRecievedChar(void)
{
   while((GET_BIT(UART0_FR_R,UART0_RXFE))==1){}
		 return (char)UART0_DR_R&0XFF;
}
void UART0_voidTransmittedChar(char data)
{
  while((UART0_FR_R&0X0020)!=0){}
	   UART0_DR_R=data;
}
void UART0_voidSendString(char *string)
{
  while(*string!=0)
	{
		UART0_voidTransmittedChar(*string);
		string++;
	}
}

//needed to set frequency @ 80MHZ -copied from "http://armofthings.com/2016/02/13/pll-and-clock-settings-in-tm4c123gh6pm/"
void set_pll_80(void){
	SYSCTL_RCC2_R|=(1<<31); 
	SYSCTL_RCC2_R|=(1<<11);	
	SYSCTL_RCC_R=(SYSCTL_RCC_R&~0x7C0)+0x540; //selecting crystal value and oscillator source
	SYSCTL_RCC2_R&= ~0x70;			
	SYSCTL_RCC2_R &= ~(1<<13);	
  SYSCTL_RCC2_R |= (1<<30);  
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000)+(0x2<<23); //selecting the divisor for running @80 MHz 
  while((SYSCTL_RIS_R&0x40)==0){}; 
  SYSCTL_RCC2_R&=~(1<<11);	
}

