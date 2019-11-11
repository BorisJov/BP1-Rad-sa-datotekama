#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

//p = po zadatku 6
const short int PRIMARY_ZONE_BAKET_NUM = 7;
const short int BAKETING_FACTOR = 3;

const short int KEY_MAX_DIGITS = 6;
const short int TYPE_MAX_CHARACTERS = 30;
const short int DATE_MAX_CHARACTERS = 17;
const short int ORDER_MAX_CHARACTERS = 50;
const short int AMMOUNT_MAX_VALUE = 10;


enum Status { ACTIVE = 1, EMPTY = 0, DELETED = 2 };

typedef struct Slog
{
    unsigned int key;
    char pizza_type[30];
    //format "dd-mm-yyyy hh-mm"
    char datetime[17];
    char order_address[50];
    short unsigned int ammount;
    enum Status status;
} Slog;

#define EMPTY_SLOG(X) Slog X = { .key = 0, .pizza_type = NULL, .datetime = NULL, .order_address = NULL, .ammount = 0, .status = 0 }

typedef struct Baket
{
    Slog slog_u_baketu[3];
} Baket;

#endif // DEFS_H_INCLUDED
