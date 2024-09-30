#define _CRT_SECURE_NO_WARNINGS

//подключение библиотек
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

//объявление переменных
int col_student = 3;				//количество студентов
int i, user_answer, user_answer_find;	//перемнные для организации циклов, чтения ответов пользователя
int number = 1;						//нумерация для вывода
char tmp_find[40];					//временная переменная для организации поиска
char tmp_find_save[40];				//временная переменная для организации поиска
char research_famil[20];			//переменная для организации поиска по фамилии студента
char tmp_name[20];					//временная переменная для организации поиска по имени студента
char research_name[20];				//переменная для организации поиска по имени студента
char research_facult[20];			//переменная для организации поиска по факультету студента
int nomzach_research;				//переменная для организации поиска по номеру зачетки студента

struct student {					//объявление структуры
	char famil[20];
	char name[20];
	char facult[20];
	int Nomzach;
}stud[3];


int main() {
	SetConsoleCP(1251);				//подключение русского языка
	setlocale(0, "rus");

	printf("1) Ввести данные с клавиатуры\n");		//вывод информационного сообщения
	printf("2) Загрузить данные из файла\n");		//вывод информационного сообщения

	scanf("%d", &user_answer);						//чтение ответа пользователя
	switch (user_answer) {

	case 1:											//ввод данных с клавиатуры
	{
		for (i = 0; i < col_student; i++) {
			printf("Введите фамилию %d-го студента -> ", number);
			scanf("%20s", stud[i].famil);			//считывание фамилии студента
			number++;
		}

		number = 1;
		for (i = 0; i < col_student; i++) {
			printf("Введите имя %d-го студента -> ", number);
			scanf("%20s", stud[i].name);		//считывание имени студента
			number++;
		}

		number = 1;
		for (i = 0; i < col_student; i++) {
			printf("Введите название факультета  %d-го студента -> ", number);
			scanf("%20s", stud[i].facult);		//считывание факультета студента
			number++;
		}

		number = 1;
		for (i = 0; i < col_student; i++) {
			printf("Введите номер зачётной книжки %d-го студента -> ", number);
			scanf("%d", &stud[i].Nomzach);		//считывание номера зачетки студента
			number++;
		}
		printf("\n");
		break;
	}
	case 2:															//ввод данных из файла
	{
		FILE* file;
		file = fopen("bd.txt", "r");								//открытие файла для считывания
		for (i = 0; i < col_student; i++) {
			fgets(stud[i].famil, 20, file);							//построчное считывание файла
			strtok(stud[i].famil, "\n");							//отсечение "/n" в конце строки
			fgets(stud[i].name, 20, file);
			strtok(stud[i].name, "\n");
			fgets(stud[i].facult, 20, file);
			strtok(stud[i].facult, "\n");
			fscanf_s(file, "%d", &stud[i].Nomzach);
			fscanf_s(file, "\n");
		}
		printf("\n");
	}
	}

	for (i = 0; i < col_student; i++) {									//вывод всего списка студентов
		printf("Cтудент %s %s обучается на факультете %s, номер зачётной книжки % d \n",
			stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
	}
	printf("\n");

	printf("1) Поиск по имени и фамилии\n");							//вывод информационных сообщений
	printf("2) Поиск по факультету\n");
	printf("3) Поиск по номеру зачетной книжки\n");
	printf("0) Выход\n");

	do {
		printf("\nВведите выбранные вариант -> ");
		scanf("%d", &user_answer_find);


		switch (user_answer_find) {
		case 1:															//ввод данных с клавиатуры
		{
			printf("Введите фамилию и имя студента для поиска -> ");	//поиск заданного студента
			getchar();
			fgets(tmp_find, 20, stdin);


			if (strpbrk(tmp_find, " ") == NULL) {
				printf("Данные некорректны");
			}
			else {
				strcpy(tmp_find_save, tmp_find);					//сохранение копии строки в tmp_find_save
				strcpy(research_famil, strtok(tmp_find, " "));		//копирование символов до пробела в research_famil
				strcpy(tmp_name, strpbrk(tmp_find_save, " "));		//сохранение имени в tmp_name (strbrk - поиск первого вхождения)
				memmove(research_name, tmp_name + 1, (strlen(tmp_name) - 2));	//отсечение пробела до имени и "\n" после имени



				for (i = 0; i < col_student; i++) {
					if ((strcmp(stud[i].famil, research_famil) == 0) && (strcmp(stud[i].name, research_name) == 0)) {	//сравнение полей famil и name у каждого студента в структуре student со строкой, введенной пользователем
						printf("Cтудент %s %s обучается на факультете %s, номер зачётной книжки % d \n",				//вывод при совпадении
							stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
					}
				}
			}
			break;
		}

		case 2:											//поиск студента по факультету
		{
			printf("Введите факультет -> ");
			getchar();									//ожидание ввода данных пользователем
			fgets(research_facult, 20, stdin);			//чтение данных пользоввателя
			strtok(research_facult, "\n");				//отсечение "/n" в конце строки
			for (i = 0; i < col_student; i++) {
				if (strcmp(stud[i].facult, research_facult) == 0) {	//сравнение поля facult у каждого студента в структуре student со строкой, введенной пользователем
					printf("Cтудент %s %s обучается на факультете %s, номер зачётной книжки % d \n",	//вывод при совпадении
						stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
				}
			}
			break;
		}



		case 3:													//поиск студента по номеру зачетной книжки
		{
			printf("Введите номер зачетной книжки -> ");
			scanf("%d", &nomzach_research);						//чтение данных пользоввателя

			for (i = 0; i < col_student; i++) {
				if (stud[i].Nomzach == nomzach_research) {		//сравнение поля Nomzach у каждого студента в структуре student с числом, введенным пользователем
					printf("Cтудент %s %s обучается на факультете %s, номер зачётной книжки % d \n",	//вывод при совпадении
						stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
				}
			}
			break;
		}
		}
	} while (user_answer_find != 0);
	return 0;
}
