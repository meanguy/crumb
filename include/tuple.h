#pragma once

/**
 * @brief tuple_t is a data structure for storing a pair of values.
 * 
 */
typedef struct tuple_t {
    /*! the first element in the pair. */
    void* first;
    /*! the second element in the pair. */
    void* second;
} tuple_t;

/**
 * @brief tuple_new returns a new @ref tuple_t of the given pair @p first
 * and @p second.
 * 
 * @param first the first value in the pair.
 * @param second the second value in the pair.
 * 
 * @return tuple_t* a new @ref tuple_t instance.
 */
tuple_t* tuple_new(void* first, void* second);

/**
 * @brief tuple_copy returns a new @ref tuple_t containing the same key-value
 * pairs as @p self.
 * 
 * @param self the @ref tuple_t instance.
 * 
 * @return tuple_t* a copy of @p self.
 */
tuple_t* tuple_copy(tuple_t* self);

/**
 * @brief tuple_free frees the memory of @p self.
 * 
 * @param self the @ref tuple_t instance.
 * 
 */
void tuple_free(tuple_t* self);
