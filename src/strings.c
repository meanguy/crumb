#include "strings.h"

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

void string_free(string_t* self) {
    free(self->buf);
    free(self);
}

bool string_equal(string_t* lhs, string_t* rhs) {
    return strncmp(string_data(lhs), string_data(rhs), crumb_min(string_length(lhs), string_length(rhs))) == 0;
}

char* string_data(string_t* self) {
    return self->buf;
}

int64_t string_length(string_t* self) {
    return self->length;
}
