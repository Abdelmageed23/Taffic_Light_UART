/*
 *
 *
 */

#ifndef UART_PRIVATE_H
#define UART_PRICATE_H


/* Registers*/
#define UART_UDR		*(( volatile uint8_t* )0x2C)
#define UART_UCSRA		*(( volatile uint8_t* )0x2B)
#define UART_UCSRB		*(( volatile uint8_t* )0x2A)
#define UART_UCSRC		*(( volatile uint8_t* )0x40)
#define UART_UBRRL		*(( volatile uint8_t* )0x29)
#define UART_UBRRH		*(( volatile uint8_t* )0x40)


/* Registers Pin*/
/*UCSRB*/
#define RXCIE	7	// RX Complete Interrupt Enable
#define TXCIE	6	// TX Complete Interrupt Enable
#define UDRIE	5	// USART Data Register Empty Interrupt Enable
#define RXEN	4	// Receiver Enable
#define TXEN	3	// Transmitter Enable
#define UCSZ2	2	// Character Size  (UCSZ2 bits combined with the UCSZ1)
#define	RXB8	1	// Receive Data Bit 8
#define TXB8	0	// Transmit Data Bit 8

/*UCSRC*/

#define URSEL	7	// Register Select
#define	UMSEL	6	// USART Mode Select
#define	UPM1	5	// Parity Mode
#define	UPM0	4	// Parity Mode
#define	USBS	3	// Stop Bit Select
#define	UCSZ1	2	// Character Size
#define	UCSZ0	1	// Character Size
#define UCPOL	0	// Clock Polarity

/*UCSRA*/

#define	RXC		7	// USART Receive Complete
#define	TXC		6	// USART Transmit Complete
#define	UDRE	5	// USART Data Register Empty
#define	FE		4	// Frame Error
#define	DOR		3	// Data OverRun
#define	PE		2	// Parity Error
#define U2X		1	// Double the USART Transmission Speed
#define	MPCM	0	// Multi-processor Communication Mode


/*Configurations*/
#define ASYNCHRONUS_NORMAL_MODE		1
#define	ASYNCHRONUS_DOUBLE_SPEED	2
#define	SYNCHRONUS_MASTER_MODE		3

/* Operating mode*/
#define ASYNCHRONUS_NORMAL_MODE   	1
#define ASYNCHRONUS_DOUBLE_SPEED  	2
#define SYNCHRONUS_MASTER_MODE    	3

#define DISABLED					1
#define EVEN_PARITY					2
#define ODD_PARITY					3

#define ONE_BIT						1
#define TWO_BIT						2

#define	BITS_5						1
#define BITS_6						2
#define BITS_7						3
#define BITS_8						4
#define BITS_9						5


#define	NO_INTTERRUPT				0
#define TX_INTERRUPT_ONLY			6
#define RX_INTERRUPT_ONLY			7
#define TX_RX_INTERRUPT				8

#define UART_NOTINITIALIZED			0
#define UART_INTIALIZED				1
#endif
