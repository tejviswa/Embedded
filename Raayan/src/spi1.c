#define RCC_BASE        0x40023800
#define GPIOB_BASE      0x40020400
#define GPIOC_BASE      0x40020800
#define SPI2_BASE       0x40003800

#define RCC_AHB1ENR     (*(volatile unsigned int *)(RCC_BASE + 0x30))
#define GPIOB_MODER     (*(volatile unsigned int *)(GPIOB_BASE + 0x00))
#define GPIOB_AFRH      (*(volatile unsigned int *)(GPIOB_BASE + 0x24))
#define GPIOC_MODER     (*(volatile unsigned int *)(GPIOC_BASE + 0x00))
#define GPIOC_AFRL      (*(volatile unsigned int *)(GPIOC_BASE + 0x20))
#define SPI2_CR1        (*(volatile unsigned int *)(SPI2_BASE + 0x00))
#define SPI2_CR2        (*(volatile unsigned int *)(SPI2_BASE + 0x04))
#define SPI2_SR         (*(volatile unsigned int *)(SPI2_BASE + 0x08))
#define SPI2_DR         (*(volatile unsigned int *)(SPI2_BASE + 0x0C))

#define SPI_CR1_DFF     (1 << 11)
#define SPI_CR1_CPOL    (1 << 1)
#define SPI_CR1_CPHA    (1 << 0)
#define SPI_CR1_LSBFIRST (1 << 7)
#define SPI_CR1_SSM     (1 << 9)
#define SPI_CR1_MSTR    (1 << 2)
#define SPI_CR1_SPE     (1 << 6)
#define SPI_CR2_FRF     (1 << 4)
#define SPI_SR_RXNE     (1 << 0)
#define SPI_SR_TXE      (1 << 1)

void SPI2_Slave_Init(void) {
    // Enable GPIOB and GPIOC clocks
    RCC_AHB1ENR |= (1 << 1) | (1 << 2);

    // Configure SPI2 SCK (PB10), MISO (PC2), MOSI (PC3), NSS (PC4) pins as alternate function
    GPIOB_MODER &= ~(0x3 << (10 * 2));
    GPIOB_MODER |= (0x2 << (10 * 2)); // Alternate function for PB10
    GPIOB_AFRH |= (0x5 << ((10 - 8) * 4)); // AF5 for SPI2

    GPIOC_MODER &= ~((0x3 << (2 * 2)) | (0x3 << (3 * 2)) | (0x3 << (4 * 2)));
    GPIOC_MODER |= (0x2 << (2 * 2)) | (0x2 << (3 * 2)) | (0x2 << (4 * 2));
    GPIOC_AFRL |= (0x5 << (2 * 4)) | (0x5 << (3 * 4)) | (0x5 << (4 * 4));

    // 1. Set the data frame format to 8-bit (DFF = 0)
    SPI2_CR1 &= ~SPI_CR1_DFF; // Ensure 8-bit frame format

    // 2. Configure clock polarity (CPOL) and phase (CPHA)
    // Example: CPOL = 0, CPHA = 0
    SPI2_CR1 &= ~SPI_CR1_CPOL; // Clock polarity low
    SPI2_CR1 &= ~SPI_CR1_CPHA; // First clock transition is the first data capture edge

    // 3. Set MSB-first frame format
    SPI2_CR1 &= ~SPI_CR1_LSBFIRST; // MSB transmitted first

    // 4. Configure NSS management
    // Hardware mode: NSS pin is used for slave select
    SPI2_CR1 &= ~SPI_CR1_SSM; // Disable software NSS management

    // 5. Disable TI mode
    SPI2_CR2 &= ~SPI_CR2_FRF; // Motorola mode

    // 6. Configure the SPI in slave mode (MSTR = 0) and enable SPI (SPE = 1)
    SPI2_CR1 &= ~SPI_CR1_MSTR; // Configure as slave
    SPI2_CR1 |= SPI_CR1_SPE;   // Enable SPI
}

unsigned char SPI2_Receive(void) {
    while (!(SPI2_SR & SPI_SR_RXNE)); // Wait until RXNE is set
    return (unsigned char)(SPI2_DR & 0xFF); // Read and return received data
}


void SPI2_outchar(char ch)
{
	while(!(SPI2_SR & SPI_SR_TXE));
	SPI2_DR = ch;
}

unsigned char SPI2_inchar_nonblocking(void)
{
	if((SPI2_SR & SPI_SR_RXNE))
		return  (unsigned char)(SPI2_DR & 0xFF);
	else 
		return 0;
}



void SPI2_Transmit(unsigned char data) {
    while (!(SPI2_SR & SPI_SR_TXE)); // Wait until TXE is set
    SPI2_DR = data; // Write data to transmit
}
unsigned char received ='A';
unsigned char ch;
int main(void) 
	{
    SPI2_Slave_Init();

    while (1) 
			{
        // Example: Echo received data back
        
				SPI2_outchar(received);
				ch = SPI2_inchar_nonblocking();
				received++;
        
    }
}
