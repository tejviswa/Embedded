

void KM_I2C1_init(void);
void KM_I2C1_config(void);

int KM_I2C1_IsDeviceReady(short int DevAddr,int Timeout);

int KM_I2C1_RTC_MemWrite(short int DevAddr,short int MemAddr,short int MemAddrSize,unsigned char *data,short int length);

int KM_I2C1_RTC_MemRead(short int DevAddr,short int MemAddr,short int MemAddrSize,unsigned char *data,short int length);



//dev addr= 0x68  || memaddr=0x02 || memaddrsize=0x01 || char data =Date ||short int length =2