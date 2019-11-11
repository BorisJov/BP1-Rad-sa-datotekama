#ifndef HIGHEROPS_H_INCLUDED
#define HIGHEROPS_H_INCLUDED

//returns -1 if not found, else relative address of baket to file beginning
int find_slog_in_file(FILE *f, unsigned int key)
{
    unsigned int prim_key = middle_square_method(key);
    //try to find in primary zone
    fseek(f, prim_key * sizeof(Baket), SEEK_SET);
    Baket b = read_baket(f);
    for(int i = 0; i < BAKETING_FACTOR; i++)
    {
        if(b.slog_u_baketu[i].status == ACTIVE)
        {
            if(b.slog_u_baketu[i].key == key)
                return prim_key;
        }
    }

    //try to find in secondary zone
    position_at_start_of_secondary_zone(f);
    int position = PRIMARY_ZONE_BAKET_NUM;
    b = read_baket(f);
    while(!is_baket_empty(b))
    {
        for(int i = 0; i < BAKETING_FACTOR; i++)
        {
            if(b.slog_u_baketu[i].status == ACTIVE)
            {
                if(b.slog_u_baketu[i].key == key)
                    return position;
            }
            if(b.slog_u_baketu[i].status == EMPTY)
                return -1;
        }

        b = read_baket(f);
        position++;
    }

    //fail
    return -1;
}

void put_slog_in_file(FILE *f, Slog s)
{
    if(find_slog_in_file(f,s.key) >= 0)
        printf("Slog already in file\n");
    else
    {
        unsigned int prim_key = middle_square_method(s.key);
        fseek(f,prim_key*sizeof(Baket),SEEK_SET);
        Baket b = read_baket(f);
        for(int i = 0; i < BAKETING_FACTOR; i++)
        {
            if(b.slog_u_baketu[i].status == EMPTY)
            {
                b.slog_u_baketu[i] = s;
                fseek(f, -sizeof(Baket), SEEK_CUR);
                write_baket(f,b);
                return;
            }
        }

        position_at_start_of_secondary_zone(f);
        while(free_space_in_baket(b) == 0)
        {
            b = read_baket(f);
        }
        for(int i = 0; i < BAKETING_FACTOR; i++)
        {
            if(b.slog_u_baketu[i].status == EMPTY)
            {
                b.slog_u_baketu[i] = s;
                fseek(f, -sizeof(Baket), SEEK_CUR);
                write_baket(f,b);
                //if baket now full
                if(i == BAKETING_FACTOR - 1)
                {
                    Baket empty_backet = create_empty_baket();
                    write_baket(f,empty_backet);
                }
                return;
            }
        }
    }
}

//returns true/false value
int change_slog_address_value(FILE *f, unsigned int key, char *new_value)
{
    int position = find_slog_in_file(f,key);
    if(position < 0)
        return 0;
    else
    {
        fseek(f,position*sizeof(Baket),SEEK_SET);
        Baket b = read_baket(f);
        int i;
        for(i = 0; i < BAKETING_FACTOR; i++)
        {
            if(b.slog_u_baketu[i].status == ACTIVE)
            {
                if(b.slog_u_baketu[i].key == key)
                {
                    strcpy(b.slog_u_baketu[i].order_address, new_value);
                    fseek(f,-(sizeof(Baket)),SEEK_CUR);
                    write_baket(f,b);
                    return 1;
                }
            }
        }
    }
    return 0;
}
//=logicko brisanje, returns true/false for success/failure
int soft_delete_slog(FILE *f, unsigned int key)
{
    int position = find_slog_in_file(f,key);
    if(position < 0)
        return 0;
    else
    {
        fseek(f,position*sizeof(Baket),SEEK_SET);
        Baket b = read_baket(f);
        int i;
        for(i = 0; i < BAKETING_FACTOR; i++)
        {
            if(b.slog_u_baketu[i].status == ACTIVE)
            {
                if(b.slog_u_baketu[i].key == key)
                {
                    b.slog_u_baketu[i].status = DELETED;
                    fseek(f,-(sizeof(Baket)),SEEK_CUR);
                    write_baket(f,b);
                    return 1;
                }
            }
        }
    }
    return 0;
}
#endif // HIGHEROPS_H_INCLUDED
