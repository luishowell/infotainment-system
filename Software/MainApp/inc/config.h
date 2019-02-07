#ifndef CONFIG_H
#define CONFIG_H

#include <Qt>
#include <QSize>

#define DEBUG 
#define GUI_TEST 1 //uncomment for testing the gui without the OBD2 connector 

/* size of raspberry pi touchscreen */
#define WIDGET_SIZE_X 800
#define WIDGET_SIZE_Y 480
const QSize widgetSize = QSize(WIDGET_SIZE_X, WIDGET_SIZE_Y);

/* OBD2 config */
#define DIAG_RATE 500 //ms
#define LOGGING_RATE 1500 //ms
#define FUEL_CAPACITY 65 //litres







#endif // CONFIG_H
