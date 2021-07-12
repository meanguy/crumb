#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "strings.h"

void list_foreach_fprintf(void* elem) {
    fprintf(stdout, "%s\n", string_data((string_t*) elem));
}

void list_foreach_string_free(void* elem) {
    string_free((string_t*) elem);
}

int main(int argc, char** argv) {
    list_t* l = list_new(8);
    l = list_append(
            list_append(l, string("hello", 6)),
            string("world", 6));
    list_fprint(l, stdout);

    l = list_append(l, string("fizz", 5));
    list_fprint(l, stdout);

    fprintf(stdout, "%ld\n", list_find(l, list_get(l, 0)));

    string_free((string_t*) list_get(l, 0));
    list_remove(l, list_get(l, 0));
    list_fprint(l, stdout);

    list_foreach(l, list_foreach_fprintf);

    list_foreach(l, list_foreach_string_free);
    list_free(l);

    return 0;
}
