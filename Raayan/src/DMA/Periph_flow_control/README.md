
# **Peripheral Flow Control Mode in DMA for STM32 (USART Example)**

## **Overview**
Peripheral Flow Control Mode in DMA for STM32 allows the peripheral to dictate the number of data items to be transferred instead of the DMA.  
In normal DMA mode, the **DMA_SxNDTR** register is preloaded with a value that decrements with each transfer until zero.  
However, in **Peripheral Flow Control Mode**, the peripheral device controls the flow and stops the DMA transfer when it has finished its operation.  

This is useful when the exact amount of data is unknown beforehand, such as in UART or SPI communication where message lengths may vary.  

---

## **Registers Involved**

### **DMA Registers:**
- **DMA_SxCR (Stream Configuration Register)**  
  - **PFCTRL (Bit 5):**  
    - 0: DMA is the flow controller (normal mode)  
    - 1: Peripheral is the flow controller  
  - **DIR (Bits 6:7):**  
    - 00: Peripheral to memory  
    - 01: Memory to peripheral  

- **DMA_SxNDTR (Number of Data Register)**  
  - Holds the number of data items to be transferred.  
  - In peripheral flow control mode, it decrements dynamically as the peripheral sends requests.  

- **DMA_SxPAR (Peripheral Address Register)**  
  - Holds the address of the peripheral data register.  

- **DMA_SxM0AR (Memory Address Register)**  
  - Holds the memory buffer address.  

- **DMA_LISR & DMA_HISR (Interrupt Status Registers)**  
  - Hold status flags such as transfer complete (TCIF) and transfer error (TEIF).  

---

## **USART in Peripheral Flow Control Mode**

### **USART Registers:**
- **USART_SR (Status Register):**  
  - **RXNE (Bit 5):** Receive Not Empty  
  - **TXE (Bit 7):** Transmit Empty  

- **USART_DR (Data Register):**  
  - Holds data for transmission or reception.  

- **USART_CR3 (Control Register 3):**  
  - **DMAR (Bit 6):** Enable DMA for RX  
  - **DMAT (Bit 7):** Enable DMA for TX  

---

## **How NDTR Works in Peripheral Flow Control Mode**

- **NDTR** is initialized with a large value (often **0xFFFF**).  
- It decrements **by 1** with each successful transfer.  
- Final **NDTR** value reflects how many elements were **not** transferred.  

**Example:**  
- Start with **NDTR = 0xFFFF**  
- End with **NDTR = 0xFFFE**  
- **1 byte** was transferred.  

---

## **Bare-Metal Example for USART2_RX with DMA**

```c
// Enable Clocks
RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;   // Enable DMA1 clock
RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // Enable USART2 clock

// USART2 Configuration
USART2->BRR = 0x008A;  // Baud rate (115200)
USART2->CR3 |= USART_CR3_DMAR;  // Enable DMA for RX
USART2->CR1 |= USART_CR1_UE | USART_CR1_RE;  // Enable USART, RX

// DMA1_Stream5 Configuration
DMA1_Stream5->PAR = (uint32_t)&USART2->DR;  // Peripheral address
DMA1_Stream5->M0AR = (uint32_t)rx_buffer;   // Memory address
DMA1_Stream5->CR |= DMA_SxCR_PFCTRL;        // Peripheral Flow Control
DMA1_Stream5->CR &= ~DMA_SxCR_DIR;          // Peripheral to Memory
DMA1_Stream5->CR |= DMA_SxCR_MINC;          // Memory increment mode
DMA1_Stream5->NDTR = 0xFFFF;                // Large initial value
DMA1_Stream5->CR |= DMA_SxCR_EN;            // Enable DMA

// Reading Data
uint16_t received_length = 0xFFFF - DMA1_Stream5->NDTR;
```

---

## **Does DMA Automatically Check TXE and RXNE?**

Yes, in **Peripheral Flow Control Mode**, the DMA automatically monitors the **TXE** and **RXNE** bits of **USART2**:

- **RXNE (Receive Not Empty)**:  
  - DMA reads **USART_DR**, clearing **RXNE**.  
  - **NDTR decrements by 1** for each transfer.  

- **TXE (Transmit Empty)**:  
  - DMA writes to **USART_DR**, clearing **TXE**.  
  - **NDTR decrements by 1** for each transfer.  

This eliminates the need for the CPU to manually check the status bits, improving efficiency.  

---

## **Conclusion**
Peripheral flow control mode is ideal for situations where the length of data is unknown.  
It leverages hardware automation to reduce CPU load and improves efficiency during continuous or burst data transfers.  

---

### **References**
- STM32F4 Reference Manual (DMA and USART sections)
