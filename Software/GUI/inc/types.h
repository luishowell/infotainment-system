#ifndef TYPES_H
#define TYPES_H


typedef enum{
    MAIN_MENU,
    DIAGNOSTICS,
    ERROR_CODES,
    MEDIA,
    PARKING
} state_t;

typedef struct diagMsg {
    int speed;
    int rpm;
    int fuel;
} diagMsg_t;

#endif //TYPES_H