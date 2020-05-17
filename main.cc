#include "Hash_H.h"
#include "queue.h"
#include <assert.h>
int ARR_SIZE = 100;

int check(int value, int cash_len, struct list_d* hash_t,struct node_t* queue, int* size, int quest) {

	struct list_d* node;
	int* adress_value = find_hash(value, hash_t, cash_len);

	if (check_in_hash(value, hash_t, cash_len) == 1) {
		//Если в хэшэ, то ищем в списке и увеличиваем частоту
		assert(adress_value);
		Incr_freq(queue,value,*size); // Нашел в хэшэ ячейку со значением и передали значение в функцию, которая увеличила
		return 1;
	}
	else
		// Если не в списке, то проверяем заполненость хэша и если заполнен, то удаляем и добавляем. Если нет то добавляем в хэш и добавляем ячейку, увеличивая размер заполнености
		if (*size < cash_len) {
			// Добавить ячейку с нужным значением
			add_hash(hash_t, cash_len, value);
			adress_value = find_hash(value, hash_t, cash_len);
			// Создать привязку к частоте
			Incr_freq(queue, value, *size);
			*size+=1;
		}
		else {
			// Удалить ячейку с наименьшим приорететом
			hash_del(hash_t, Find_min(queue, *size), cash_len); // Нужна функция Find_min, чтобы я из хэша удалил ячейку
			// Добавить ячейку с нужным значением

			add_hash(hash_t, cash_len, value);
			adress_value = find_hash(value, hash_t, cash_len);
			Incr_freq(queue,value, *size);
		}

	return 0;
};

int main(void) {
	int cash_len, quest, value;
	int count = 0;
	struct list_d* hash_t;
	int size = 0;
	
	// Читаем длину кэша и кол-во запросов
	scanf("%d%d", &cash_len, &quest);

	//Создали очередь из кол-ва запросов
	struct node_t* queue =  create_queue(ARR_SIZE);

	// Создаем пустую хэш таблицы
	create_hash(cash_len, &hash_t);

	for (int i = 0; i < quest;i++) {
		scanf("%d", &value);
		if (check(value,cash_len,hash_t,queue,&size,quest) == 1)
			count++;
	}
	printf("%d", count);
}
