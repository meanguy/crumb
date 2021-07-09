#include "tuple.h"

#include <stdlib.h>

tuple_t* tuple_new(void* first, void* second) {
    tuple_t* self = malloc(sizeof(tuple_t));
    self->first = first;
    self->second = second;

    return self;
}

tuple_t* tuple_copy(tuple_t* self) {
    return tuple_new(self->first, self->second);
}

void tuple_free(tuple_t* self) {
    free(self);
}
