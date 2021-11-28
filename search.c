#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int DFS(int* checTop, int TopNumber, char sign, int* BitField,char* name);

int main(void*)
{
    FILE* file;

    int checkTop=0;
    char sign;
    int wasSearch = 0;

    int column = 0;
    int row = 0;
    int MaxTop = 1;

    char *name;
    name = (char*)malloc(sizeof(char)*8);
    int* BitField;

    int* tmpint;
    char *tmp;
    
    file = fopen("C:\\Users\\Георгий\\Desktop\\table.txt", "r");

    fgetc(file);

    while ((sign = fgetc(file)) != '\n') {
        tmp = (char*)realloc(name, sizeof(char) * 8 * (MaxTop+1));
        name = tmp;
        if(name)
        name[MaxTop - 1] = sign;
        MaxTop++;
    }
    fgetc(file);

    tmpint = (int*)calloc(MaxTop, sizeof(int));
    BitField = tmpint;

    while ((sign = fgetc(file)) != EOF) {
        if (sign != '\n'&& (sign == '1'|| sign == '0')) {
            if(BitField)
            BitField[row] = BitField[row] | ((sign-'0') << column);
            column++;
        }
        else if(sign != '\n') {
            column = 0;
            row++;
        }
    }
    fclose(file);

    printf("input serch top\n");
    sign = getchar();
    for (int i = 0;i < (sizeof(int)*8);i++) {
        if ((checkTop & (1 << i)) == 0) 
            if (DFS(&checkTop, i, sign, BitField, name)) {
                printf("Top was searched");
                wasSearch = 1;
                break;
            }
    }   
    if(!wasSearch)
        printf("Top wasn\'t searched");
    
}
int DFS(int *checkTop,int TopNumber,char sign,int* BitField,char* name) {
    if (name[TopNumber] == sign)
        return 1;
    else {
        *checkTop = *checkTop | (1 << TopNumber);
        for (int i = 0;i < (sizeof(int)*8);i++) {
            if (((BitField[TopNumber] & (1 << i)) > 0) && ((*checkTop & (1 << i)) == 0)) 
                if (DFS(checkTop, i, sign, BitField, name) == 1)
                    return 1;
        }
        return 0;
    }

}
