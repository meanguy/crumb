#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    char* buf;
    int64_t length;
} string_t;

string_t* string(char const*, int64_t);
void string_free(string_t*);

bool string_equal(string_t*, string_t*);

char* string_data(string_t*);

int64_t string_length(string_t*);
