#include "Hash_H.h"
#include "queue.h"
#include <assert.h>

const int SUCCESS = 1;
const int FAIL = -1;
const int HIT_CASH = 1;
const int MISS_CASH = 0;


//Подсчет попаданий в кэш
int check(int value, int cash_len, struct list_d* hash_t,struct node_t* queue, int* size, int quest) {

	// Проверка данных
	assert(hash_t);
	assert(queue);
	assert(size);

	// Проверяем наличие в кэшэ
	if (check_in_hash(value, hash_t, cash_len) == SUCCESS) {

		//Если в кэшэ, то увеличиваем частоту
		Incr_freq(queue,value,*size);
		return HIT_CASH;

	}
	else

		// Добавляем в кэш
		if (*size < cash_len) {
			// Добавить ячейку с нужным значением
			add_hash(hash_t, cash_len, value);

			// Добавить частоту
			Incr_freq(queue, value, *size);

			// Увеличиваем размер кэша
			*size+=1;

			return MISS_CASH;
		}
	// Удаляем из кэша и добавляем новый элемент
		else {
			// Удалить ячейку с наименьшим приорететом
			hash_del(hash_t, Find_min(queue, *size), cash_len);

			// Добавить ячейку с нужным значением
			add_hash(hash_t, cash_len, value);

			// Увеличить частоту
			Incr_freq(queue,value, *size);

			return MISS_CASH;
		}

	return MISS_CASH;
};

int main(int argc, char** argv) {
	
	//Вводим нужные переменные
	int cash_len = 0;
	int quest = 0;
	int value = 0;
	int count = 0;
	struct list_d* hash_t = NULL;
	int size = 0;
	
	// Читаем длину кэша и кол-во запросов
	assert(scanf("%d%d", &cash_len, &quest));

	FILE* f = fopen("test.txt", "r");

	//Создали очередь из кол-ва запросов
	struct node_t* queue =  create_queue(ARR_SIZE);
	assert(queue);

	// Создаем пустую хэш таблицы
	create_hash(cash_len, &hash_t);


	// Запускаем кэширование запросов
	for (int i = 0; i < quest;i++) {
		// Читаем запрос
		assert(scanf("%d", &value));

		// Проверяем попадание в кэш
		if (check(value,cash_len,hash_t,queue,&size,quest) == 1)
			count++;
	}

	// Выводим ответ
	printf("%d", count);
}
