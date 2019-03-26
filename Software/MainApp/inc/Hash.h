#include <Qt>
#include <string>
#include <vector>
#include "types.h"
#include <QGroupBox>
#include <QMetaType>

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