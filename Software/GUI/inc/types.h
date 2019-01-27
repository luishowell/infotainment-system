#ifndef TYPES_H
#define TYPES_H

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
    int speed;
    int rpm;
    int fuel;
    int intakeAirTemp;
} diagMsg_t;

/* @brief: parking sensor signals */
typedef struct sensorDist {
    bool connectionFault;
    int32_t rearLeft;
    int32_t rearRight;
    int32_t rearCentre;
    int32_t frontLeft;
    int32_t frontRight;
    int32_t frontCentre;
} sensorDist_t;

#endif //TYPES_H