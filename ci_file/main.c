#include "Hash_Function.h"
#include "queue.h"
#include <assert.h>

/*const int SUCCESS = 1;
const int FAIL = -1;
const int HIT_CASH = 1;
const int MISS_CASH = 0;*/


//Подсчет попаданий в кэш
int check(int value, int cash_len, struct list_d* hash_t,struct node_t** queue_big, int* size, int quest,struct node_t** queue_small) {

	// Проверка данных
	assert(hash_t);
	assert(queue_big);
	assert(size);
	assert(queue_small);

	int age_value = 1;

	// Проверяем наличие в кэшэ
	if (check_in_hash(value, hash_t, cash_len) == 1/*SUCCESS*/) {

		//Если в кэшэ, то увеличиваем частоту в большой куче
		Incr_freq(&queue_big,value,*size,&age_value);

		// Теперь увеличиваем частоту в малой кучи
		Incr_freq_small(&queue_small, value, cash_len, age_value);

		return 1/*HIT_CASH*/;

	}
	else

		// Добавляем в кэш
		if (*size < cash_len) {
			// Добавить ячейку с нужным значением
			add_hash(hash_t, cash_len, value);

			// Добавить частоту в большую кучу
			Incr_freq(&queue_big, value, *size, &age_value);

			
			// Добавить частоту из большой кучи в малую
			Incr_freq(&queue_small, value, cash_len, &age_value);

			// Увеличиваем размер кэша
			*size+=1;

			return 0/*MISS_CASH*/;
		}
	// Удаляем из кэша и добавляем новый элемент
		else {
			// Удалить ячейку с наименьшим приорететом
			hash_del(hash_t, Find_min(*queue_small), cash_len);

			// Добавить ячейку с нужным значением
			add_hash(hash_t, cash_len, value);

			// Увеличить частоту в большой куче
			Incr_freq(&queue_big,value, *size, &age_value);

			// Удаляем минимальное из малой кучи
			delete_min(*queue_small, cash_len);

			// Добавить частоту из большой кучи в малую
			Incr_freq_small(&queue_small, value, cash_len, age_value);

			return 0/*MISS_CASH*/;
		}

	return 0/*MISS_CASH*/;
};

int main(int argc, char** argv) {
	
	//Вводим нужные переменные
	int cash_len = 0;
	int quest = 0;
	int value = 0;
	int count = 0;
	struct list_d* hash_t = NULL;
	int size = 0;
	
	Commands1 // Красивое меню

	// Читаем длину кэша и кол-во запросов
	assert(scanf("%d", &cash_len));
	printf("	/Number of request-------->");
	assert(scanf("%d", &quest));

	//Создали очередь из кол-ва запросов
	struct node_t* queue_big =  create_queue(1/*ARR_SIZE*/);
	assert(queue_big);

	//Создаем очередь размером с ХЭШ
	struct node_t* queue_small = create_queue(cash_len);
	assert(queue_small);

	// Создаем пустую хэш таблицы
	create_hash(cash_len, &hash_t);


	// Запускаем кэширование запросов
	for (int i = 0; i < quest; i++) {

		// Читаем запрос
		printf("	/Page[%d]----------------->",i);
		assert(scanf("%d", &value));
		printf("\n");

		// Проверяем попадание в кэш
		if (check(value,cash_len,hash_t,&queue_big,&size,quest,&queue_small) == 1)
			count++;
	}

	// Выводим ответ
	printf("%d", count);
}
