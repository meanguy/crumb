#pragma once

#include "list.h"
#include "strings.h"

typedef struct {
    list_t* buckets;
} map_t;

/**
 * @brief map_new returns a new \ref map_t with \p bucket_count buckets with
 * \p bucket_capacity initial capacity. 
 * 
 * @param bucket_count the number of buckets for storing key-value pairs.
 * @param bucket_capacity the initial capacity for each bucket.
 * 
 * @return map_t* a new \ref map_t instance.
 */
map_t* map_new(int64_t, int64_t);

/**
 * @brief map_copy returns a new \ref map_t containing the same key-value 
 * pairs as \p self. \p bucket_count and \p bucket_capacity are used for
 * creating the new \ref map_t.
 * 
 * @param self the \ref map_t instance.
 * @param bucket_count the number of buckets for storing key-value pairs.
 * @param bucket_capacity the initial capacity for each bucket.
 * 
 * @return map_t* a copy of \p self.
 */
map_t* map_copy(map_t*, int64_t, int64_t);

/**
 * @brief map_free frees the memory of \p self.
 * 
 * @param self the \ref map_t instance.
 */
void map_free(map_t*);

/**
 * @brief map_clear clears all buckets in \p self, freeing any stored 
 * key-value pairs.
 * 
 * @param self the \ref map_t instance.
 * 
 * @return map_t* \p self.
 */
map_t* map_clear(map_t*);

/**
 * @brief map_set adds a key-value pair to the \ref map_t instance.
 * 
 * @param self the \ref map_t instance.
 * @param key the key for the key-value pair.
 * @param value the value for the key-value pair.
 * 
 * @return map_t* \p self.
 */
map_t* map_set(map_t*, string_t*, void*);


/**
 * @brief map_delete removes the key-value pair matching \p key, returning
 * the value if \p key matches a key-value pair, else NULL.
 * 
 * @param self the \ref map_t instance.
 * @param key the key to search for deletion.
 * 
 * @return void* the value matching \p if found, else NULL.
 */
void* map_delete(map_t*, string_t*);

/**
 * @brief map_get returns the key-value pair matching the given \p key,
 * else NULL if no match was found.
 * 
 * @param self the \ref map_t instance.
 * @param key the key to lookup.
 * 
 * @return void* 
 */
void* map_get(map_t*, string_t*);
