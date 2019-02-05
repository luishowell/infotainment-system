#ifndef SENSORTYPES_H
#define SENSORTYPES_H


/* @brief: parking sensor pins */
typedef struct sensorPins_t {
    int sel[3];
    int echoPin;
    int triggerPin;
    int en;
} sensorPins_t;

#endif //SENSORTYPES_H