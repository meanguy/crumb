#pragma once

typedef struct {
    void* first;
    void* second;
} tuple_t;

tuple_t* tuple_new(void*, void*);
tuple_t* tuple_copy(tuple_t*);
void tuple_free(tuple_t*);
