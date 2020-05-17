#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct node_t
{
	int age;
	int data;
};

static inline int parent(int i) { return (i - 1) / 2; };

static inline int left(int i) { return 2 * i + 1; };

static inline int right(int i) { return 2 * i + 2; };

const int ARR_SIZE = 100;
const int NO_HEAP = -1;
const int IN_HEAP = 1;
const int ADD_SIZE = 1000;

// Создаем очередь
struct node_t* create_queue(int N)
{
	struct node_t* top = (struct node_t*)calloc(N, sizeof(struct node_t));
	return top;
};

//Ищем размер кучи
int size_check(struct node_t* top, int data_t, int N, int* sizet)
{
	int place = NO_HEAP;

	assert(sizet != NULL);
	assert(top != NULL);

	for (int i = 0; i < N; i++)
	{
		if ((((top + i)->data) == data_t) && (((top + i)->age) != 0))
			place = i;
		if (((top + i)->age) == 0)
		{
			*sizet = i;
			break;
		};
	};
	if (*sizet == -1)
		*sizet = N;
	return place;
};

// Ищем минимальный элемент
struct node_t* min_t(struct node_t* left, struct node_t* right)
{
	assert(left != NULL);
	assert(right != NULL);

	if ((left->age) <= (right->age))
		return left;
	else
		return right;
};

// Меняем местами два элемента
void swap(struct node_t* a, struct node_t* b)
{
	struct node_t per = *a;
	a->age = b->age;
	b->age = per.age;
	a->data = b->data;
	b->data = per.data;
};

void shift_down(struct node_t* top, int i, int N)
{
	int pright = 0;
	int pleft = 0;
	while (right(i) < N)
	{
		int new_i = 0;
		pright = right(i);
		pleft = left(i);
		struct node_t* pmin = min_t((top + pleft), (top + pright));
		if ((pmin->age) == ((top + pright)->age))
			new_i = pright;
		else
			new_i = pleft;
		swap((top + i), (top + new_i));
		i = new_i;
	};
	if (left(i) < N)
		swap((top + i), (top + left(i)));
};

void shift_up(struct node_t* top, int i)
{
	if (i == 0)
		return;
	int new_i = parent(i);

	assert((new_i > 0) && "shift_up");
	assert(((top + i) != NULL) && "shift_up");
	assert(((top + new_i) != NULL) && "shift_up");

	if (((top + i)->age) < ((top + new_i)->age))
	{
		swap(top + i, (top + new_i));
		shift_up(top, new_i);
	};
};

// Добавляем элемент в очередь
void push(struct node_t* top, int i, int data_t) {


	assert((top != NULL) && "push");
	assert((i >= 0) && "push");


	((top + i)->age)++;
	((top + i)->data) = data_t;
};

// Добавления элемента в очередь или увеличение возраста
void Incr_freq(struct node_t* top, int data_t, int N) {

	//Задаем начальный размер кучи
	static int size = ARR_SIZE;

	//Задаем длину кучи
	int sizet = NO_HEAP;

	// Узнаем нахождение в куче
	int p = size_check(top, data_t, size, &sizet);

	//Выполняем добавление или увеличение
	if (p == NO_HEAP) {

		// Добавление
		if (sizet < size)
		{
			push(top, sizet, data_t);
			shift_up(top, sizet);
		}
		// Добавление и удлинение массива
		else
			if (sizet == size)
			{
				size = size + ADD_SIZE;
				top = (struct node_t*)realloc(top, size);
				push(top, sizet, data_t);
				shift_up(top, sizet);
			};
	}
	// Обновление возраста
	else
	{
		((top + p)->age)++;
		shift_up(top, p);
		shift_down(top, p, sizet);
	};
};

// Поиск минимального
int Find_min(struct node_t* top, int N)
{
	assert((top != NULL) && "Find_min");
	return top->data;
};
