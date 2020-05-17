#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#pragma warning (disable:4996)
int NO_VALUE = 0;
// Пишу здесь хэш функцию: массив из структур двухсвязных списков

// Одна ячейка двухсвязного списка
struct list_d {
	struct list_d* parent = NULL;
	struct list_d* son = NULL;
	int value = NO_VALUE;
};

// Создает ячейку
void create_node(struct list_d* node) {
	struct list_d* son = (struct list_d*) calloc(1, sizeof(struct list_d));
	son->parent = node;
	node->son = son;
	son->value = NO_VALUE;

};

// Удаляем ячейку
void del_node(struct list_d* node) {
	node->son = NULL;
	node->parent = NULL;
	node->value = NO_VALUE;
};

// Хэш функция. Берет число, длину кэша и вычислят значение
int hash_f(int x, int cash_len) {
	return ((37 * x + 34) % 7) % cash_len;
}

// Создаем хэш таблицу и заполняем нулями
void create_hash(int cash_len, struct list_d** hash_t) {
	*hash_t = (struct list_d*)calloc(cash_len, sizeof(struct list_d));
}

//Удаляем из хэша значение 
void hash_del(struct list_d* hash_t, int value, int cash_len) {
	//Находим ячейку в кэшэ
	int key = hash_f(value, cash_len);
	list_d* node = &hash_t[key];

	while (node->son != NULL && node->value != value)
		node = node->son;
	node->value = NO_VALUE;

	// Перевязыаем сына удаляемой ячейки к отцу.
	if(node->son != NULL)
	node->son->parent = node->parent;

	del_node(node);
}

// Добавляем в кэш новое значени и сдвигаем все предыдущие
void add_hash(struct list_d* hash_t, int cash_len, int value) {

	//Находим ячейку в кэшэ
	int key = hash_f(value, cash_len);
	list_d* node = &hash_t[key];

	//Проверка на коллизии
	while (node->son != NULL && node->value != 0)
			node = node->son;
		node->value = value;
		create_node(node);

}

int* find_hash(int value, struct list_d* hash_t, int cash_len) {

	int key = hash_f(value, cash_len);
	list_d* node = &hash_t[key];

	while (node->value != value && node->son != NULL)
		node = node->son;
	if (node->value == value)
		return &node->value;
	else
		return NULL;
}

int check_in_hash(int value, struct list_d* hash_t, int cash_len) {
	int key = hash_f(value, cash_len);
	list_d node = hash_t[key];
	while (node.value != value && node.son != NULL)
		node = *node.son;
	if (node.value == value)
		return 1;
	else
		return 0;
}
