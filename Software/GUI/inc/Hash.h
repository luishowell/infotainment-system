#include <Qt>
#include <string>
#include <vector>
#include "types.h"

/**
 * @brief 
 * 
 */
namespace Hash
{
    diagParams_t HashParameterName(QString name);
    diagParams_t HashPID(std::string pidString);
    std::string  PID2Name(QString pidString);
}