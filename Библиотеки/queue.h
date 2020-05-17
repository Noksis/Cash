#pragma once

struct node_t
{
	int age;
	int data;
};

static inline int  parent(int i) { return (i - 1) / 2; };

static inline int left(int i) { return 2 * i + 1; };

static inline int right(int i) { return 2 * i + 2; };

//создание очереди размером N
struct node_t* create_queue(int N);//+
/*
	N - размер кэша
*/
//определение структуры с наименьшим приоритетом
struct node_t* min_t(struct node_t* left, struct node_t* right);//+
/*
	left - левый ребёнок
	right - правый ребёнок
*/

//найти индекс элемента и определить текущую длину очереди
int size_check(struct node_t* top, int data_t, int N, int* sizet);
/*
	top - указатель на начало очереди
	data_t - данные которые хотим найти
	N - максимальный размер очереди
	sizet - указатель на текущий размер очереди
*/

//определение размера очереди
int size(struct node_t* top, int N);//+
/*
	top - указатель на начало массива
	N - размер кэша
*/
//поменять 2 элемента местами
void swap(struct node_t* a, struct node_t* b);//+
/*
*/
//удаление эелемента с минимальным приоритетом
void delete_min(struct node_t* top, int N);//+
/*
	top - указатель на начало массива
	N - размер кэша
*/
//добавление элемента в конец очереди
void push(struct node_t* top, int i, int data_t);//+
/*
	top - указатель на начало очереди
	i - первое не занятое место в очереди
	data_t - адрес вносимых данных
*/
//опустить элемент вниз если надо
void shift_down(struct node_t* top, int i, int N);//+
/*
	top - указатель на начало очереди
	i - номер элемента который хотим опустить
	N - размер кэша
*/
//поднять элемент вверх если надо
void shift_up(struct node_t* top, int i);//+
/*
	top - указатель на начало очереди
	i - номер элемента который хотим поднять
*/
//проверка на наличие эелемента в очереди
int check(struct node_t* top, int data_t, int N);//+
/*
	top - указатель на начало очереди
	data_t - указатель на данные который хотим найти
	N - размер кэша
*/
//добавление или увелечение приоритета данных в очереди
void Incr_freq(struct node_t* top, int data_t, int N);//+
/*
	top - указатель на начало очереди
	sizet - нынешний размер очереди
	data_t - указательна данные которые запрашиваются
	N - размер кэша
*/

//возвращает данные с наименьшим приоритетом
int Find_min(struct node_t* top, int N);
/*
	top - указатель на начало очереди
	N - текущий размер кэша
*/
