
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct node{
	int priority;
	char inf[256];												// полезная информация
	struct node* next;											// ссылка на следующий элемент 
};
struct node* head = NULL, * last = NULL, * f = NULL;			// указатели на первый и последний элементы списка
int dlinna = 0;


// Функции добавления элемента, просмотра списка, удаления элемента из списка
void spstore(void), review(void), del(char* name);

char find_el[256];
struct node* find(char* name);									// функция нахождения элемента
struct node* get_struct(void);									// функция создания элемента

void crop(char* str) {			//функция отсечения символа перевода на новую строку ('\n') 
	int str_num = 0;
	while (str[str_num] != '\0')				//проход по всем символам слова
	{
		if (str[str_num] == char(10))			//если символ == символу перевода на новую строки ('\n')
		{
			str[str_num] = char(0);				//замена '\n' на "нулевой символ" (исключение '\n' в конце слова) 
		};
		str_num++;								//переход к следующему символу слова
	};
}

struct node* get_struct(void)			//функция используется в функции spstore()
{
	struct node* p = NULL;				//указатнль на добавляемый элемент
	char s[256];						//переменная для считывания данных пользователя

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)		// выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите название объекта: \n");						// вводим данные
	getchar();
	fgets(s, 50, stdin);										//запись данных в s
	crop(s);													//отсечение '/n'
	
	if (*s == 0)												//если пользователь ничего не ввел, то возвращаем NULL
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	strcpy(p->inf, s);											//запись данных в поле структуры inf
	printf("Введите приоритет объекта: \n");					//вводим данные о приоритете элемента
	scanf("%d", &(p->priority));								//считываем в поле структуры priority
	

	p->next = NULL;												//новый элемент указывает на NULL

	return p;													// возвращаем указатель на созданный элемент
}

/* Добавление в список элемента*/
void spstore(void){
	struct node* p = NULL;										//указатель на добавляемый элемент
	struct node* struc = head;									//указатель, проходящий по списку, установлен на начало списка
	struct node* prev = NULL;									//указатель на предыдущий элемент

	p = get_struct();
	if (head == NULL && p != NULL) {							// если списка нет, то устанавливаем голову списка
		head = p;												//p - первый и последний элемент списка
		last = p;
	}
	else if (head != NULL && p != NULL) {						// список уже есть, добавляем элемент в конец
		do {
			if (struc->priority > p->priority) {				//сравнение приоритета - если приоритет р выше приоритета лемента в структуре, то
				if (prev==NULL) {								//(prev==NULL, значит приоритет добавляемого элемента сравнивался с головой)р добавляется на первое место - становится головой списка
					p->next = head;								//р указывает на начало списка
					head = p;									//р - голова списка
				}
				else {											//р добавляется после головы
					prev->next = p;								//предыдущий элемент указывет на р
					p->next = struc;							//р указывает на текущий элемент struc
				}
				return;
			}
			
			prev = struc;										//сохранение текущего элемента как предыдущего								
			struc = struc->next;								//переход к следующему элементу
			
		} while (struc != NULL);
																//приоритет самый низкий, р добавляется в конец списка
		last = prev;											//запись последнего элемента											
		last->next = p;											//последний элемент указывает на добавляемый элемент
		last = p;												//добавляемый элемент становится последним
	}
	return;
}


/* Просмотр содержимого списка. */
void review(void){
	struct node* struc = head;									// указатель, проходящий по списку, установлен на начало списка
	if (head == NULL){											//порверка на существование списка
		printf("Список пуст\n");
	}
	while (struc){												//пока struc не NULL
		printf("Имя - %s, \n", struc->inf);						//вывод информационного поля inf элемента структуры 
		struc = struc->next;									//переход к следующему элементу
	}
	return;
}


/* Поиск элемента по содержимому. */
struct node* find(char* name){
	int i = 1;
	struct node* struc = head;									//указатель на голову списка
	if (head == NULL){											//порверка на существование списка
		printf("Список пуст\n");
	}
	while (struc){												//пока struc не NULL
		if (strcmp(name, struc->inf) == 0){						//сравнение введенных данных и поля inf текущего элемента структуры
			printf("Элемент с приоритетом №%d \n", struc->priority);		//вывод приоритета элемента
			return struc;										//возвращаем текущий элемент
		}
		i++;
		struc = struc->next;									//переход к  следующему элементу
	}
	printf("Элемент не найден\n");								//элемент не найден - возвращаемое значение NULL
	return NULL;
}


