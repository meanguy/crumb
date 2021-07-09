#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct list {
    void** buf;
    int64_t capacity;
    int64_t size;
} list_t;

list_t* list_new(int64_t);
list_t* list_copy(list_t*);
void list_free(list_t*);

list_t* list_append(list_t*, void*);
list_t* list_clear(list_t*);
list_t* list_extend(list_t*, list_t*);
list_t* list_insert(list_t*, int64_t, void*);
list_t* list_prepend(list_t*, void*);
list_t* list_remove(list_t*, void*);
list_t* list_resize(list_t*, int64_t);
list_t* list_slice(list_t*, int64_t, int64_t);

bool list_equal(list_t*, list_t*);

int64_t list_capacity(list_t*);
int64_t list_find(list_t*, void*);
int64_t list_size(list_t*);

void* list_get(list_t*, int64_t);
void* list_pop(list_t*, int64_t);
void* list_set(list_t*, int64_t, void*);

void list_fprint(list_t*, FILE*);
void list_foreach(list_t*, void(void*));
