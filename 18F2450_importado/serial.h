// THE BAUDRATE CLOCK IS DERIVED FROM AN INTERNAL SYSTEM CLOCK OF 48MHZ !!!
//
// spbrg =  ( Fosc / ( 16 * B )) - 1 = (48Mhz / ( 16 * 19200 )) - 1
/*
#define FOSC 48000000
#define BaudcntHigh(baud) (int)((FOSC/( 16.0 * baud ) ) - 0.5)
#define BaudcntLow(baud) (int)((FOSC/( 64.0 * baud ) ) - 0.5)

// definition of baudrate constants to be written into spbrg
typedef enum
{
  baud_9600   = BaudcntLow(9600),
  baud_19200  = BaudcntHigh(19200),
  baud_38400  = BaudcntHigh(38400),
  baud_57600  = BaudcntHigh(57600),
  baud_115200 = BaudcntHigh(115200)
} SERIAL_SPEED;

*/
// Serial receive buffer size
#define SERIAL_BUFFER_SIZE 16

// FIFO buffer
typedef struct{
	char buffer[SERIAL_BUFFER_SIZE];
	char *in;
	char *out;
	int count;
} SERIAL_FIFO;
void InitializeUsart(void);
// Open serial connection with predefined baudrate
void SerialOpenConnection(int baud);

// Close serial connection
void SerialCloseConnection(void);

// Serial transmit routines
void SeralTransmitChar(char c);
void SerialTransmitInt(int i);
void SerialTransmitString(char *s);

// Check if transmitter register ready
int SerialTransmitterReady(void);

// Receive a character
char SerialReceive(void);

#ifdef _SERIAL_RX_ON_INTERRUPT
// Interrupt service routine for serial receive on interrupt
void SerialReceiveInterrupt(void);
int SerialDataAvailable(void);
#endif

#ifdef _SERIAL_TX_ON_INTERRUPT
// Interrupt service routine for serial transmit on interrupt (NOT IMPLEMENTED YET)
void SerialTransmitInterrupt(void);
#endif

//#endif
//#pragma idata 
char TRXcount=0; 


//#pragma udata 
//char limpiarRX;
//SERIAL_FIFO receiveBuffer;