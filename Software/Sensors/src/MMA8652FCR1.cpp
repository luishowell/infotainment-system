/**
 * @file MMA8652FCR1.cpp
 * @author Joe Walker
 * @brief Implementation of MMA8652FCR1 class.
 * @version 0.1
 * @date 2019-02-25
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "config.h"
#include "MMA8652FCR1.h"


using namespace std;

//constructor
MMA8652FCR1::MMA8652FCR1(){
    staticVals = new accValues_t;
}




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
    int result = wiringPiI2CReadReg8(this->fd, MMA8652FCR1_WHO_AM_I_REG);
    if(result != MMA8652FCR1_DEVICE_ID)
    {
        cout << "Who am i register mistmatch." << endl << "Expecting: 0x4A Received: " << hex << result << endl; 
        return false;
    }
    
    //set the configuration registers
    result = wiringPiI2CWriteReg8(this->fd, MMA8652FCR1_CTRL_REG1, 0x00); //put into standby mode
    
    result = wiringPiI2CWriteReg8(this->fd, MMA8652FCR1_F_SETUP_REG, 0x00); //turn off the FIFO
    result = wiringPiI2CWriteReg8(this->fd, MMA8652FCR1_XYZ_DATA_CFG_REG, 0x02); //set the range to 8G
    result = wiringPiI2CWriteReg8(this->fd, MMA8652FCR1_CTRL_REG1, 0x18); //set data rate to 100Hz
    result = wiringPiI2CWriteReg8(this->fd, MMA8652FCR1_CTRL_REG2, 0x00); //set power mode to auto sleep off
    result = wiringPiI2CWriteReg8(this->fd, MMA8652FCR1_CTRL_REG3, 0x00); //set interrupt to be active high
    result = wiringPiI2CWriteReg8(this->fd, MMA8652FCR1_CTRL_REG4, 0x01); //set the interrupt to be triggered by data ready
    result = wiringPiI2CWriteReg8(this->fd, MMA8652FCR1_CTRL_REG5, 0x01); //route interrupt to INT2 pin
    
    result = wiringPiI2CWriteReg8(this->fd, MMA8652FCR1_CTRL_REG1, 0x19); //set to active mode
    
    //get static values
    this->recordStatic();   

    return true;
    
#endif
    return false; 

}


/*
    Records current readings in staticVals
*/
bool MMA8652FCR1::recordStatic()
{
    return this->getData(staticVals);
}


/*
    Function used to get and record data from the accelerometer
    Converts using 2's complement
*/
bool MMA8652FCR1::getData(accValues_t *data)
{
#ifdef RPI

    //read the data values from the registers
    int xMSB = wiringPiI2CReadReg8(this->fd,MMA8652FCR1_OUT_X_MSB_REG);
    int xLSB = wiringPiI2CReadReg8(this->fd,MMA8652FCR1_OUT_X_LSB_REG);
    int yMSB = wiringPiI2CReadReg8(this->fd,MMA8652FCR1_OUT_Y_MSB_REG);
    int yLSB = wiringPiI2CReadReg8(this->fd,MMA8652FCR1_OUT_Y_LSB_REG);
    int zMSB = wiringPiI2CReadReg8(this->fd,MMA8652FCR1_OUT_Z_MSB_REG);
    int zLSB = wiringPiI2CReadReg8(this->fd,MMA8652FCR1_OUT_Z_LSB_REG);
    
    
    //do twos complement conversion
    data->xAxis = this->twosComp(xMSB, xLSB);
    data->yAxis = this->twosComp(yMSB, yLSB);
    data->zAxis = this->twosComp(zMSB, zLSB);
    
    return true;
#endif
    return false;
}



/*
    Performs the twos complement of a single byte of data
    and scales to max range
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
        
    //scale to max range
    returnVal = ((twosCompVal & 0xFF) * m_accRange * sign)/(pow(2,7));
    
    return returnVal;
}


/*
    Performs the twos complement on 12-bit of data
    and scales to max range
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
        
    //scale to max range
    returnVal = ((twosCompVal & 0xFFF) * m_accRange * sign)/(pow(2,11));
    
    return returnVal;
}
