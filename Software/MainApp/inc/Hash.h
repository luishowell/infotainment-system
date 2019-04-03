/**
 * @file Hash.h
 * @author Jamie
 * @brief Hash functions for OBD2 pid codes.
 * @version 0.1
 * @date 2019-04-03
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <Qt>
#include <string>
#include <vector>
#include "types.h"
#include <QGroupBox>
#include <QMetaType>

/**
 * @brief Hash functions to convert codes, descriptive names and enums for OBD2 pid codes.
 * 
 */
namespace Hash
{
    /**
     * @brief Converts a parameter name from a string to an enum.
     * 
     * @param name A descriptive name of a parameter.
     * @return diagParams_t The converted parameter as an enum.
     */
    diagParams_t HashParameterName(QString name);

    /**
     * @brief Converts a pid code from a string to an enum.
     * 
     * @param pidString A pid code as a string.
     * @return diagParams_t The converted parameter as an enum.
     */
    diagParams_t HashPID(std::string pidString);

    /**
     * @brief Converts a pid code to a parameter name
     * 
     * @param pidString A pid code as a string.
     * @return std::string The converted descriptive parameter name as a string.
     */
    std::string  PID2Name(QString pidString);
}