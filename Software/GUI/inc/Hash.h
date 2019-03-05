#include <Qt>
#include <string>
#include "types.h"

/**
 * @brief 
 * 
 */
namespace Hash
{
    diagParams_t HashParameterName(QString name);
    diagParams_t HashPID(QString pidString);
    std::string  PID2Name(QString pidString);
}