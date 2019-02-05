#ifndef SENSORTYPES_H
#define SENSORTYPES_H


/* @brief: parking sensor pins */
typedef struct sensorPins_t {
    int sel[3];
    int echo_pin;
    int trigger_pin;
} sensorPins_t;

#endif //SENSORTYPES_H