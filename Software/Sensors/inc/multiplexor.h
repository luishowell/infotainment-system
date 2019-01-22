#ifndef MULTIPLEXOR_H
#define MULTIPLEXOR_H


#include <stdio.h>
#include <wiringPi.h>

class multiplexor
{

    public:

        //constructor
        multiplexor();

        //initialise the mux
        void init(int sel_0, int sel_1, int sel_2);

        //set the mux
        bool set_mux(unsigned int select_val);

    private:

        //pin values
        int m_sel_0;
        int m_sel_1;
        int m_sel_2;


};



#endif