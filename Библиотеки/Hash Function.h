#pragma once
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#pragma warning (disable:4996)


struct list_d {
	struct list_d* parent = NULL;
	struct list_d* son = NULL;
	int value = 0;
};

struct list_d create_node(struct list_d* parent);

struct list_d del_node(struct list_d* parent);

int hash_f(int x, int cash_len);

void create_hash(int cash_len, struct list_d** hash_t);

void hash_del(struct list_d* hash_t, int value, int cash_len);

void add_hash(struct list_d* hash_t, int cash_len, int value);

int check_in_hash(int value, struct list_d* hash_t, int cash_len);

int* find_hash(int value, struct list_d* hash_t, int cash_len);
