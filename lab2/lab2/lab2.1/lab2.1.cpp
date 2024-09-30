#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* qs(int* items, int left, int right) { //вызов функции: qs(items, 0, count-1);
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

    return items;
}


#define N 50000
int mas[N];
int* masp = mas;
int* otvet;

int main() {
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        masp[i] = rand() % 100 - 20;
        //printf(" %d ", masp[i]);
    }

    clock_t start = clock();
    otvet = qs(masp, 0, N-1);
    clock_t end = clock();

    /*printf("\n\n");
    for (int i = 0; i < N; i++) {
        printf(" %d ", otvet[i]);
    }*/

    printf("\n\n");
    printf("%f\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}