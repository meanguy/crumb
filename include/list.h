#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @brief list_t is a dynamic-array data structure.
 */
typedef struct list_t {
    /*! the underlying memory buffer. */
    void** buf;
    /*! the current max size of the memory buffer. */
    int64_t capacity;
    /*! the number of elements in the @ref list_t. */
    int64_t size; 
} list_t;

/**
 * @brief list_fn is a callback function type for use with @ref list_foreach.
 * 
 * @relates list_t
 * 
 * @param elem the @ref list_t element.
 */
typedef void(list_fn)(void* elem);

/**
 * @brief list_new returns a new @ref list_t instance.
 * 
 * map_new returns a new @ref list_t instance with enough memory for storing
 * up to @p capacity values.
 * 
 * @relates list_t
 * 
 * @param capacity the initial memory buffer size.
 * 
 * @return list_t* a new @ref list_t instance.
 */
list_t* list_new(int64_t capacity);

/**
 * @brief list_copy returns a copy of @p self.
 * 
 * list_copy returns a new @ref list_t containing the same elements as
 * @p self. The underlying memory buffer is not the same as @p self,
 * meaning their lifetimes are not shared. Copying all elements in @p self
 * takes O(n) time.
 * 
 * @relates list_t
 * 
 * @param self the @ref list_t instance.
 * 
 * @return list_t* a copy of @p self.
 */
list_t* list_copy(list_t* self);

/**
 * @brief list_free frees the memory of @p self.
 * 
 * @relates list_t
 * 
 * @param self the @ref list_t instance.
 */
void list_free(list_t* self);


/**
 * @brief list_appends appends a value to the end of the @ref list_t.
 * 
 * @relates list_t
 * 
 * @param self the @ref list_t instance.
 * @param value the value to append to the list.
 * 
 * @return list_t* @p self.
 */
list_t* list_append(list_t* self, void* value);

/**
 * @brief list_clear clears all elements in @p self.
 * 
 * @relates list_t
 * 
 * @param self the @ref map_t instance.
 * 
 * @return list_t* @p self.
 */
list_t* list_clear(list_t* self);

/**
 * @brief list_extend appends the elements in @p other to @p self.
 * 
 * list_extends append the elements in @p other to @p self, taking O(n) time
 * to copy all elements.
 * 
 * @relates list_t
 * 
 * @param self the @ref list_t instance.
 * @param other the @ref list_t to append to the end of @p self.
 * 
 * @return list_t* @p self.
 */
list_t* list_extend(list_t* self, list_t* other);

/**
 * @brief list_prepend adds @p value to the beginning of the @ref list_t.
 * 
 * list_prepend adds @p value to the beginning of the @ref list_t. All other
 * elements will be shifted to the right, potentially taking O(n) time.
 * 
 * @relates list_t
 * 
 * @param self the @ref list_t instance.
 * @param value the value to prepend.
 * 
 * @return list_t* @p self.
 */
list_t* list_prepend(list_t* self, void* value);

/**
 * @brief list_resize increases the capacity of a @ref list_t.
 * 
 * list_resize increases the capacity of a @ref list_t. list_resize will never
 * decrease the capacity of a @ref list_t; instead, if @p capacity is less than
 * the current capacity, then the capacity of the @ref list_t will be unchanged.
 * 
 * @relates list_t
 * 
 * @param self the @ref list_t instance.
 * @param capacity the new capacity of the list.
 * 
 * @return list_t* @p self.
 */
list_t* list_resize(list_t* self, int64_t capacity);

/**
 * @brief list_slice returns a new @ref list_t from a subet of @p self.
 * 
 * list_slice returns a new @ref list_t containing a copy of the elements
 * in the range [@p start...@p end] from @p self. list_slice takes O(m-n)
 * time to construct the new @ref list_t.
 * 
 * @relates list_t
 * 
 * @param self the @ref list_t instance.
 * @param start the starting index of the slice.
 * @param end the ending index of the slice.
 * 
 * @return list_t* @p self.
 */
list_t* list_slice(list_t* self, int64_t start, int64_t end);


