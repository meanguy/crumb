#include "map.h"

#include <stdlib.h>

#include "xxhash.h"

#include "cstrings.h"
#include "tuple.h"

#define CRUMB_MAP_SEED 4374805547167856529

void list_foreach_tuple_free_fn(void* elem) {
    tuple_t* self = (tuple_t*) elem;
    string_t* key = (string_t*) self->first;

    string_free(key);
    tuple_free(self);
}

void list_foreach_tuple_list_free_fn(void* elem) {
    list_t* self = (list_t*) elem;

    list_foreach(self, list_foreach_tuple_free_fn);
    list_free(self);
}

uint64_t map_hash_key(map_t* self, string_t* key) {
    return XXH64(string_data(key), string_length(key), CRUMB_MAP_SEED) % list_size(self->buckets);
}

map_t* map_new(int64_t bucket_count, int64_t bucket_capacity) {
    map_t* self = malloc(sizeof(map_t*));
    self->buckets = list_new(bucket_count);

    for (int64_t n = 0; n < bucket_count; ++n) {
        self->buckets = list_append(self->buckets, list_new(bucket_capacity));
    }

    return self;
}

map_t* map_copy(map_t* self, int64_t bucket_count, int64_t bucket_capacity) {
    map_t* other = map_new(bucket_count, bucket_capacity);

    for (int64_t b = 0; b < list_size(self->buckets); ++b) {
        list_t* bucket = list_get(self->buckets, b);

        for (int64_t p = 0; p < list_size(bucket); ++p) {
            tuple_t* pair = (tuple_t*) list_get(bucket, p);

            other = map_set(other, (string_t*) pair->first, pair->second);
        }
    }

    return other;
}

void map_free(map_t* self) {
    list_foreach(self->buckets, list_foreach_tuple_list_free_fn);
    list_free(self->buckets);
    free(self);
}

map_t* map_clear(map_t* self) {
    int64_t bucket_count = list_size(self->buckets);
    int64_t bucket_capacity = 0;

    if (bucket_count > 0) {
        bucket_capacity = list_capacity((list_t*) list_get(self->buckets, 0));
    }

    for (int64_t n = 0; n < bucket_count; ++n) {
        list_t* bucket = list_get(self->buckets, n);

        list_foreach(bucket, list_foreach_tuple_free_fn);
        list_free(bucket);
    }
    list_free(self->buckets);

    self->buckets = list_new(bucket_count);
    for (int64_t n = 0; n < bucket_count; ++n) {
        self->buckets = list_append(self->buckets, list_new(bucket_capacity));
    }

    return self;
}

map_t* map_set(map_t* self, string_t* key, void* value) {
    list_t* bucket = list_get(self->buckets, map_hash_key(self, key));

    for (int64_t index = 0; index < list_size(bucket); ++index) {
        tuple_t* pair = list_get(bucket, index);

        if (string_equal(key, (string_t*) pair->first)) {
            // cleanup the old key-value pair
            string_free((string_t*) pair->first);
            tuple_free(pair);

            list_set(bucket, index, tuple_new(string_copy(key), value));

            return self;
        }
    }

    list_append(bucket, tuple_new(string_copy(key), value));

    return self;
}

bool map_equal(map_t* lhs, map_t* rhs) {
    if (lhs == rhs) {
        return true;
    }

    for (int n = 0; n < list_size(lhs->buckets); ++n) {
        list_t* bucket = list_get(lhs->buckets, n);

        for (int p = 0; p < list_size(bucket); ++p) {
            tuple_t* pair = list_get(bucket, p);
            string_t* key = pair->first;

            void* value = map_get(rhs, key);
            if (value != pair->second) {
                return false;
            }
        }
    }

    for (int n = 0; n < list_size(rhs->buckets); ++n) {
        list_t* bucket = list_get(rhs->buckets, n);

        for (int p = 0; p < list_size(bucket); ++p) {
            tuple_t* pair = list_get(bucket, p);
            string_t* key = pair->first;

            void* value = map_get(lhs, key);
            if (value != pair->second) {
                return false;
            }
        }
    }

    return true;
}

void* map_delete(map_t* self, string_t* key) {
    list_t* bucket = list_get(self->buckets, map_hash_key(self, key));

    for (int n = 0; n < list_size(bucket); ++n) {
        tuple_t* pair = list_get(bucket, n);

        if (string_equal(key, (string_t*) pair->first)) {
            void* elem = pair->second;
            bucket = list_remove(bucket, pair);

            string_free((string_t*) pair->first);
            tuple_free(pair);

            return elem;
        }
    }

    return NULL;
}

void* map_get(map_t* self, string_t* key) {
    list_t* bucket = list_get(self->buckets, map_hash_key(self, key));

    for (int64_t n = 0; n < list_size(bucket); ++n) {
        tuple_t* pair = list_get(bucket, n);

        if (string_equal(key, (string_t*) pair->first)) {
            return pair->second;
        }
    }

    return NULL;
}
