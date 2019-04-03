/**
 * @file config.h
 * @author Jamie Brown
 * @brief This file used for global configuration of the app. Resizing of widgets etc.
 * @version 0.1
 * @date 2019-04-03
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <Qt>
#include <QSize>

#define DEBUG 

/* comment the following line for non raspberry-pi builds */
//#define RPI 1

/* size of raspberry pi touchscreen */
#define WIDGET_SIZE_X 800
#define WIDGET_SIZE_Y 480
const QSize widgetSize = QSize(WIDGET_SIZE_X, WIDGET_SIZE_Y);

/* OBD2 config */
#define DIAG_RATE 420 //ms
#define LOGGING_RATE 1500 //ms
#define FUEL_CAPACITY 65 //litres







#endif // CONFIG_H
