#include "config.h"
#include "multiplexor.h"

//constructor
multiplexor::multiplexor(){}

/*
    Function used to setup the pins on the pi that connect to the mux
*/
bool multiplexor::init(int sel_0, int sel_1, int sel_2)
{
#ifdef RPI
    //set the pins as outputs and save values
     this->m_sel_0 = sel_0;
     pinMode(sel_0, OUTPUT);
     this->m_sel_1 = sel_1;
     pinMode(sel_1, OUTPUT);
     this->m_sel_2 = sel_2;
     pinMode(sel_2, OUTPUT);

     //set all pins to 0 as default
     digitalWrite(sel_0, LOW);
     digitalWrite(sel_1, LOW);
     digitalWrite(sel_2, LOW);

     return true;
#endif

    return false;

}

/*
    Function used to set the mux
*/
bool multiplexor::set_mux(unsigned int select_val)
{
#ifdef RPI

    //check the value is valid, i.e. 0-7
    if(select_val > 7)
    {
        //return error response
        return false;
    }
    //set the pins
    digitalWrite(m_sel_0,(select_val & 1));
    digitalWrite(m_sel_1,(select_val & 2) >> 1);
    digitalWrite(m_sel_2,(select_val & 4) >> 2);

    return true;
#endif
    return false;

}