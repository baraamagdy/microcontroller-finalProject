#include "MCAL_GPIO_UART_interface.h"
#include "HAL_KPD_interface.h"

//return key that has been pushed 
char KPD_charGetPressedKey(void)
{
	char KeyNB_Loc='x';
	u8 u8ColIdx_Loc;
	u8 u8RowIdx_Loc;
	GPIO_Pin_Value enuPinValue_Loc=GPIO_HIGH; 
	for(u8ColIdx_Loc =0;u8ColIdx_Loc<COL_NB ;u8ColIdx_Loc++)
	{
		GPIO_voidSetPinValue(KPD_PORT,u8ColIdx_Loc,GPIO_LOW);
		for(u8RowIdx_Loc=0;u8RowIdx_Loc<ROW_NB;u8RowIdx_Loc++)
		{
		  enuPinValue_Loc=GPIO_enuGetPinValue(KPD_PORT,(u8RowIdx_Loc+COL_NB));

			while(enuPinValue_Loc==GPIO_LOW)
			{
				KeyNB_Loc=KeysNumber[u8RowIdx_Loc][u8ColIdx_Loc];
				enuPinValue_Loc=GPIO_enuGetPinValue(KPD_PORT,(u8RowIdx_Loc+COL_NB));
			}
		}
	 GPIO_voidSetPinValue(KPD_PORT,u8ColIdx_Loc,GPIO_HIGH);
	}
	return  KeyNB_Loc;
}