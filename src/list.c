#include "list.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "math.h"

list_t* list_new(int64_t capacity) {
    list_t* self = malloc(sizeof(list_t));
    self->buf = malloc(sizeof(void*) * capacity);
    self->capacity = capacity;
    self->size = 0;

    return self;
}

list_t* list_copy(list_t* self) {
    list_t* other = list_new(self->capacity);

    other->size = self->size;
    for (int64_t n = 0; n < self->size; ++n) {
        other->buf[n] = self->buf[n];
    }

    return other;
}

void list_free(list_t* self) {
    for (int64_t n = 0; n < self->size; ++n) {
        self->buf[n] = NULL;
    }

    free(self->buf);
    free(self);
}

list_t* list_append(list_t* self, void* elem) {
    if (self->size >= self->capacity) {
        self = list_resize(self, self->capacity * 2);
    }

    self->buf[self->size] = elem;
    ++self->size;

    return self;
}

list_t* list_clear(list_t* self) {
    for (int64_t n = 0; n < self->size; ++n) {
        self->buf[n] = NULL;
    }

    self->size = 0;

    return self;
}

list_t* list_extend(list_t* self, list_t* other) {
    int newsize = self->size + other->size;

    if (newsize >= self->capacity) {
        self = list_resize(self, crumb_max(newsize, self->capacity * 2));
    }

    for (int64_t n = 0; n < other->size; ++n) {
        self = list_append(self, other->buf[n]);
    }

    return self;
}

list_t* list_prepend(list_t* self, void* elem) {
    if ((self->size + 1) >= self->capacity) {
        self = list_resize(self, self->capacity * 2);
    }

    for (int64_t n = self->size; n > 0; --n) {
        self->buf[n] = self->buf[n-1];
    }

    self->buf[0] = elem;
    ++self->size;

    return self;
}

list_t* list_resize(list_t* self, int64_t capacity) {
    assert(capacity > self->capacity && capacity > self->size);

    self->capacity = capacity;
    self->buf = realloc(self->buf, self->capacity);

    return self;
}

list_t* list_slice(list_t* self, int64_t start, int64_t end) {
    if (start < 0 || start > end || end < 0) {
        return NULL;
    }

    if (start > self->size || end > self->size) {
        return NULL;
    }

    int64_t num_elems = end - start;
    list_t* slice = list_new(num_elems);
    for (int64_t n = start; n < end; ++n) {
        slice = list_append(slice, list_get(self, n));
    }

    return slice;
}

bool list_equal(list_t* lhs, list_t* rhs) {
    if (lhs == rhs) {
        return true;
    }

    if (lhs->size != rhs->size) {
        return false;
    }

    for (int64_t n = 0; n < lhs->size; n++) {
        if (lhs->buf[n] != rhs->buf[n]) {
            return false;
        }
    }

    return true;
}

int64_t list_capacity(list_t* self) {
    return self->capacity;
}

int64_t list_find(list_t* self, void* elem) {
    for (int64_t n = 0; n < self->size; ++n) {
        if (self->buf[n] == elem) {
            return n;
        }
    }

    return -1;
}

int64_t list_size(list_t* self) {
    return self->size;
}

void* list_get(list_t* self, int64_t index) {
    if (index >= self->size || index < 0) {
        return NULL;
    }

    return self->buf[index];
}

void* list_insert(list_t* self, int64_t index, void* elem) {
    if (self->size >= self->capacity) {
        self = list_resize(self, self->capacity * 2);
    }

    for (int64_t n = 0; n < (self->size-index); ++n) {
        self->buf[index+n+1] = self->buf[index+n];
    }
    self->buf[index] = elem;
    ++self->size;

    return self;
}

void* list_pop(list_t* self, int64_t index) {
    if (index >= self->size || index < 0) {
        return NULL;
    }

    void* elem = self->buf[index];

    for (int n = index; n < self->size-1; ++n) {
        self->buf[n] = self->buf[n+1];
    }
    --self->size;

    return elem;
}

void* list_remove(list_t* self, void* elem) {
    return list_pop(self, list_find(self, elem));
}

void* list_set(list_t* self, int64_t index, void* elem) {
    if (index >= self->size) {
        return NULL;
    }

    self->buf[index] = elem;

    return elem;
}

void list_fprint(list_t* self, FILE* fd) {
    fprintf(fd, "[");
    for (int n = 0; n < self->size; ++n) {
        fprintf(fd, "%px", self->buf[n]);

        if (n < self->size - 1) {
            fprintf(fd, ", ");
        }
    }
    fprintf(fd, "]\n");
}

void list_foreach(list_t* self, void(fn)(void*)) {
    for (int n = 0; n < self->size; ++n) {
        fn(self->buf[n]);
    }
}
