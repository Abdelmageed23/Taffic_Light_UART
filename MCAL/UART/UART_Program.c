/*********************************************/
/* Author  : Abdelrahman Mohamed     		 */
/* Date     : 27 Jan	2022               	 */
/* Version  : V01                          	 */
/*********************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


#include "UART_Interface.h"
#include "UART_Private.h"
#include "UART_Config.h"

#ifndef F_CPU
#define F_CPU	8000000			//8MHz
#endif


static uint8_t UART_InitChack = UART_NOTINITIALIZED;

uint8_t UART_Init(void)
{
	uint8_t UART_UCSRC_local = UART_NOTINITIALIZED;
	SET_BIT(UART_UCSRC_local,URSEL);
	/* Configure the baud prescale based on mode on config file */
#if	UART_OPERATING_MODE == ASYNCHRONUS_NORMAL_MODE
#define BAUD_PRESCALE (((F_CPU / (UART_BAUDRATE * 16UL))) - 1)
			CLR_BIT(UART_UCSRC_local,UMSEL);	//	ASynchronous Operation
#elif	UART_OPERATING_MODE ==	ASYNCHRONUS_DOUBLE_SPEED
#define BAUD_PRESCALE (((F_CPU / (UART_BAUDRATE * 8UL))) - 1)
			CLR_BIT(UART_UCSRC,UMSEL);	//	ASynchronous Operation
#elif UART_OPERATING_MODE	==	SYNCHRONUS_MASTER_MODE
#define BAUD_PRESCALE (((F_CPU / (UART_BAUDRATE * 2UL))) - 1)
		SET_BIT(UART_UCSRC,UMSEL);	//	Synchronous Operation
#else
	#error "Wrong Operating Mode"
#endif

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	CLR_BIT(UART_UBRRH,URSEL);
	UART_UBRRH = (BAUD_PRESCALE ) >> 8;
	UART_UBRRL= BAUD_PRESCALE;

	/* Enable receiver and transmitter */
	SET_BIT(UART_UCSRB,RXEN);
	SET_BIT(UART_UCSRB,TXEN);

	/* UART INTERRUPT STATE*/
#if UART_INTERRUPT == NO_INTTERRUPT
#elif UART_INTERRUPT == TX_INTERRUPT_ONLY
	SET_BIT(UART_UCSRB,TXCIE);
#elif UART_INTERRUPT == RX_INTERRUPT_ONLY
	SET_BIT(UART_UCSRB,RXCIE);
#elif UART_INTERRUPT == TX_RX_INTERRUPT
	SET_BIT(UART_UCSRB,TXCIE);
	SET_BIT(UART_UCSRB,RXCIE);
#else
#error "Wrong Interrupt configuration, please check Config file"
#endif


	/* Configure the parity based on Configuration file */
#if UART_PARITY == DISABLED
	CLR_BIT(UART_UCSRC_local,UPM0);
	CLR_BIT(UART_UCSRC_local,UPM1);
#elif	UART_PARITY == 	EVEN_PARITY
	SET_BIT(UART_UCSRC_local,UPM0);
	CLR_BIT(UART_UCSRC_local,UPM1);
#elif	UART_PARITY == 	ODD_PARITY
	SET_BIT(UART_UCSRC_local,UPM0);
	SET_BIT(UART_UCSRC_local,UPM1);
#else
#error "Wrong Parity configuration"
#endif


	/* Configure the STOP BIT based on Configuration file */
#if	STOP_BIT	==	ONE_BIT
	CLR_BIT(UART_UCSRC_local,USBS);
#elif STOP_BIT	==	TWO_BIT
	SET_BIT(UART_UCSRC_local,USBS);
#else
#error "Wrong STOP configuration"
#endif

	/* Configure the Character size based on Configuration file */
#if 	CHARACTER_SIZE ==	BITS_5
	CLR_BIT(UART_UCSRC_local,UCSZ0);
	CLR_BIT(UART_UCSRC_local,UCSZ1);
	CLR_BIT(UART_UCSRC_local,UCSZ2);
#elif	CHARACTER_SIZE ==	BITS_6
	SET_BIT(UART_UCSRC_local,UCSZ0);
	CLR_BIT(UART_UCSRC_local,UCSZ1);
	CLR_BIT(UART_UCSRC_local,UCSZ2);
#elif	CHARACTER_SIZE ==	BITS_7
	CLR_BIT(UART_UCSRC_local,UCSZ0);
	SET_BIT(UART_UCSRC_local,UCSZ1);
	CLR_BIT(UART_UCSRC_local,UCSZ2);
#elif	CHARACTER_SIZE ==	BITS_8
	SET_BIT(UART_UCSRC_local,UCSZ0);
	SET_BIT(UART_UCSRC_local,UCSZ1);

#elif	CHARACTER_SIZE ==	BITS_9
	SET_BIT(UART_UCSRC_local,UCSZ0);
	SET_BIT(UART_UCSRC_local,UCSZ1);
#else
#error		"Wrong Character configuration"
#endif
	UART_UCSRC = UART_UCSRC_local;
	UART_InitChack =UART_INTIALIZED;
	return OK;
}


uint8_t UART_SendByte(uint8_t Data)
{
	if(UART_InitChack ==UART_NOTINITIALIZED)
	{
		return NOK;
	}
	else
	{
	/* Wait for empty transmit buffer */
	while( (GET_BIT(UART_UCSRA,UDRE)) ==0);

	/* Put data into buffer, sends the data */
	UART_UDR = Data;
	return OK;
	}

}

uint8_t UART_ReciveByte(uint8_t* Data)
{
	if(UART_InitChack ==UART_NOTINITIALIZED)
		{
			return NOK;
		}
		else
		{
	/* Wait for data to be received */
	while ( (GET_BIT(UART_UCSRA,RXC)) ==0 );

	/* Get and return received data from buffer */
	*Data = (uint8_t)UART_UDR;

	return OK;
		}
}



uint8_t UART_SendString(uint8_t *String)
{
	if(UART_InitChack ==UART_NOTINITIALIZED)
		{
			return NOK;
		}
	else
	{
	uint8_t i = 0;
	/* keep sending to null terminator  */
	while(String[i] != '\0')
	{
		UART_SendByte(String[i]);
		i++;
	}
	return OK;
	}

}


uint8_t UART_ReceiveString(uint8_t *String)
{
	if(UART_InitChack == UART_NOTINITIALIZED)
			{
				return NOK;
			}
		else
		{
			uint8_t i = 0;
			 UART_ReciveByte(&String[i]);
			/*Enter condition to end the string*/
			while(String[i] != '\n' && String[i] !='\r')
			{
				i++;
				  UART_ReciveByte(&String[i]);
			}
			String[i] = '\0';
			return OK;
		}
}


void UART_Flush( void )
{
	uint8_t dummy;
	while ( UART_UCSRA & (1<<RXC) ) dummy = UART_UDR;
}

/* ISR of when Receiving  complete */
void UART_RxCompleteISR(void(*Callback)(void))
{
	UART_RxCompleteCallBack = Callback;
}

void __vector_13(void)__attribute__((signal));
void __vector_13(void)
{
	UART_RxCompleteCallBack();
}

/* ISR of when Transmit complete */
void UART_TxCompleteISR(void(*Callback)(void))
{
	UART_RxCompleteCallBack = Callback;
}

void __vector_15(void)__attribute__((signal));
void __vector_15(void)
{
	UART_TxCompleteCallBack();
}
