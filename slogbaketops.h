#ifndef SLOGBAKETOPS_H_INCLUDED
#define SLOGBAKETOPS_H_INCLUDED

#include <string.h>

int is_slog_empty(Slog s)
{
    return s.status == EMPTY;
}

int is_baket_empty(Baket b)
{
    if(is_slog_empty(b.slog_u_baketu[0]) && is_slog_empty(b.slog_u_baketu[1]) && is_slog_empty(b.slog_u_baketu[1]))
        return 1;
    else
        return 0;
}

int free_space_in_baket(Baket b)
{
    return (is_slog_empty(b.slog_u_baketu[0]) + is_slog_empty(b.slog_u_baketu[1]) + is_slog_empty(b.slog_u_baketu[2]));
}

void printSlog(const Slog s)
{
    if(is_slog_empty(s))
        printf("*EMPTY*\n");
    else
    {
        printf("Slog %u:\n", s.key);
        printf("\tTip pice:\t%s\n", s.pizza_type);
        printf("\tDatum i vreme:\t%s\n", s.datetime);
        printf("\tAdresa:\t\t%s\n", s.order_address);
        printf("\tKolicina:\t%u\n", s.ammount);
        printf("\tStatus:\t\t");
        if(s.status == ACTIVE)
            printf("ACTIVE\n");
        else if(s.status == DELETED)
            printf("DELETED\n");
        else if(s.status == EMPTY)
            printf("EMPTY\n");
    }
}

void printBaket(Baket b)
{
    printf("-------------------------------------\n");
    for(int i = 0; i < BAKETING_FACTOR; i++)
        printSlog(b.slog_u_baketu[i]);
    printf("-------------------------------------\n");
}

Slog newSlog(const unsigned int key, const char* type, const char* address, const char* date, const short int ammount)
{
    Slog retVal;
    retVal.key = key;
    strcpy(retVal.pizza_type,type);
    strcpy(retVal.datetime,date);
    strcpy(retVal.order_address,address);
    retVal.ammount = ammount;
    retVal.status = ACTIVE;
    return retVal;
}

Baket create_empty_baket()
{
    EMPTY_SLOG(empty_slog);
    Baket empty_baket = {
        .slog_u_baketu[0] = empty_slog,
        .slog_u_baketu[1] = empty_slog,
        .slog_u_baketu[2] = empty_slog
    };
    return empty_baket;
}

#endif // SLOGBAKETOPS_H_INCLUDED
