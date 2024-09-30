#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

char mas[5] = { 'г', 'а', 'в', 'Б', 'ё'};

int compare(const void* i, const void* j) {
    return *(char*)i - *(char*)j;
}


int main() {  
    setlocale(0, "rus");
    qsort(mas, 5, sizeof(char), compare);

    for (int i = 0; i < 5; i++) {
        printf("%c", mas[i]);
    }
   
    return 0;


}