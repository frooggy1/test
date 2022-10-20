#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int count = 0;
int indexes[200];//radky s jmenem
int indexes_numbers_size = 0;
int indexes_numbers[200];//radky s cislem

void final_check_and_out(char names[200][230], int change_behaviour)//
{
    if(change_behaviour==0) {
        int tmp;
        bool noSwap;
        for (int i = count - 1; i >= 0; --i) {
            noSwap = 1;
            for (int j = 0; j < i; ++j) {
                if (indexes[j] > indexes[j + 1]) {
                    tmp = indexes[j];
                    indexes[j] = indexes[j + 1];
                    indexes[j + 1] = tmp;
                    noSwap = 0;
                }
            }
            if (noSwap == 1) {
                break;
            }
        }
    }
    if(change_behaviour==1 || change_behaviour==0) {
        for (int i = 0; i < count; i++) {
            for (int j = i + 1; j < count; j++) {
                if (indexes[i] == indexes[j]) {
                    for (int k = j; k < count - 1; k++) {
                        indexes[k] = indexes[k + 1];
                    }
                    count--;
                    j--;
                }
            }
        }
    }
    if(change_behaviour==1 || change_behaviour==0) {
        if (indexes[0] == 0) {
            printf("You don't have such contact in your list\n");
        } else {
            for (int i = 0; i < count; ++i) {
                printf("Name: %s, Number: %s \n", names[indexes[i]-1], names[indexes[i]]);
            }
        }
    }else if(change_behaviour == 2)
    {
        if (indexes_numbers[0] == 0) {
            printf("You don't have such contact in your list\n");
        }else {
            for (int i = 0; i < count; ++i) {
                for (int j = 0; j < indexes_numbers_size; ++j) {
                    if(indexes[i] == indexes_numbers[j]-1)
                    {
                        indexes_numbers[j] = 0;
                    }
                }
            }
            for (int k = 0; k < indexes_numbers_size; ++k) {
                if(indexes_numbers[k]!=0)
                {
                    printf("Name: %s, Number: %s\n", names[indexes_numbers[k]-2], names[indexes_numbers[k]-1]);
                }
            }
        }
    }
}

int check(char final[], char names[200][230], int size, int change_behaviour, int rows){ //funkce hleda slabek v names[][]
                                                                                        //change_behaviour(0 - hledame jmeno po slabiku, 1 - hledame jmeno po cislu, 2 - hledame jmeno bez poradku v slabku)
    if(change_behaviour == 2)//udelame count prazdne,
    {                        //protoze po volani funkce pri
        count = 0;           //change_behaviour == 1 neni prazdny
    }                        //

    int radky = 0;//pocet radku
    int upperSwap = 0;//promenna jestli pismeno bylo velke
    while(radky<rows){
        int pismeno = 0;
        int internal = 0;
        if(isupper(names[radky][pismeno])) //oznacime jestli pismeno bylo velke, a
        {                                  //udelame ji malou
            names[radky][pismeno]+= 32;    //
            upperSwap = 1;                 //
        }
        end_of_line:
        while(pismeno < strlen(names[radky])) //cyklusy pro kontrolu
        {                                       //vsichni pismen
            while(internal<size)                //
            {
                if(final[internal] != names[radky][pismeno])       //kontrola jestli pismeno je stejne jako v final
                {                                                  //
                    if(upperSwap == 1)
                    {
                        names[radky][pismeno] -= 32;
                        upperSwap = 0;
                    }
                    pismeno++;
                    if(pismeno > strlen(names[radky]))
                    {
                        goto end_of_line;
                    }
                }
                else if(final[internal] == names[radky][pismeno])  //kontrola jestli pismeno je stejne jako v final
                {                                                  //
                    if(upperSwap == 1)
                    {
                        names[radky][pismeno] -= 32;
                        upperSwap = 0;
                    }
                    internal++;
                    pismeno++;
                    if(final[internal] != names[radky][pismeno] && internal < size && (change_behaviour == 0 || change_behaviour == 2 ))//jestli nemame poraadek
                    {                                                                                                                   //jako v final, zaciname hledat opet
                       internal = 0;                                                                                                    //
                    }
                }
            }

            if(change_behaviour == 0) {                             //zapiseme radek s jmenen v indexes
                indexes[count] = radky+1;                           //
                count++;
                for (int j = pismeno; j > pismeno - size; --j) {
                    if (islower(names[radky][j-1])) {
                        names[radky][j - 1] -= 32;
                    }
                }
            }else if (change_behaviour == 1)//zapiseme radek bez poradku v indexes
            {
                indexes[count] = radky+1;
                count++;
            }else if(change_behaviour == 2)//zapiseme radek s cislem v indexes_numbers
            {
                indexes_numbers[count] = radky+1;
                indexes_numbers_size++;
                count++;
            }
            pismeno += strlen(names[radky]); //zavrime cyklus
        }
        radky++;//zmenime radek
    }
}

