#ifndef FILEOPS_H_INCLUDED
#define FILEOPS_H_INCLUDED

void write_baket(FILE *active, Baket bak)
{
    fwrite(&bak,sizeof(Baket),1,active);
}

Baket read_baket(FILE *active)
{
    Baket retVal;
    fread(&retVal,sizeof(Baket),1,active);
    return retVal;
}

//creates and closes
void create_empty_file(char* file_name)
{
    FILE *f = fopen(file_name,"wb");
    Baket empty_baket = create_empty_baket();
    // primarna zona + prvi clan zone prekoracenja
    for(int i = 0; i < PRIMARY_ZONE_BAKET_NUM + 1; i++)
    {
        write_baket(f,empty_baket);
    }
    fclose(f);
}

FILE * open_existing_file(char* file_name)
{
    FILE *retVal = fopen(file_name,"rb+");
    return retVal;
}

void printFile(FILE *active)
{
    fseek(active,0,SEEK_SET);
    printf("-------------------------------------\n");
    printf("PRIMARY ZONE:\n");
    printf("-------------------------------------\n");
    for(int i = 0; i < PRIMARY_ZONE_BAKET_NUM; i++)
    {
        printf("-------------------------------------\n");
        printf("Baket %d:\n", i);
        printBaket(read_baket(active));
    }
    printf("-------------------------------------\n");
    printf("SECONDARY ZONE:\n");
    printf("-------------------------------------\n");
    Baket b = read_baket(active);
    int pos = 0;
    if(is_baket_empty(b))
    {
        printf("*EMPTY*\n");
        printf("-------------------------------------\n");
    }
    else
    {
        while(!is_baket_empty(b))
        {
            printf("Baket %d:\n", pos);
            printBaket(b);
            if(free_space_in_baket(b) == 0)
            {
                b = read_baket(active);
                pos++;
            }
            else
                return;
        }
    }
}

void position_at_start_of_secondary_zone(FILE *f)
{
    fseek(f,PRIMARY_ZONE_BAKET_NUM*sizeof(Baket),SEEK_SET);
}

#endif // FILEOPS_H_INCLUDED
