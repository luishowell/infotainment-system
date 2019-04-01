#include "Hash.h"
#include "QtCore"

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

/**
 * @brief Converts a pid code to a parameter name
 * 
 * @param pidString 
 * @return std::string
 */
std::string Hash::PID2Name(QString pidString)
{
   if (pidString == "010C")
   {
      //qDebug() << "rniwniwniwne"; 
      return "RPM";
   } 
   if (pidString == "010D") return "Speed";
   if (pidString == "010F") return "Air-Temperature";
   if (pidString == "0111") return "Throttle";
   if (pidString == "011F") return "Engine-Runtime";
   if (pidString == "0104") return "Engine-Load";
   if (pidString == "01A4") return "Gear";
   if (pidString == "010A") return "Fuel-Pressure";
}


