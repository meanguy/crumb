#pragma once

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief string_t is a string data structure.
 * 
 */
typedef struct string_t {
    /*! the underlying memory buffer. */
    char* buf;
    /*! the length of the string. */
    int64_t length;
} string_t;

/**
 * @brief string returns a new @ref string_t instance.
 * 
 * string returns a new @ref string_t with enough memory for storing
 * @p length characters.
 * 
 * @relates string_t
 * 
 * @param str the raw string data to store.
 * @param length the length of the string.
 * 
 * @return string_t* a new @ref string_t instance.
 */
string_t* string(char const* str, int64_t length);

/**
 * @brief string_copy returns a copy of @p self.
 * 
 * list_copy returns a new @ref string_t containing the same characters
 * as @p self. The underlying memory buffer is not the same as @p self,
 * meaning their lifetimes are not shared. Copying all characters in @p self
 * takes O(n) time.
 * 
 * @relates string_t
 * 
 * @param self the @ref string_t instance.
 * 
 * @return string_t* a copy of @p self.
 */
string_t* string_copy(string_t* self);

/**
 * @brief list_free frees the memory of @p self.
 * 
 * @relates string_t
 * 
 * @param self the @ref string_t instance.
 */
void string_free(string_t* self);

/**
 * @brief string_equal returns true if two @ref string_t instances are equal.
 * 
 * string_equal returns true if two @ref string_t instances are equal, where
 * equality is defined by identity and data. Data comparison may take O(n)
 * time if the two @ref string_t instances are equal in data but not identity.
 * 
 * @relates string_t
 * 
 * @param lhs the @ref string_t on the left side of the comparison.
 * @param rhs the @ref string_t on the right side of the comparison.
 * 
 * @return bool true if the identity or data of @p lhs and @p rhs are 
 * equal, else false.
 */
bool string_equal(string_t* lhs, string_t* rhs);

/**
 * @brief string_data returns the underlying memory buffer of @p self.
 * 
 * @relates string_t
 * 
 * @param self the @ref string_t instance.
 * 
 * @return char* the underlying memory buffer owned by @p self.
 */
char* string_data(string_t* self);

/**
 * @brief string_length returns the length of the string data.
 * 
 * @relates string_t
 * 
 * @param self the @ref string_t instance.
 * 
 * @return int64_t the length of the data in @p self.
 */
int64_t string_length(string_t* self);
