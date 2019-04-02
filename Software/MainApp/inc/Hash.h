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
    /**
     * @brief 
     * 
     * @param name 
     * @return diagParams_t 
     */
    diagParams_t HashParameterName(QString name);

    /**
     * @brief 
     * 
     * @param pidString 
     * @return diagParams_t 
     */
    diagParams_t HashPID(std::string pidString);

    /**
     * @brief 
     * 
     * @param pidString 
     * @return std::string 
     */
    std::string  PID2Name(QString pidString);
}