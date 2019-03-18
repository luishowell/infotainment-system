#include "config.h"
#include "MMA8652FCR1.h"


using namespace std;

//constructor
MMA8652FCR1::MMA8652FCR1(){}




/*
    Function used to set up the accelerometer
*/
bool MMA8652FCR1::init(int devID, int intPin1, int intPin2)
{
#ifdef RPI
    //set the interrupt pins as inputs
    this->m_intPin1 = intPin1;
    this->m_intPin2 = intPin2;
    pinMode(intPin1, INPUT);
    pinMode(intPin2, INPUT);
    
    //save the deviceID and check it is present
    this->m_devID = devID;
    this->fd = 53; //test val
    this->fd = wiringPiI2CSetup(devID);    //initialise the I2C
    if(fd == -1)
    {
        cout << "Error initialising the i2c device: " << errno << endl;
        return false;    //error response    
    }


    //check the who am i register
    int result = wiringPiI2CReadReg8(this->fd, 0x0D);
    cout << "Who am i reg says: 0x"  << hex << result << endl;
    if(result != 0x4A)
    {
        cout << "Who am i register mistmatch." << endl << "Expecting: 0x4A Received: " << hex << result << endl; 
    }
    
    //set the configuration registers
    result = wiringPiI2CWriteReg8(this->fd, 0x2A, 0x00); //put into standby mode
    
    result = wiringPiI2CWriteReg8(this->fd, 0x09, 0x00); //turn off the FIFO
    result = wiringPiI2CWriteReg8(this->fd, 0x0E, 0x02); //set the range to 8G
    result = wiringPiI2CWriteReg8(this->fd, 0x2A, 0x18); //set data rate to 100Hz
    result = wiringPiI2CWriteReg8(this->fd, 0x2B, 0x00); //set power mode to auto sleep off
    result = wiringPiI2CWriteReg8(this->fd, 0x2C, 0x00); //set interrupt to be active high
    result = wiringPiI2CWriteReg8(this->fd, 0x2D, 0x01); //set the interrupt to be triggered by data ready
    result = wiringPiI2CWriteReg8(this->fd, 0x2E, 0x01); //route interrupt to INT2 pin
    
    result = wiringPiI2CWriteReg8(this->fd, 0x2A, 0x19); //set to active mode
    
    //get static values
    staticVals = new accValues_t;
    this->recordStatic();   

    
#endif
    return true; 

}


/*
    Records current readings in staticVals
*/
void MMA8652FCR1::recordStatic()
{
    this->getData(staticVals);
}


/*
    Function used to get and record data from the accelerometer
    Converts using 2's complement
*/
void MMA8652FCR1::getData(accValues_t *data)
{
#ifdef RPI

    //read the data values from the registers
    int xMSB = wiringPiI2CReadReg8(this->fd,0x01);
    int xLSB = wiringPiI2CReadReg8(this->fd,0x02);
    int yMSB = wiringPiI2CReadReg8(this->fd,0x03);
    int yLSB = wiringPiI2CReadReg8(this->fd,0x04);
    int zMSB = wiringPiI2CReadReg8(this->fd,0x05);
    int zLSB = wiringPiI2CReadReg8(this->fd,0x06);
    
    
    //do twos complement conversion
    data->xAxis = this->twosComp(xMSB, xLSB);
    data->yAxis = this->twosComp(yMSB, yLSB);
    data->zAxis = this->twosComp(zMSB, zLSB);
    
#endif
    return;
}



/*
    Performs the twos complement of a single byte of data
    and scales to 8G
*/
double MMA8652FCR1::twosComp(uint8_t MSB)
{
    double returnVal;
    
    uint16_t twosCompVal = MSB;
    int sign = 1;
    
    if(MSB > 0x7F)
    {
        twosCompVal = (~twosCompVal + 1);
        sign = -1;
    }else{
        twosCompVal = twosCompVal;
    }
        
    //scale to 8G
    returnVal = ((twosCompVal & 0xFF) * 8 * sign)/(pow(2,7));
    
    return returnVal;
}


/*
    Performs the twos complement on 12-bit of data
    and scales to 8G
*/
double MMA8652FCR1::twosComp(uint8_t MSB, uint8_t LSB)
{
    double returnVal;
    
    uint16_t twosCompVal = ((MSB << 8)| LSB) >> 4;
    int sign = 1;
    
    if(MSB > 0x7F)
    {
        twosCompVal = (~twosCompVal + 1);
        sign = -1;
    }else{
        twosCompVal = twosCompVal;
    }
        
    //scale to 8G
    returnVal = ((twosCompVal & 0xFF) * 8 * sign)/(pow(2,11));
    
    return returnVal;
}
