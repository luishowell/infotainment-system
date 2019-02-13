#ifndef TYPES_H
#define TYPES_H

#include <QGroupBox>


/* @brief: GUI view states */
typedef enum{
    MAIN_MENU,
    DIAGNOSTICS,
    ERROR_CODES,
    MEDIA,
    PARKING
} state_t;

/* @brief: diagnostics messages */
typedef struct diagMsg {
    bool connectionFault;
    int channelA;
    int channelB;
    std::string requestA;
    std::string requestB;
} diagMsg_t;

/* @brief: parameters that can be requested from the OBD2 thread */
typedef enum {
    SPEED,
    RPM,
    AIR_TEMP, 
    THROTTLE
} diagParams_t;

typedef enum {
    CHANNEL_A,
    CHANNEL_B
} obd2Channel_t;

/* @brief: parking sensor signals */
typedef struct sensorDist {
    bool connectionFault;
    double rearLeft;
    double rearRight;
    double rearCentre;
    double frontLeft;
    double frontRight;
    double frontCentre;
} sensorDist_t;




#endif //TYPES_H