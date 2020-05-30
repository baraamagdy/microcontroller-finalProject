#include "stdint.h"
#include <stdbool.h> 
#include "HAL_KPD_interface.h"
#include "MCAL_GPIO_UART_interface.h"

#define passlen         4
#define NumOfRooms      5
#define ConnectedRoom  '1'

#define Led_Red   1  //red->room is unlocked
#define Led_Green 3  //green->room is locked
#define Led_BLUE  2  //password entered wrongly

//user mode
#define Receptionist  '0'
#define Client        '1' 

//room modes
#define Clean     'C'
#define Reserve   'R'
#define CheckOut  'O' 

int main()
{
	set_pll_80();
  UART0_voidInit();
	GPIO_voidPortB_Init();
	GPIO_voidPortF_Init();
	
	int  flag=0;
	int  roomIndx=0;
	char userMode='x';
	char inputChar='x';
	char roomNumber='x';
	char roomStatus='x';  
	bool validRoom=false;
  char hotel[NumOfRooms][(passlen+1)]; //first bit for room number
  
	UART0_voidSendString("SetUp:enter numbers of rooms\n\r"); 
	for(int i=0 ;i<NumOfRooms;i++)
	{
			inputChar =UART0_charRecievedChar();
		  hotel[i][0]=inputChar;	
		  UART0_voidTransmittedChar(inputChar);
			
		}		
  UART0_voidSendString("\n\rReady...\n\r");  
  
  while(1)
	{
		UART0_voidSendString("Enter 0:receptionist, 1:client\n\r");
		userMode =UART0_charRecievedChar();
		UART0_voidTransmittedChar(userMode);			
		
	  switch(userMode)
		 {
			 case Receptionist:
				 //room staus
				 UART0_voidSendString("\n\rEnter R:Reserve, C:Clean, O:Checkout}\n\r");
				 roomStatus =UART0_charRecievedChar();
				 UART0_voidTransmittedChar(roomStatus);				
			 
			   //room number
			   while(validRoom==false)
				  {
				    UART0_voidSendString("\n\rEnter room num \n\r");
				    roomNumber =UART0_charRecievedChar();
				    UART0_voidTransmittedChar(roomNumber);		
            //check if number of room is valid 
			      for(int i=0;i<NumOfRooms;i++)
			       {
					      if(hotel[i][0]==roomNumber)
							  { validRoom=true; break;}
					   }
				    if(validRoom==false)
					   {
					    UART0_voidSendString("\n\rInvalid room number \n\r");
					   }
					 }
				  validRoom=false;
					 
				//to get room index
				 for(int i=0 ; i<NumOfRooms ; i++)
				  {
						if(hotel[i][0]==roomNumber)
						{ roomIndx = i; break;}
					}
					 
				 switch(roomStatus)
					{	
						case Reserve:	
						 UART0_voidSendString(" \n\rSet pass '4-char'\n\r");
						 for(int i=0 ;i<passlen;i++)
							{
								 inputChar =UART0_charRecievedChar();
								 hotel[roomIndx][i]=inputChar;
								 UART0_voidTransmittedChar('*');
							 }
							GPIO_voidSetPinValue(GPIO_PORT_F ,Led_Green,GPIO_HIGH);
              GPIO_voidSetPinValue(GPIO_PORT_F ,Led_Red,GPIO_LOW);							 
						 break;
							 
						case Clean:		 
							GPIO_voidSetPinValue(GPIO_PORT_F ,Led_Green,GPIO_LOW);
							GPIO_voidSetPinValue(GPIO_PORT_F ,Led_Red,GPIO_HIGH);
						 break;
						 
						case CheckOut:
							hotel[roomIndx][1]='n'; 
						  GPIO_voidSetPinValue(GPIO_PORT_F ,Led_Green,GPIO_LOW);
							GPIO_voidSetPinValue(GPIO_PORT_F ,Led_Red,GPIO_HIGH);
						 break;
					 }						 
		     break;
					 
				 case Client: 
					inputChar='x';
				  for(int i=0 ; i<NumOfRooms ; i++)
					 {
						if(hotel[i][0]==ConnectedRoom)
						{ roomIndx = i; break;}
					 }
				  for(int i=0 ;i<passlen;i++)
				   {
						 while(inputChar=='x')
							{
   							inputChar =KPD_charGetPressedKey();
							}
							
						if(hotel[roomIndx][i]==inputChar)
						 {
							  flag++;
								
						 }
							 inputChar='x'; 
				   }
					if(flag==passlen)
					 {
						 GPIO_voidSetPinValue(GPIO_PORT_F ,Led_Green,GPIO_LOW);
						 GPIO_voidSetPinValue(GPIO_PORT_F ,Led_Red,GPIO_HIGH);
					 }
					flag=0;
         break;							 		 	
			}
	 }
}








