#ifndef CONFIG_H
#define CONFIG_H

#include <Qt>

#define DEBUG 

/* size of raspberry pi touchscreen */
#define WIDGET_SIZE_X 800
#define WIDGET_SIZE_Y 480
const QSize widgetSize = QSize(WIDGET_SIZE_X, WIDGET_SIZE_Y);

/* CAN config */
#define DIAG_RATE 100 //ms
#define FUEL_CAPACITY 65 //litres







#endif // CONFIG_H
