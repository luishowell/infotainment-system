/**
 * @file MMA8652FCR1.h
 * @author Joe Walker
 * @brief The class MMA8652FCR1.h provides methods for controlling the operation of the accelerometer of the same name.
 * @version 0.1
 * @date 2019-02-25
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef MMA8652FCR1_H
#define MMA8652FCR1_H

#include "config.h"
#include "types.h"

#include <stdio.h>
#include <iostream>
#include <errno.h>
#include <cmath>
#include <string.h>

#ifdef RPI
#include <wiringPi.h>
#include <wiringPiI2C.h>
#endif

//define the register addresses
#define MMA8652FCR1_STATUS_REG              0x00 // Status register (R)
#define MMA8652FCR1_OUT_X_MSB_REG           0x01 // 8 most significant bits of the x-axis register (R)
#define MMA8652FCR1_OUT_X_LSB_REG           0x02 // Register containing the 4 least significant bits of x-axis data (R)
#define MMA8652FCR1_OUT_Y_MSB_REG           0x03 // 8 most significant bits of the y-axis register (R)
#define MMA8652FCR1_OUT_Y_LSB_REG           0x04 // Register containing the 4 least significant bits of y-axis data (R)
#define MMA8652FCR1_OUT_Z_MSB_REG           0x05 // 8 most significant bits of the z-axis register (R)
#define MMA8652FCR1_OUT_Z_LSB_REG           0x06 // Register containing the 4 least significant bits of z-axis data (R)
#define MMA8652FCR1_F_SETUP_REG             0x09 // FIFO setup register (R/W)
#define MMA8652FCR1_TRIG_CFG_REG            0x0A // Map of FIFO capture events (R/W)
#define MMA8652FCR1_SYSMOD_REG              0x0B // Current system mode (R)
#define MMA8652FCR1_INT_SOURCE_REG          0x0C // Interrupt status (R)
#define MMA8652FCR1_WHO_AM_I_REG            0x0D // Who am i register (R)
#define MMA8652FCR1_XYZ_DATA_CFG_REG        0x0E // Dynamic range settings (R/W)
#define MMA8652FCR1_HP_FILTER_CUTOFF_REG    0x0F // High-pass filter selection (R/W)
#define MMA8652FCR1_PL_STATUS_REG           0x10 // Landscape/portrait orientation status (R)
#define MMA8652FCR1_PL_CFG_REG              0x11 // landscape/portrait configuration (R/W)
#define MMA8652FCR1_PL_COUNT_REG            0x12 // landscape/portrait debounce counter (R/W)
#define MMA8652FCR1_PL_BF_ZCOMP_REG         0x13 // back/front, z-lock trip threshold (R/W)
#define MMA8652FCR1_P_L_THS_REG             0x14 // portrait/landscape thershold and hysteresis (R/W)
#define MMA8652FCR1_FF_MT_CFG_REG           0x15 // freefall/motion functional block configuration (R/W)
#define MMA8652FCR1_FF_MT_SRC_REG           0x16 // freefall/motion event source register (R)
#define MMA8652FCR1_FF_MT_THS_REG           0x17 // freefall/motion threshold register (R/W)
#define MMA8652FCR1_FF_MT_COUNT_REG         0x18 // freefall/motion debounce counter (R/W)
#define MMA8652FCR1_TRANSIENT_CFG_REG       0x1D // transient functional block configuration (R/W)
#define MMA8652FCR1_TRANSIENT_SRC_REG       0x1E // transient event status register (R)
#define MMA8652FCR1_TRANSIENT_THS_REG       0x1F // transient event threshold (R/W)
#define MMA8652FCR1_TRANSIENT_COUNT_REG     0x20 // transient debounce counter (R/W)
#define MMA8652FCR1_PULSE_CFG_REG           0x21 // pulse enable configuration (R/W)
#define MMA8652FCR1_PULSE_SRC_REG           0x22 // pulse detection source (R)
#define MMA8652FCR1_PULSE_THSX_REG          0x23 // x pulse threshold (R/W)
#define MMA8652FCR1_PULSE_THSY_REG          0x24 // y pulse threshold (R/W)
#define MMA8652FCR1_PULSE_THSZ_REG          0x25 // z pulse threshold (R/W)
#define MMA8652FCR1_PULSE_TMLT_REG          0x26 // time limit for pulse (R/W)
#define MMA8652FCR1_PULSE_LTCY_REG          0x27 // latency time for second pulse (R/W)
#define MMA8652FCR1_PULSE_WIND_REG          0x28 // window time for second pulse (R/W)
#define MMA8652FCR1_ASLP_COUNT_REG          0x29 // counter setting for auto-sleep (R/W)
#define MMA8652FCR1_CTRL_REG1               0x2A // data rates and modes settings (R/W)
#define MMA8652FCR1_CTRL_REG2               0x2B // sleep enable, os modes, rst, st (R/W)
#define MMA8652FCR1_CTRL_REG3               0x2C // wake from sleep, ipol, PP_OD (R/W)
#define MMA8652FCR1_CTRL_REG4               0x2D // Interrupt enable register (R/W)
#define MMA8652FCR1_CTRL_REG5               0x2E // Interrupt pin map (R/W)
#define MMA8652FCR1_OFF_X_REG               0x2F // x-offset adjustment
#define MMA8652FCR1_OFF_Y_REG               0x30 // y-offset adjustment
#define MMA8652FCR1_OFF_Z_REG               0x31 // z-offset adjustment

//define the device id
#define MMA8652FCR1_DEVICE_ID               0x4a

class MMA8652FCR1
{

    public:

        /**
         * @brief MMA8652FCR1 object constructor
         */
        MMA8652FCR1();
        
        /**
         * @brief Initialises the accelerometer and configures registers.
         *
         * @param devID The device ID of the accelerometer.
         * @param intPin1 The wiringPi pin number of the pin connected to interrupt 1.
         * @param intPin2 The wiringPi pin number of the pin connected to interrupt 2.
         * @return Bool that reports if the setup has been successful.
         */
        bool init(int devID, int intPin1, int intPin2);
        
        /**
         * @brief Gets the acceleration value from each of the three axis.
         *
         * @param data Pointer to a accValues_t struct that contains the x, y and z accelerations.
         */
        void getData(accValues_t *data);
        
        //recording of the accelerometer values when static
        accValues_t *staticVals;
        
        /**
         * @brief Records the current accelerometer reading in staticVals.
         *
         */
        void recordStatic();
        
    private:
    
        //2's complement data conversion functions
        double twosComp(uint8_t MSB);
        double twosComp(uint8_t MSB, uint8_t LSB);
    
        //interrupt pin connections
        int m_intPin1;
        int m_intPin2;
        
        
        //devid of the sensor
        int m_devID;
        
        //i2c port
        int fd;

};

#endif