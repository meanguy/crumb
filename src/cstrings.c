#include "cstrings.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "math.h"

string_t* string(char const* text, int64_t length) {
    string_t* self = malloc(sizeof(string_t));
    self->buf = malloc(sizeof(char) * length);

    memcpy(self->buf, text, length);
    self->length = length;

    return self;
}

string_t* string_copy(string_t* self) {
    return string(string_data(self), string_length(self));
}

void string_free(string_t* self) {
    free(self->buf);
    free(self);
}

bool string_equal(string_t const* lhs, string_t const* rhs) {
    if (string_length(lhs) != string_length(rhs)) {
        return false;
    }

    return strncmp(string_data(lhs), string_data(rhs), string_length(lhs)) == 0;
}

char* string_data(string_t const* self) {
    return self->buf;
}

int64_t string_length(string_t const* self) {
    return self->length;
}

string_t* string_substr(string_t const* self, int64_t start, int64_t end) {
    if (start < 0 || start >= self->length) {
        return NULL;
    }

    if (end < start || end >= self->length) {
        return NULL;
    }

    return string(string_data(self) + start, end - start + 1);
}
