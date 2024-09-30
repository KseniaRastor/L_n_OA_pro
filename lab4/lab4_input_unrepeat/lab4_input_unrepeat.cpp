#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};

struct Node* root;


struct Node* CreateTree(struct Node* root, struct Node* r, int data) {
	if (r == NULL)					//конец дерева, создание нового узла
	{
		r = (struct Node*)malloc(sizeof(struct Node));		//выделение памяти для нового элемента
		if (r == NULL)										//память не выделена, завершение программы
		{
			printf("Ошибка выделения памяти");
			exit(0);
		}

		r->left = NULL;			//для текщего узла ссылка на левую ветку не определена, приравниваем к NULL
		r->right = NULL;		//для текщего узла ссылка на правую ветку не определена, приравниваем к NULL
		r->data = data;			//в поле data заносится числовое значение
		if (root == NULL) return r;		//если root == NULL, то до этого дерева не существовало, r становится корнем дерева


		if (data > root->data)	root->left = r;		//левая ветка - значение больше текущего
		else root->right = r;						//правая ветка - значение меньше текущего
		return r;
	}

	
											//проход по всем элементам дерева, учитывая их вес
	if (data == r->data) {					//дополнительная проверка на совпадение числовых значений
		printf("Элемент уже существует\n");	//если элементы совпадают, выход из цикла
		return root;
	}
	else {
		if (data > r->data) CreateTree(r, r->left, data);		//левая ветка - значение больше текущего	
		else CreateTree(r, r->right, data);						//правая ветка - значение меньше текущего
	}
	
	return root;
}


void print_tree(struct Node* r, int l) {
	if (r == NULL) {
		return;
	}

	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++) {
		printf(" ");
	}

	printf("%d\n", r->data);
	print_tree(r->left, l + 1);
}

void print_list(struct Node* r) {
	if (r == NULL) {
		return;
	}

	print_list(r->right);

	printf("%d\n", r->data);
	print_list(r->left);
}

int main()
{
	setlocale(LC_ALL, "");
	int D, start = 1;

	root = NULL;
	printf("-1 - окончание построения дерева\n");
	while (start)
	{
		printf("Введите число: ");
		scanf_s("%d", &D);
		if (D == -1)
		{
			printf("Построение дерева окончено\n\n");
			start = 0;
		}
		else
			root = CreateTree(root, root, D);
	}

	print_tree(root, 0);

	printf("\n\n");
	print_list(root);

	return 0;
}