/**
 * @brief list_equal returns true if two @ref list_t instances are equal.
 * 
 * list_equal returns true if two @ref list_t instances are equal, where
 * equality is defined by identity and elements. Element comparison may take
 * O(n) time if the two @ref list_t instances are equal in elements but not
 * identity.
 * 
 * @relates list_t
 * 
 * @param lhs the @ref list_t on the left side of the comparison.
 * @param rhs the @ref list_t on the right side of the comparison.
 * 
 * @return bool true if the identity or elements of @p lhs and @p rhs are 
 * equal, else false.
 */
bool list_equal(list_t* lhs, list_t* rhs);


/**
 * @brief list_capacity returns the current maximum capacity of a @ref list_t.
 * 
 * @relates list_t
 * 
 * @param self the @ref list_t instance.
 * 
 * @return int64_t the current maximum capacity of @p self.
 */
int64_t list_capacity(list_t* self);

/**
 * @brief list_find returns the index of @p value in @p self, if found.
 * 
 * list_find returns the index of @p value in @p self, or -1 if @p value
 * is not found.
 * 
 * @relates list_t
 * 
 * @param self the @ref list_t instance.
 * @param value the value to search for.
 * 
 * @return int64_t the index of @p value in @p or -1 if not found.
 */
int64_t list_find(list_t* self, void* value);

/**
 * @brief list_size returns the number of elements in a @ref list_t.
 * 
 * @relates list_t
 * 
 * @param self the @ref list_t instance.
 * 
 * @return int64_t the number of elements in @p self.
 */
int64_t list_size(list_t* self);


/**
 * @brief list_get returns the element found at the given @p index.
 * 
 * list_get returns the element found at the given @p index, or -1 if @p index
 * is out of bounds.
 * 
 * @relates list_t
 * 
 * @param self the @ref list_t instance.
 * @param index the index of the element to get.
 * 
 * @return void* the element at @p index, or NULL if out of bounds.
 */
void* list_get(list_t* self, int64_t index);

/**
 * @brief list_insert adds an element at the given index.
 * 
 * list_insert adds an element at the given index, returning the inserted 
 * @p value if @p index is within the @ref list_t bounds, else NULL. Elements
 * after @p index will be shifted to the right, potentially taking O(n) time.
 * 
 * @relates list_t
 * 
 * @param self the @ref list_t instance.
 * @param index the index to insert the element at.
 * @param value the value to insert.
 * 
 * @return void* @p value if @p index is in bounds, else NULL.
 */
void* list_insert(list_t* self, int64_t index, void* value);

/**
 * @brief list_pop removes and returns the value at @p index.
 * 
 * list_pop removes and returns the value at @p index if @p index is in
 * bounds, else NULL. Elements after @p index will be shifted to the left,
 * potentially take O(n) time.
 * 
 * @relates list_t
 * 
 * @param self the @ref list_t instance.
 * @param index the index to pop the element at.
 * 
 * @return void* the value at @p index if @p index is in bounds, else NULL.
 */
void* list_pop(list_t* self, int64_t index);

/**
 * @brief list_remove removes and returns @p value from a @ref list_t if found.
 * 
 * list_remove removes a @p value from @p self, and returns the @p value. If
 * @p value is not found, NULL is returned instead. Elements after the removed
 * element will be shifted to the left, potentially taking O(n) time.
 * 
 * @relates list_t
 * 
 * @param self the @ref list_t instance.
 * @param value the value to remove from @p self.
 * 
 * @return list_t* 
 */
void* list_remove(list_t* self, void* value);

/**
 * @brief list_set sets the element at @p index to @p value, returning @p value.
 * 
 * list_set sets the element at @p index to @p value, returning @p value or
 * NULL if @p index is out of bounds.
 * 
 * @relates list_t
 * 
 * @param self the @ref list_t instance.
 * @param index the index of the element to set.
 * @param value the new value of the element.
 * 
 * @return void* @p value if @p index is in bounds else NULL.
 */
void* list_set(list_t* self, int64_t index, void* value);


/**
 * @brief list_fprint writes a string representation of a @ref list_t to @p stream.
 * 
 * @relates list_t
 * 
 * @param self the @ref list_t instance.
 * @param stream the stream to write to.
 */
void list_fprint(list_t* self, FILE* stream);

/**
 * @brief list_foreach calls a function with each element in a @ref list_t.
 * 
 * @relates list_t
 * 
 * @param self the @ref list_t instance.
 * @param fn the function to call.
 */
void list_foreach(list_t* self, list_fn fn);
