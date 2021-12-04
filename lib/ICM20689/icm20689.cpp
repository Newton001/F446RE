/***************************************************
  This is a library for the ICM20689

  Written by Newton Kelvin, a hobbyist
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <mbed.h>
#include <icm20689.h>


#if 0
static UnbufferedSerial serial_port(USART_1_TX, USART_1_RX);
static UnbufferedSerial serial_port(USBTX, USBRX);
FileHandle *mbed::mbed_override_console(int fd)
{
    return &serial_port;
}

#endif

//Allow the pin allocation for the I2C communication in main.cpp
//ICM20689::ICM20689(PinName SDA, PinName SCL) : connection(SDA, SCL)
//{
//}

I2C connection(D14,D15);



//Acc Full Scale Range 

enum Ascale
{
    AFS_2G,
    AFS_4G,
    AFS_8G,
    AFS_16G
};

//Gyro Full Scale Range 

enum Gscale
{
    GFS_250DPS,
    GFS_500DPS,
    GFS_1000DPS,
    GFS_2000DPS
};


//Scale Resolutions per LSB for the sensors

float aRes, gRes;
int Ascale = AFS_2G;
int Gscale = GFS_2000DPS;

void ICM20689_WriteByte(uint8_t ICM20689_reg, uint8_t ICM20689_data)
{
    char data_out[2];
    data_out[0]=ICM20689_reg;
    data_out[1]=ICM20689_data;
    connection.write(ICM20689_slave_addr, data_out, 2, 0);
}

uint8_t ICM20689_ReadByte(uint8_t ICM20689_reg)
{
    char data_out[1], data_in[1];
    data_out[0] = ICM20689_reg;
    connection.write(ICM20689_slave_addr, data_out, 1, 1);
    connection.read(ICM20689_slave_addr, data_in, 1, 0);
    return (data_in[0]);
}

//Connection Test: WHO_AM_I register reading

void ICM20689::whoAmI()
{
    uint8_t whoAmI = ICM20689_ReadByte(WHO_AM_I); // Value Returned should be 0x68
    printf("I AM ICM20689: 0x%x \r\n", whoAmI);

    if(whoAmI==0x12)//0x68
    {
        printf("ICM20689 is online .....\r\n");
    }

    else
    {
        printf("Connection halted!!!\r\n Check Connection \r\n");
    }
}

void ICM20689::init()
{
    connection.frequency(400000);
    ICM20689_WriteByte(PWR_MGMT_1, 0x00); // CLK_SEL=0: internal 8MHz, TEMP_DIS=0, SLEEP=0 
    ICM20689_WriteByte(SMPLRT_DIV, 0x07); // Gyro output sample rate = Gyro Output Rate/(1+SMPLRT_DIV)
    ICM20689_WriteByte(CONFIG, 0x01); //176Hz     // set TEMP_OUT_L, DLPF=3 (Fs=1KHz):0x03
//    ICM20689_WriteByte(GYRO_CONFIG, 0x00); // bit[4:3] 0=+-250d/s,1=+-500d/s,2=+-1000d/s,3=+-2000d/s :0x18
//    ICM20689_WriteByte(ACCEL_CONFIG, 0x00);// bit[4:3] 0=+-2g,1=+-4g,2=+-8g,3=+-16g, ACC_HPF=On (5Hz):0x01
    setAccRange(Ascale);
    setGyroRange(Gscale);
}

int16_t ICM20689::getAccXvalue()
{
    uint8_t LoByte, HiByte;
    LoByte = ICM20689_ReadByte(ACCEL_XOUT_L); // read Accelerometer X_Low  value
    HiByte = ICM20689_ReadByte(ACCEL_XOUT_H); // read Accelerometer X_High value
    return((HiByte<<8) | LoByte);
//    printf("accx:%d,%d\r\n",HiByte,LoByte);  // send data to matlab
}

int16_t ICM20689::getAccYvalue()
{
    uint8_t LoByte, HiByte;
    LoByte = ICM20689_ReadByte(ACCEL_YOUT_L); // read Accelerometer X_Low  value
    HiByte = ICM20689_ReadByte(ACCEL_YOUT_H); // read Accelerometer X_High value
    return((HiByte<<8) | LoByte);
//    printf("accy:%d,%d\r\n",HiByte,LoByte);  // send data to matlab
}

int16_t ICM20689::getAccZvalue()
{
    uint8_t LoByte, HiByte;
    LoByte = ICM20689_ReadByte(ACCEL_ZOUT_L); // read Accelerometer X_Low  value
    HiByte = ICM20689_ReadByte(ACCEL_ZOUT_H); // read Accelerometer X_High value
    return((HiByte<<8) | LoByte);
//    printf("accx:%d,%d\r\n",HiByte,LoByte);  // send data to matlab
}

int16_t ICM20689::getGyrXvalue()
{
    uint8_t LoByte, HiByte;
    LoByte = ICM20689_ReadByte(GYRO_XOUT_L); // read Accelerometer X_Low  value
    HiByte = ICM20689_ReadByte(GYRO_XOUT_H); // read Accelerometer X_High value
    return((HiByte<<8) | LoByte);
//    printf("accx:%d,%d\r\n",HiByte,LoByte);  // send data to matlab
}

int16_t ICM20689::getGyrYvalue()
{
    uint8_t LoByte, HiByte;
    LoByte = ICM20689_ReadByte(GYRO_YOUT_L); // read Accelerometer X_Low  value
    HiByte = ICM20689_ReadByte(GYRO_YOUT_H); // read Accelerometer X_High value
    return((HiByte<<8) | LoByte);
//    printf("accx:%d,%d\r\n",HiByte,LoByte);  // send data to matlab
}

int16_t ICM20689::getGyrZvalue()
{
    uint8_t LoByte, HiByte;
    LoByte = ICM20689_ReadByte(GYRO_ZOUT_L); // read Accelerometer X_Low  value
    HiByte = ICM20689_ReadByte(GYRO_ZOUT_H); // read Accelerometer X_High value
    return((HiByte<<8) | LoByte);
//    printf("accx:%d,%d\r\n",HiByte,LoByte);  // send data to matlab
}

int16_t ICM20689::getIMUTemp()
{
    uint8_t LoByte, HiByte;
    LoByte = ICM20689_ReadByte(TEMP_OUT_L);
    HiByte = ICM20689_ReadByte(TEMP_OUT_H);
    return ((HiByte<<8) | LoByte);
}


//Calculating Acc Resolution

float ICM20689::setAccRange(int Ascale)
{
    switch(Ascale)
    {
        case AFS_2G:
            aRes = 2.0/32768.0;
            break;
        case AFS_4G:
            aRes = 4.0/32768.0;
            break;
        case AFS_8G:
            aRes = 8.0/32768.0;
            break;
        case AFS_16G:
            aRes = 16.0/32768.0;
            break;
    }
    ICM20689_WriteByte(ACCEL_CONFIG, Ascale<<3); // bit[4:3] 0=+-2g,1=+-4g,2=+-8g,3=+-16g, ACC_HPF=On (5Hz)
    return aRes;
}

//Calculating Gyro Resolution

float ICM20689::setGyroRange(int Gscale)
{
    switch(Gscale)
    {
        case GFS_250DPS:
            gRes = 250.0/32768.0;
            break;
        case GFS_500DPS:
            gRes = 500.0/32768.0;
            break;
        case GFS_1000DPS:
            gRes = 1000.0/32768.0;
            break;
        case GFS_2000DPS:
            gRes = 2000.0/32768.0;
            break;
    }
    ICM20689_WriteByte(GYRO_CONFIG, Gscale<<3); // bit[4:3] 0=+-250d/s,1=+-500d/s,2=+-1000d/s,3=+-2000d/s
    return gRes;
}