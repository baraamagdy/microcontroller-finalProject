

#define KPD_PORT      GPIO_PORT_B
#define ROW_NB  4   
#define COL_NB  4

static char KeysNumber[ROW_NB][COL_NB]={ {'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'} };

char KPD_charGetPressedKey(void);