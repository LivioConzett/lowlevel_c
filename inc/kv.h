#ifndef KV_H
#define KV_H

#include <stdlib.h>

typedef struct {
    char* key;
    char* value;
} kv_entry_t;

typedef struct{
    size_t capacity;
    size_t count;
    kv_entry_t* entries;
} kv_t;

/**
 * \brief initializes a key value database
 * \param capacity how many entries should be stored 
 * \return pointer to the db. On error: Null
 */
kv_t* kv_init(size_t capacity);

/**
 * \brief Adds a key value pair into a kv db
 * \param db the database to put the kv pair into
 * \param key the key to use 
 * \param value the value to use
 * \return the index of the key. On error: -1. On not found: -2
 */
int kv_put(kv_t* db, char* key, char* value);
void kv_free(kv_t* db);

#endif 