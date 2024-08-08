#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H

/*
Use these macros to set the USART_MODE in the config file
*/

#define USART_OperMode_t_Async 			1
#define USART_OperMode_t_Sync			2
/********************************************** USART Registers ************************************************/

#define USART_UDR						(*((volatile u8 *)0x2C))
#define USART_UCSRA						(*((volatile u8 *)0x2B))
#define USART_UCSRB						(*((volatile u8 *)0x2A))
#define USART_UBRRL						(*((volatile u8 *)0x29))
#define USART_UBRRH_UCSRC				(*((volatile u8 *)0x40))

#endif
