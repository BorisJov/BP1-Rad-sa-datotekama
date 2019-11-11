#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "slogbaketops.h"
#include "keyops.h"
#include "fileops.h"
#include "higherops.h"

const unsigned int CHARACTER_MAX_NUM = 55;

void read_string(int max_character_num, char *retVal)
{
    scanf("\n");
    fgets(retVal,max_character_num,stdin);
    strtok(retVal, "\n");
}

void print_main_menu()
{
    printf(" --------------------------------------------\n");
    printf("|                  MAIN MENU                 |\n");
    printf(" --------------------------------------------\n");
    printf("| Select operation:                          |\n");
    printf("| 1.) Create file                            |\n");
    printf("| 2.) Open existing file                     |\n");
    printf("| 3.) Test key hash function                 |\n");
    printf("| 4.) Exit application                       |\n");
    printf(" --------------------------------------------\n");
}

void choose_file_name_menu(char *filename)
{
    printf(" --------------------------------------------\n");
    printf("| Choose file name:                          |\n");
    printf("|\t");
    read_string(CHARACTER_MAX_NUM, filename);
    printf(" --------------------------------------------\n");
}

void print_file_operations_menu(char* filename)
{
    printf(" --------------------------------------------\n");
    printf("|            FILE OPERATIONS MENU            |\n");
    printf("| %s\n",filename);
    printf(" --------------------------------------------\n");
    printf("| Select operation:                          |\n");
    printf("| 1.) Print file contents                    |\n");
    printf("| 2.) Put slog in file                       |\n");
    printf("| 3.) Find slog in file                      |\n");
    printf("| 4.) Change address value                   |\n");
    printf("| 5.) Delete slog                            |\n");
    printf("| 6.) Close file                             |\n");
    printf(" --------------------------------------------\n");
}

Slog slog_creation_menu()
{
    printf(" --------------------------------------------\n");
    printf("|             SLOG CREATION MENU             |\n");
    printf(" --------------------------------------------\n");

    printf("| Insert key:                                |\n");
    printf("|\t");
    unsigned int key;
    scanf("%u",&key);
    while(!(key >= 0 && key <= pow(10,KEY_MAX_DIGITS)-1))
    {
        printf("| Key max number is 999999, try again:       |\n");
        printf("|\t");
        scanf("%u",&key);
    }

    printf("| Insert pizza type:                         |\n");
    printf("|\t");
    char pizza_type[TYPE_MAX_CHARACTERS];
    read_string(TYPE_MAX_CHARACTERS,pizza_type);

    printf("| Insert date and time (dd-mm-yyyy hh:mm):   |\n");
    printf("|\t");
    char datetime[DATE_MAX_CHARACTERS];
    read_string(DATE_MAX_CHARACTERS,datetime);

    printf("| Insert order address:                      |\n");
    printf("|\t");
    char order_address[ORDER_MAX_CHARACTERS];
    read_string(ORDER_MAX_CHARACTERS, order_address);

    printf("| Insert ammount:                            |\n");
    printf("|\t");
    unsigned int ammount;
    scanf("%u",&ammount);
    while(!(ammount >= 0 && ammount <= AMMOUNT_MAX_VALUE))
    {
        printf("| Ammount must be less than 10, try again:   |\n");
        printf("|\t");
        scanf("%u",&ammount);
    }

    printf(" --------------------------------------------\n");

    return newSlog(key, pizza_type, order_address, datetime, ammount);
}

unsigned int choose_key_menu()
{
    unsigned int retVal;
    printf(" --------------------------------------------\n");
    printf("| Choose slog key:                           |\n");
    printf("|\t");
    scanf("%u",&retVal);
    printf(" --------------------------------------------\n");
    return retVal;
}

void found_not_found(unsigned int key, int position, FILE *active)
{
    printf(" --------------------------------------------\n");
    if(position < 0)
    {
        printf("| Slog with key %u not found         \n",key);
    }
    else
    {
        printf("| Slog with key %u found at ",key);
        if(position < PRIMARY_ZONE_BAKET_NUM)
            printf("%u in PRIMARY ZONE |\n",position);
        else
            printf("%u in SECONDARY ZONE\n",position - PRIMARY_ZONE_BAKET_NUM);
        fseek(active,position*sizeof(Baket),SEEK_SET);
        Baket b = read_baket(active);
        for(int i = 0; i < BAKETING_FACTOR; i++)
        {
            if(b.slog_u_baketu[i].status == ACTIVE)
            {
                if(b.slog_u_baketu[i].key == key)
                {
                    printf("| At position no%d in baket\n",i);
                    printSlog(b.slog_u_baketu[i]);
                }
            }
        }
    }
    printf(" --------------------------------------------\n");
}

void choose_new_address_menu(char *new_address)
{
    printf(" --------------------------------------------\n");
    printf("| Choose new address:                        |\n");
    printf("|\t");
    read_string(CHARACTER_MAX_NUM, new_address);
    printf(" --------------------------------------------\n");
}

void print_change_successful()
{
    printf(" --------------------------------------------\n");
    printf("| Change successfull!                        |\n");
    printf(" --------------------------------------------\n");
}

void print_change_unsuccessfull()
{
    printf(" --------------------------------------------\n");
    printf("| Change unsuccessfull.                      |\n");
    printf(" --------------------------------------------\n");
}

void print_file_not_found()
{
    printf(" --------------------------------------------\n");
    printf("| Unfortunately, file could not be found.    |\n");
    printf(" --------------------------------------------\n");

}

void test_middle_square_method()
{
    printf(" --------------------------------------------\n");
    printf("| Insert key for test:                       |\n");
    printf("|\t");
    unsigned int key;
    scanf("%u",&key);
    while(!(key >= 0 && key <= pow(10,KEY_MAX_DIGITS)-1))
    {
        printf("| Key max number is 999999, try again:       |\n");
        printf("|\t");
        scanf("%u",&key);
    }
    key = middle_square_method(key);
    printf("| Resulting key is %u\n",key);
    printf(" --------------------------------------------\n");
}

int main()
{
    int selected_op = 0;
    char filename[30];
    FILE * active;
    while(selected_op != 4)
    {

        print_main_menu();
        scanf("%d",&selected_op);
        if(selected_op == 1)
        {
            choose_file_name_menu(filename);
            create_empty_file(filename);
        }
        else if (selected_op == 2)
        {
            choose_file_name_menu(filename);
            active = open_existing_file(filename);
            if(active == NULL)
            {
                print_file_not_found();
                continue;
            }
            int sel_op = 0;
            unsigned int sel_key;
            Slog s;
            char new_address[51];
            while(sel_op != 6)
            {
                print_file_operations_menu(filename);
                scanf("%d",&sel_op);
                switch(sel_op)
                {
                case 1:
                    printFile(active);
                    break;
                case 2:
                    s = slog_creation_menu();
                    put_slog_in_file(active,s);
                    break;
                case 3:
                    sel_key = choose_key_menu();
                    found_not_found(sel_key,find_slog_in_file(active,sel_key),active);
                    break;
                case 4:
                    sel_key = choose_key_menu();
                    choose_new_address_menu(new_address);
                    if(change_slog_address_value(active,sel_key,new_address))
                        print_change_successful();
                    else
                        print_change_unsuccessfull();
                    break;
                case 5:
                    sel_key = choose_key_menu();
                    if(soft_delete_slog(active,sel_key))
                        print_change_successful();
                    else
                        print_change_unsuccessfull();
                    break;

                default:
                    break;
                }
            }
            fclose(active);
        }
        else if(selected_op == 3)
        {
            test_middle_square_method();
        }
    }
    return 0;
}
