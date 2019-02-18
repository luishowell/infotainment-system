/**
 * @file multiplexor.h
 * @author Joe Walker
 * @brief The class multiplexor provides methods for controlling the operation of a multiplexor from the raspberry pi.
 * @version 0.1
 * @date 2019-02-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef MULTIPLEXOR_H
#define MULTIPLEXOR_H


#include <stdio.h>
#include <wiringPi.h>

class multiplexor
{

    public:

        /**
         * @brief multiplexor object constructor
         * 
         */
        multiplexor();

        /**
         * @brief initiliase the multiplexor
         * 
         * @param sel_0 The wiringPi pin number that is connected to pin sel[0] on the multiplexor
         * @param sel_1 The wiringPi pin number that is connected to pin sel[1] on the multiplexor
         * @param sel_2 The wiringPi pin number that is connected to pin sel[2] on the multiplexor
         */
        void init(int sel_0, int sel_1, int sel_2);

        /**
         * @brief multiplexor object constructor
         * 
         * @param select_val Value for the multiplexor to be set to. Valid values are 0-7.
         * @return bool Flag to report if the multiplexor has been set correctly.
         * init() must have been run at least once
         */
        bool set_mux(unsigned int select_val);

    private:

        //pin values
        int m_sel_0;
        int m_sel_1;
        int m_sel_2;


};



#endif