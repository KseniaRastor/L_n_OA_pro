
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct node {
	char inf[256];												// полезная информация
	struct node* next, * prev;									// ссылка на соседние элементы 
};
typedef node* pnode;											// тип "указатели на узел"

struct stack {
	pnode head, tail;
};



void crop(char* str) {				//функция отсечения символа перевода на новую строку ('\n') 
	int str_num = 0;
	while (str[str_num] != '\0')
	{
		if (str[str_num] == char(10))
		{
			str[str_num] = char(0);
		};
		str_num++;
	};
}


/* Последовательное добавление в список элемента*/
stack* push(stack& S, char& name) {
	pnode newnode;						//создание нового узла
	newnode = new node;

	strcpy(newnode->inf, &name);		//введенная пользователем информация копируется в поле inf

	if (S.head == NULL) {				// если списка нет, то
		newnode->next = NULL;			// newnode - голова (строка 54) и хвост (строка 45)
		newnode->prev = NULL;			// указатели на соседние элементы указывают на NULL
		S.tail = newnode;
	}
	else {
		newnode->next = S.head;			//следующий элемент для добавляемого узла - голова
		newnode->prev = NULL;			//предыдущего элемента для добавляемого узла нет
	}


	if (S.head) S.head->prev = newnode;	//если в очереди был элемент, то он становится предыдущим для головы
	S.head = newnode;					//добавляемый элемент становится головой списка

	return (&S);
}


/* Просмотр содержимого списка. */
void review(stack& S) {
	struct stack S_tmp = S;

	if (S.tail == NULL) {
		printf("Список пуст\n");
		return;
	}
	while (1) {
		printf("Имя - %s, \n", S_tmp.tail->inf);	//вывод поля inf текущего узла
		if (S_tmp.tail->prev == NULL) {				//если указатель на следующий элемент NULL, дошли до конца списка
			return;
		}
		else {
			S_tmp.tail = S_tmp.tail->prev;			//переход на следующий узел
		}
	}
}


/* Поиск элемента по содержимому. */
void find(stack& S, char& name) {
	int i = 1;
	struct stack S_tmp = S;

	if (S.tail == NULL) {
		printf("Список пуст\n");
	}
	do {
		if (strcmp(&name, S_tmp.tail->inf) == 0) {		//найдено совпадение - вывод номера элемента в стеке
			printf("Элемент №%d в списке\n", i);
			return;
		}
		i++;
		S_tmp.tail = S_tmp.tail->prev;			//переход к следующему узлу
	} while (S_tmp.tail != NULL);
	printf("Элемент не найден\n");
	return;
}


/* Удаление элемента по содержимому. */
stack* pop(stack& S) {

	if (S.tail == NULL) {
		printf("Список пуст\n");
	}

	pnode EndNode = S.tail;				//EndNode указывает на последний узел очереди
	S.tail = EndNode->prev;				//хвостом становится предпоследний узел
	if (S.tail) S.tail->next = NULL;	//если предпоследний узел найден, то его указатель на следующий элемент ссылается на NULL
	else S.head = NULL;					//иначе список пуст (состоял из одного удаляемого узла)

	delete EndNode;						//удаление
	printf("Операция выполнена успешно\n");
	return(&S);
}


int answer;
char name[50];
int flag_first = 1;

int main() {
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	printf("1) Добавление элемента\n");
	printf("2) Просмотр всех элементов\n");
	printf("3) Поиск элемента\n");
	printf("4) Удаление элемента\n");
	printf("0) Выход\n");
	stack* S = (stack*)malloc(sizeof(stack));
	do {

		if (flag_first == 1) {
			S->head = NULL;
			S->tail = NULL;
			flag_first = 0;
		}



		printf("\nВведите номер выбранного варианта -> ");
		scanf("%d", &answer);

		switch (answer) {
		case (1): {
			printf("Введите название объекта: \n");						// вводим данные
			getchar();
			fgets(name, 50, stdin);
			crop(name);
			if (*name == 0) {
				printf("Запись не была произведена\n");
				break;
			}

			S = push(*S, *name);
			break;
		}

		case (2): {
			review(*S);
			break;
		}

		case (3): {
			printf("Введите искомый элемент -> ");
			getchar();
			fgets(name, 50, stdin);
			crop(name);
			if (*name == 0) {
				printf("Запись не была произведена\n");
				break;
			}

			find(*S, *name);
			break;
		}

		case (4): {
			S = pop(*S);
			break;
		}
		}
	} while (answer != 0);

	return 0;
}