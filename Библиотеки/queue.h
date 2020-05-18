#pragma once
// Ячейка кучи
struct node_t
{
	int age;
	int data;
};

static inline int  parent(int i) { return (i - 1) / 2; };

static inline int left(int i) { return 2 * i + 1; };

static inline int right(int i) { return 2 * i + 2; };

// Константы
const int ARR_SIZE = 1;
const int NO_HEAP = -1;
const int IN_HEAP = 1;
const int ADD_SIZE = 1000;

//Создание очереди размером N(размер очереди)
struct node_t* create_queue(int N);

//Определение структуры с наименьшим приоритетом
struct node_t* min_t(struct node_t* left, struct node_t* right);//+


//Определение длины очереди
int size_check(struct node_t* top, int data_t, int N, int* sizet);


//Определение размера очереди
// Вводим начальный элемент очереди(top) и размер очереди(N)
int size(struct node_t* top, int N);//+

//поменять 2 элемента местами
void swap(struct node_t* a, struct node_t* b);//+


//удаление эелемента с минимальным приоритетом
void delete_min(struct node_t* top, int N);//+


//добавление элемента в конец очереди
void push(struct node_t* top, int i, int data_t);//+


//опустить элемент вниз если надо
void shift_down(struct node_t* top, int i, int N);//+


//поднять элемент вверх если надо
void shift_up(struct node_t* top, int i);//+


//проверка на наличие эелемента в очереди
int check(struct node_t* top, int data_t, int N);//+

//												ОСНОВНАЯ ФУНКЦИЯ											//
//Добавляем элемент в хэш или увеличиваем частоту уже существующего
// Вводим начало кучи(top), искомое значение(data_t) и размер кучи(N)
void Incr_freq(struct node_t*** top, int data_t, int N);//+


//возвращает данные с наименьшим приоритетом
int Find_min(struct node_t* top, int N);
