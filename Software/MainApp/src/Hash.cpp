/**
 * @file Hash.cpp
 * @author Jamie Brown
 * @brief Contains implementations of hash functions.
 * @version 0.1
 * @date 2019-04-03
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "Hash.h"
#include "QtCore"

diagParams_t Hash::HashParameterName(QString name)
{
   if (name == "RPM")                       return RPM;
   if (name == "Speed")                     return SPEED;
   if (name == "Intake Air Temperature")    return AIR_TEMP;
   if (name == "Throttle Position")         return THROTTLE;
   if (name == "Engine Runtime")            return ENGINE_RUNTIME;
   if (name == "Engine Load")               return ENGINE_LOAD;
   if (name == "Current Gear")              return GEAR;
   if (name == "Fuel Pressure")             return FUEL_PRESSURE;
}

diagParams_t Hash::HashPID(std::string pidString)
{
   if (pidString == "0C") return RPM;
   if (pidString == "0D") return SPEED;
   if (pidString == "0F") return AIR_TEMP;
   if (pidString == "11") return THROTTLE;
   if (pidString == "1F") return ENGINE_RUNTIME;
   if (pidString == "04") return ENGINE_LOAD;
   if (pidString == "A4") return GEAR;
   if (pidString == "0A") return FUEL_PRESSURE;
}

std::string Hash::PID2Name(QString pidString)
{
   if (pidString == "010C") return "RPM"; 
   if (pidString == "010D") return "Speed";
   if (pidString == "010F") return "Air-Temperature";
   if (pidString == "0111") return "Throttle";
   if (pidString == "011F") return "Engine-Runtime";
   if (pidString == "0104") return "Engine-Load";
   if (pidString == "01A4") return "Gear";
   if (pidString == "010A") return "Fuel-Pressure";
}


