#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#pragma warning (disable:4996)

#include "Hash_Function.h"

// Значения по-умолчанию
/*const int NO_VALUE = -1;
const int IN_CASH = 1;
const int OUT_CASH = 0;*/

// Одна ячейка хэша 
/*struct list_d {
	struct list_d* parent = NULL;
	struct list_d* son = NULL;
	int value = NO_VALUE;
};*/

// Создает ячейку
void create_node(struct list_d* node) {

	// Создание новой ячейки
	struct list_d* son = (struct list_d*) calloc(1, sizeof(struct list_d));

	// Проверка адресса
	assert(node);
	
	son->parent = node;
	node->son = son;
	son->value = -1/*NO_VALUE*/;

};

// Удаляем ячейку
void del_node(struct list_d* node) {

	
	node->son = NULL;
	node->parent = NULL;
	node->value = -1/*NO_VALUE*/;
};

// Хэш функция (Добавил побитовые операции в начале)
int hash_f(int x, int cash_len) {
	x += (x << 3);
	x ^= (x >> 11);
	x += (x << 15);
	return ((37 * x + 34) % 7) % cash_len;
}

// Создаем хэш таблицу и заполняем нулями
void create_hash(int cash_len, struct list_d** hash_t) {
	*hash_t = (struct list_d*)calloc(cash_len, sizeof(struct list_d));
	for (int i = 0; i < cash_len; i++)
		(*hash_t + i)->value = -1/*NO_VALUE*/;
}

//Удаляем из хэша значение 
void hash_del(struct list_d* hash_t, int value, int cash_len) {
	

	//Находим ячейку в кэшэ
	int key = hash_f(value, cash_len);
	struct list_d* node = &hash_t[key];
	struct list_d* save_node;
	// Проверка на коллизии
	while (node->son != NULL && node->value != value)
		node = node->son;
	node->value = -1/*NO_VALUE*/;

	// Перевязыаем сына удаляемой ячейки к отцу.
	
	//Если есть коллизии
	if (node->son != NULL) {
		//Если есть сверху что-то
		if (node->parent != NULL) {
			node->son->parent = node->parent;
			del_node(node);
			return;
		}
		// Если сверху нет ничего
		else {
			save_node = node->son;
			del_node(node);
			hash_t[key] = *save_node;
			hash_t[key].parent = NULL;
			return;
		}
	}
	del_node(node);
	return;

	
}

// Добавляем в кэш новое значени и сдвигаем все предыдущие
void add_hash(struct list_d* hash_t, int cash_len, int value) {

	//Находим ячейку в кэшэ
	int key = hash_f(value, cash_len);
	struct list_d* node = &hash_t[key];

	//Проверка на коллизии
	while (node->son != NULL && node->value != 0)
			node = node->son;
	
	// Создаем ячейку
	node->value = value;
	create_node(node);

}

// Ищем в хэшэ
int* find_hash(int value, struct list_d* hash_t, int cash_len) {

	// Ищем в хэш таблице
	int key = hash_f(value, cash_len);
	struct list_d* node = &hash_t[key];

	// Проверка на коллизии
	while (node->value != value && node->son != NULL)
		node = node->son;

	// Вывод результата
	if (node->value == value)
		return &node->value;
	else
		return NULL;
}

// Проверяем в хэшэ
int check_in_hash(int value, struct list_d* hash_t, int cash_len) {
	// Ищем в хэшэ
	int key = hash_f(value, cash_len);
	struct list_d node = hash_t[key];

	// Проверка на коллизии
	while (node.value != value && node.son != NULL)
		node = *node.son;

	// Вывод результата
	if (node.value == value)
		return 1/*IN_CASH*/;
	else
		return 0/*OUT_CASH*/;
}