char syllables(char letters[10][100], int num, char numbers_from_terminal[], char final[], int size, char names[200][230], int change_behaviour, int rows) //Funkce udela slabky, a odesle v funkce check
{                                                                                                                                                                   //letters - pole (cisla --> písmena), num - cislo rekurze, numbers_from_terminal - our numbers,
    if(num == size)                                                                                                                                                 //final - pole pro slabiky, size - kolik mame cisel argv[1], names - names s souboru
    {                                                                                                                                                               //change_behaviour(0 - hledame jmeno po slabiku, 1 - hledame jmeno po cislu, 2 - hledame jmeno bez poradku v slabku), rows - radky
    check(final, names, strlen(final), change_behaviour, rows);
    }
    for (int i = 0; i < strlen(letters[numbers_from_terminal[num] - '0']); i++)                                         //cyklus, ktery udela vsechni mozni slabky
    {                                                                                                                     //'4','2','3' --> 'gad', 'gae', 'gaf', 'gbd', ...
        final[num] = letters[numbers_from_terminal[num] - '0'][i];                                                        //
        syllables(letters, num + 1, numbers_from_terminal, final, size, names, change_behaviour, rows);      //
    }                                                                                                                     //
}

int main(int argc, char *argv[])
{
    char names[201][230];                           //Oznamime pole,
    int count_of_rows = 0;                                      //ktere budeme pouzivat pro jmena
    int rows=0;


    while(fgets(names[count_of_rows],230, stdin)){  //Cteme textovy soubor, a
        names[count_of_rows][strlen(names[count_of_rows])-1]='\0';       //zapiseme do pole names
        count_of_rows++;
        rows++;
    }

    char letters[10][100] = {{' '},
                           {' '},
                           { 'a', 'b', 'c'},
                           { 'd', 'e', 'f'},
                           { 'g', 'h', 'i'},
                           { 'j', 'k', 'l'},
                           { 'm', 'n', 'o'},
                           { 'p', 'q', 'r', 's'},
                           { 't', 'u', 'v'},
                           { 'w', 'x', 'y', 'z'}};

    int size = strlen(argv[1]);     //kolik mame cisel argv[1]
    char final[size+1];               //pole pro slabiky
    final[size] = '\0';
    int counter_for_array=0;
    char numbers_from_terminal[size];

    while(*argv[1] != '\0')                                     //nacteme cisla z terminalu
    {                                                           //
        numbers_from_terminal[counter_for_array] = *argv[1];
        counter_for_array++;
        argv[1]++;
    }
    numbers_from_terminal[counter_for_array] = '\0';

    printf("\nby Names with order\n\n");
    syllables(letters, 0, numbers_from_terminal, final, size, names, 0, rows);
    final_check_and_out(names, 0);
    printf("\nby Numbers with order\n\n");
    check(numbers_from_terminal, names,size,2, rows);
    final_check_and_out(names, 2);
    printf("\nWITHOUT ORDER\n\n");
    syllables(letters, 0, numbers_from_terminal, final, size, names, 1, rows);
    final_check_and_out(names, 1);
    return 0;
}