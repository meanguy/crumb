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

bool tuple_equal(tuple_t* lhs, tuple_t* rhs) {
    if (lhs == rhs) {
        return true;
    }

    return lhs->first == rhs->first && lhs->second == rhs->second;
}
