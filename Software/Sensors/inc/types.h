#ifndef TYPES_H
#define TYPES_H


/* @brief: parking sensor pins */
typedef struct sensorPins_t {
    int sel[3];
    int echo_pin;
    int trigger_pin;
} sensorPins_t;

#endif //TYPES_H