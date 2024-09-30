#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct Node {
	int data;				//полезная информация
	struct Node* left;		//левая ветка
	struct Node* right;		//правая ветка
};

struct Node* root;		//указатель на дерево
int count = 0;			//подсчёт числа вхождений заданного элемента в дерево

struct Node* CreateTree(struct Node* root, struct Node* r, int data){
	if (r == NULL)		//конец дерева, создание нового узла
	{
		r = (struct Node*)malloc(sizeof(struct Node));		//выделение памяти для нового элемента
		if (r == NULL)										//память не выделена, завершение программы
		{
			printf("Ошибка выделения памяти");
			exit(0);
		}

		r->left = NULL;				//для текщего узла ссылка на левую ветку не определена, приравниваем к NULL
		r->right = NULL;			//для текщего узла ссылка на правую ветку не определена, приравниваем к NULL
		r->data = data;				//в поле data заносится числовое значение
		if (root == NULL) return r;	//если root == NULL, то до этого дерева не существовало, r становится корнем дерева

		if (data > root->data)	root->left = r;	//левая ветка - значение больше текущего
		else root->right = r;					//правая ветка - значение меньше текущего
		return r;
	}

								//проход по всем элементам дерева, учитывая их вес
	if (data > r->data)			//левая ветка - значение больше текущего
		CreateTree(r, r->left, data);
	else
		CreateTree(r, r->right, data);		//правая ветка - значение меньше текущего

	return root;
}


//вывод дерева производится слева направо
void print_tree(struct Node* r, int l){
	if (r == NULL){		//конец дерева, выход из функции
		return;
	}

	print_tree(r->right, l + 1);	//рекурсивный вызов функции для правой ветки
	for (int i = 0; i < l; i++){	//цикл для организации вывода значений дерева
		printf("  ");
	}

	printf("%d\n", r->data);		//вывод значений дерева
	print_tree(r->left, l + 1);		//рекурсивный вызов функции для левой ветки
}

int find(struct Node* r, int D_find) {

	if (r == NULL){		//конец дерева, выход из функции
		return count;
	}

	if (r->data == D_find) count++;	//элемент найден, увеличение счетчика count
		
	find(r->right, D_find);		//рекурсивный вызов функции для правой ветки
	find(r->left, D_find);		//рекурсивный вызов функции для левой ветки
}



int main()
{
	setlocale(LC_ALL, "");
	int D, start = 1;	//числовое значение узла, флаг для завершения построения дерева
	int D_find;									//искомый элемент, вводит пользователь

	root = NULL;
	printf("-1 - окончание построения дерева\n");
	while (start)								//выход из цикла по флагу start
	{
		printf("Введите число: ");
		scanf_s("%d", &D);
		if (D == -1)
		{
			printf("Построение дерева окончено\n\n");
			start = 0;							//установка флага
		}
		else
			root = CreateTree(root, root, D);	//вызов функции построения дерева
	}

	print_tree(root, 0);

	printf("\nВведите искомый элемент -> ");
	scanf("%d", &D_find);
	count = find(root, D_find);					//вызов функции нахождения элемента
	if (count) printf("\nИскомый элемент найден %d раз(а)\n", count);
	else printf("\nИскомый элемент не найден\n");

	return 0;
}