/* Удаление элемента по содержимому. */
void del(char* name){
	struct node* struc = head;								// указатель, проходящий по списку установлен на начало списка
	struct node* prev = struc;								// указатель на предшествующий удаляемому элемент
	int flag = 0;											// индикатор отсутствия удаляемого элемента в списке

	if (head == NULL) {										// если голова списка равна NULL, то список пуст		
		printf("Список пуст\n");
		return;
	}

	if (strcmp(name, struc->inf) == 0) {					// если удаляемый элемент - первый
		flag = 1;											// выставляем индикатор
		head = struc->next;									// установливаем голову на следующий элемент
		free(struc);										// удаляем первый элемент
		struc = head;										// устанавливаем указатель для продолжения поиска
		printf("Удаление выполнено успешно\n");
	}
	else
	{
		struc = struc->next;
	}

	while (struc)												// проход по списку и поиск удаляемого элемента
	{
		if (strcmp(name, struc->inf) == 0)						// если нашли, то
		{
			flag = 1;											// выставляем индикатор
			if (struc->next)									// если найденный элемент не последний в списке
			{
				prev->next = struc->next;						// меняем указатели
				free(struc);									// удаляем  элемент
				struc = prev->next;								// устанавливаем указатель для продолжения поиска
				printf("Удаление выполнено успешно\n");
			}
			else												// если найденный элемент последний в списке
			{
				prev->next = NULL;								// обнуляем указатель предшествующего элемента
				free(struc);									// удаляем  элемент
				printf("Удаление выполнено успешно\n");
				return;
			}
			
		}
		else													// если не нашли, то
		{
			prev = struc;										// устанавливаем указатели для продолжения поиска
			struc = struc->next;
		}
	}

	if (flag == 0)												// если флаг = 0, значит нужный элемент не найден
	{
		printf("Элемент не найден\n");
		return;
	}
}


void swap() {
	int i = 1;
	int element_1, element_2;
	printf("Введите 1-ый элемент -> ");
	scanf("%d", &element_1);
	printf("Введите 2-ой элемент -> ");
	scanf("%d", &element_2);

	struct node* struc = head;
	struct node* struc_save = head;
	struct node* node_1 = NULL;
	struct node* node_2 = NULL;
	char char_swap[50];				//переменная для сохранения информации
	//char* node_swap;

		//,* node_2, *node_swap;

	if (head == NULL) {
		printf("Список пуст\n");
	}
	while (struc) {					//нахождение нужных элементов в структуре
		if (i == element_1) {
			node_1 = struc;
		}
		if (i == element_2) {
			node_2 = struc;
		}
		i++;
		struc = struc->next;
	}
	
	strcpy(char_swap, node_1->inf);		//перемещение информации из поля inf
	strcpy(node_1->inf, node_2->inf);
	strcpy(node_2->inf, char_swap);

	while (struc_save) {				//вывод структуры
		printf("Имя - %s, \n", struc_save->inf);
		struc_save = struc_save->next;
	}

	return;
}


int answer;				//номер выбранного варианта пользователем
char name[50];			//переменная для поиска по содержимому


int main() {
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	printf("1) Добавление элемента\n");
	printf("2) Просмотр всех элементов\n");
	printf("3) Поиск элемента\n");
	printf("4) Удаление элемента\n");
	printf("0) Выход\n\n");

	do {
		printf("\nВведите номер выбранного варианта -> ");
		scanf("%d", &answer);
		switch (answer) {
		case (1):{
			spstore();				//добавление элемента
			break;
			}

		case (2): {
			review();				//просмотр всех элементо
			break;
		}

		case (3): {
			printf("Введите искомый элемент -> ");
			getchar();
			fgets(name, 50, stdin);
			crop(name);
			if (*name == 0) {					//проверка на пустую строку
				printf("Запись не была произведена\n");
				break;
			}

			find(name);				//поиск элемента
			break;
		}
		case (4): {
			printf("Введите удаляемый элемент -> ");
			getchar();
			fgets(name, 50, stdin);
			crop(name);
			if (*name == 0) {					//проверка на пустую строку
				printf("Запись не была произведена\n");
				break;
			}

			del(name);				//удаление элемента
			break;
		}

		case (5): {
			swap();					//функция меняет местами поля inf элементов struc 
			break;
		}
		}
	} while (answer != 0);

	return 0;
}