#ifndef GPIO_KPD_UART_interface_h
#define GPIO_KPD_UART_interface_h


typedef unsigned char u8 ;  
typedef enum{ GPIO_LOW,GPIO_HIGH }GPIO_Pin_Value;

typedef enum{ GPIO_INPUT, GPIO_OUTPUT }GPIO_Pin_Dir;

typedef enum{ GPIO_PORT_A, GPIO_PORT_B, GPIO_PORT_C,
	            GPIO_PORT_D, GPIO_PORT_E, GPIO_PORT_F }GPIO_PORTS;

typedef enum{ GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3,
            	GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7 }GPIO_PINS;

void set_pll_80(void);//set clk by 80mhz
						
							
void GPIO_voidPortF_Init(void);
void GPIO_voidPortB_Init(void);							
						
void UART0_voidInit(void);
char UART0_charRecievedChar(void);
void UART0_voidSendString(char *string);							
void UART0_voidTransmittedChar(char data);
							
GPIO_Pin_Value GPIO_enuGetPinValue(GPIO_PORTS enuPortIndx_cpy  ,GPIO_PINS enuPinIndx_cpy);
void GPIO_voidSetPinValue(GPIO_PORTS enuPortIdx_cpy, GPIO_PINS enuPinIdx_cpy,GPIO_Pin_Value enuValue_cpy);

#endif						