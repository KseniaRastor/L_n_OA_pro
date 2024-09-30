#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>


void shell(int* items, int count){          //алгоритм сортировки Шелла
    int i, j, gap, k;
    int x, a[5];

    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;
    
    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}


void qs(int* items, int left, int right){   //быстрая сортировка
    int i, j;
    int x, y;

    i = left; j = right;

    /* выбор компаранда */
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

int compare(const void* i, const void* j){
    return *(int*)i - *(int*)j;
}

int N;                              //величина массива
float TSh1, TSh2, TSh3, TSh4;       //для сортировки Шелла
float TQS1, TQS2, TQS3, TQS4;       //для быстрой сотировки
float TQSort1, TQSort2, TQSort3, TQSort4;   //для стандартной функции сортировки
//Индексы:
//1 - случайная последовательность чисел
//2 - возрастающая последовательность чисел
//3 - убывающая последовательность чисел
//4 - одна половина - возрастающая последовательность чисел, а вторая – убывающая
FILE* Shell1, *Shell2, *Shell3, *Shell4;        //переменные, организующие запись данных в файл

int main() {
    setlocale(0, "rus");
    printf("Введите величину массива -> ");
    scanf("%d", &N);
    int* mas = (int*)malloc(N * sizeof(int));           //массив для сортировки Шелла
    int* mas_save_q = (int*)malloc(N * sizeof(int));    //массив для быстрой сортировки
    int* mas_save_qsort = (int*)malloc(N * sizeof(int));    //массив для стандартной функции qsort
    
    Shell1 = fopen("ShellRand.txt", "w");           //открытие файла .txt для записи                            
    fprintf(Shell1, "До сортировки\n");


    srand(time(NULL));                              //заполнение массивов
    for (int i = 0; i < N; i++) {                   //mas, mas_save_q, mas_save_qsort
        mas[i] = rand() % 100 - 20;                 //одинаковыми случайными числами
        mas_save_q[i] = mas[i];
        mas_save_qsort[i] = mas[i];
        fprintf(Shell1, " %d ", mas[i]);            //вывод данных в файл до сортировки
    }

    clock_t start = clock();                        //начало отсчета времени
    shell(mas, N);                                  //сортировка Шелла
    clock_t end = clock();                          //завершение отсчета времени
    TSh1 = ((double)(end - start) / CLOCKS_PER_SEC);    //подсчет времени сортировки Шелла

    start = clock();
    qs(mas_save_q, 0, N-1);                         //быстрая сортировка
    end = clock();
    TQS1 = ((double)(end - start) / CLOCKS_PER_SEC);    //подсчет времени быстрой сортировки

    start = clock();
    qsort(mas_save_qsort, N, sizeof(int), compare);     //стандартная функция сортировки
    end = clock();
    TQSort1 = ((double)(end - start) / CLOCKS_PER_SEC); //подсчет времени стандартной функции сортировки
    
    fprintf(Shell1, "\n\n\nПосле сортировки\n");        //вывод в файл результата сортировки
    for (int i = 0; i < N; i++) {
        fprintf(Shell1, " %d ", mas[i]);
    }
    fclose(Shell1);


    Shell2 = fopen("ShellUp.txt", "w");                //открытие файла .txt для записи       
    fprintf(Shell2, "До сортировки\n");

    for (int i = 0; i < N; i++) {                      //создание возрастающей последовательности чисел, запись в mas
        mas[i] = i;                                    //и ее запись в файл
        fprintf(Shell2, " %d ", mas[i]);    
    }

    start = clock();
    shell(mas, N);                                    //сортировка Шелла
    end = clock();
    TSh2 = ((double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    qs(mas, 0, N - 1);                               //быстрая сортировка
    end = clock();
    TQS2 = ((double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    qsort(mas, N, sizeof(int), compare);            //стандартная функция сортировки
    end = clock();
    TQSort2 = ((double)(end - start) / CLOCKS_PER_SEC);

    fprintf(Shell2, "\n\n\nПосле сортировки\n");     //вывод в файл результата сортировки
    for (int i = 0; i < N; i++) {
        fprintf(Shell2, " %d ", mas[i]);
    }
    fclose(Shell2);


    Shell3 = fopen("ShellDown.txt", "w");            //открытие файла .txt для записи                            
    fprintf(Shell3, "До сортировки\n");

    for (int i = N; i >= 0; i--) {                  //создание убывающей последовательности чисел
        mas[i] = i;                                 //и ее запись в массивы mas, mas_save_q, mas_save_qsort
        mas_save_q[i] = mas[i];
        mas_save_qsort[i] = mas[i];
        fprintf(Shell3, " %d ", mas[i]);
    }

    start = clock();
    shell(mas, N);                                  //сортировка Шелла
    end = clock();
    TSh3 = ((double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    qs(mas_save_q, 0, N - 1);                       //быстрая сортировка
    end = clock();
    TQS3 = ((double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    qsort(mas_save_qsort, N, sizeof(int), compare);     //стандартная функция сортировки
    end = clock();
    TQSort3 = ((double)(end - start) / CLOCKS_PER_SEC);

    fprintf(Shell3, "\n\n\nПосле сортировки\n");        //вывод в файл результата сортировки
    for (int i = 0; i < N; i++) {
        fprintf(Shell3, " %d ", mas[i]);
    }
    fclose(Shell3);

    Shell4 = fopen("ShellUpDown.txt", "w");            //открытие файла .txt для записи           
    fprintf(Shell4, "До сортировки\n");

    for (int i = 0; i < N/2; i++) {                     //создание последовательности, 
        mas[i] = i;                                     //в которой одна половина - возрастающая 
        mas_save_q[i] = mas[i];                         //последовательность чисел, а вторая – убывающая
        mas_save_qsort[i] = mas[i];                     //и ее запись в массивы mas, mas_save_q, mas_save_qsort
        fprintf(Shell4, " %d ", mas[i]);
    }
    for (int i = N; i >= N/2; i--) {
        mas[i] = i;
        mas_save_q[i] = mas[i];
        mas_save_qsort[i] = mas[i];
        fprintf(Shell4, " %d ", mas[i]);
    }

    start = clock();
    shell(mas, N);                                      //сортировка Шелла
    end = clock();
    TSh4 = ((double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    qs(mas_save_q, 0, N - 1);                           //быстрая сортировка
    end = clock();
    TQS4 = ((double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    qsort(mas_save_qsort, N, sizeof(int), compare);     //стандартная функция сортировки
    end = clock();
    TQSort4 = ((double)(end - start) / CLOCKS_PER_SEC);

    fprintf(Shell4, "\n\n\nПосле сортировки\n");        //вывод в файл результата сортировки
    for (int i = 0; i < N; i++) {
        fprintf(Shell4, " %d ", mas[i]);
    }
    fclose(Shell4);


    printf("--------------------------------------------------------------------------------------------------------------|\n");
    printf("                |        rand        |          up         |          down          |        up&down          |\n");
    printf("----------------+---------------------------------------------------------------------------------------------|\n");
    printf("    Shall       |      %f      |       %f      |        %f        |        %f         |\n", TSh1, TSh2, TSh3, TSh4);
    printf("----------------+---------------------------------------------------------------------------------------------|\n"); 
    printf("      qs        |      %f      |       %f      |        %f        |        %f         |\n", TQS1, TQS2, TQS3, TQS4);
    printf("----------------+---------------------------------------------------------------------------------------------|\n");
    printf("    qsort       |      %f      |       %f      |        %f        |        %f         |\n", TQSort1, TQSort2, TQSort2, TQSort4);
    printf("--------------------------------------------------------------------------------------------------------------|\n");
   
    return 0;
}