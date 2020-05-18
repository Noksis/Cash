#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#pragma warning (disable:4996)

#define Commands1 \
printf("	/|||||||||||||||||||||||||||||||||||||||||||\\\n"); \
printf("	/                    Hello!                 \\\n"); \
printf("	/Please input cash len and number of request\\\n"); \
printf("	/                                           \\\n"); \
printf("	/                                           \\\n"); \
printf("	/                                           \\\n"); \
printf("	/|||||||||||||||||||||||||||||||||||||||||||\\\n"); \
printf("	/Cash len----------------->");\


// Значения по-умолчанию
/*const int NO_VALUE = -1;
const int IN_CASH = 1;
const int OUT_CASH = 0;*/

// Ячейка хэш таблицы
struct list_d {
	struct list_d* parent /*= NULL*/;
	struct list_d* son /*= NULL*/;
	int value /*= 0*/;
};

// Вводим ячейку и создаем к ней привязанную
void create_node(struct list_d* parent);

// Удаляем ячейку по адресу (parent)
void del_node(struct list_d* parent);


//Хэш функция (функция отображения)
//Вводим число(x) и длину хэша(cash_len)
int hash_f(int x, int cash_len);
//Получаем шифровку

// Создаем хэш таблицу
//Вводим длину хэша(cash_len) и указатель на хэш таблицу(**hash_t)
void create_hash(int cash_len, struct list_d** hash_t);

// Удаляем элемент в хэшэ 
//Вводим адресс хэша(hash_t), значение(value) и длину хэша(cash_len).
void hash_del(struct list_d* hash_t, int value, int cash_len);

// Добавляем элемент в хэш
//Вводим адрес хэша(hash_t), длину хэша (cash_len), и значение(value)
void add_hash(struct list_d* hash_t, int cash_len, int value);

// Проверяем наличие в хэшэ
//Вводим значение(value), адрес хэша(hash_t) и длину хэша(cash_len)
int check_in_hash(int value, struct list_d* hash_t, int cash_len);
//Выводит 1 если в хэшэ и 0 если не найден элемент

//Ищем элемент в хэшэ
//Вводим значение(value), адрес хэша(hash_t) и длину хэша(cash_len)
int* find_hash(int value, struct list_d* hash_t, int cash_len);
