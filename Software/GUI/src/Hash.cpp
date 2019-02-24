#include "Hash.h"

/**
 * @brief Converts a parameter name from a string to an enum
 * 
 * @param name 
 * @return diagParams_t 
 */
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

/**
 * @brief Converts a pid code from a string to an enum
 * 
 * @param inString 
 * @return diagParams_t 
 */
diagParams_t Hash::HashPID(QString pidString)
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
