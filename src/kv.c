
#include "kv.h"
#include <string.h>
#include <stdlib.h>

#define TOMBSTONE 0x1

/**
 * \brief hashes a value. Make sure it isn't larger than capacity.
 * \param value value to hash
 * \param capacity max capacity of db to put the kv entry into
 * \return the hashed value
 */
size_t hash(char* value, int capacity){
    size_t hash = 0x13371337deadbeef;

    // string is terminated with 0
    // so go until the value has hit the 0
    while(*value) {
        hash ^= *value;
        hash = hash << 8;
        hash += *value;

        // increment the pointer
        value++;
    }

    return hash % capacity;
}

/**
 * See header file
 */
int kv_put(kv_t* db, char* key, char* value){
    if(!db || !key || !value) return -1;

    size_t index = hash(key, db->capacity);

    for(int i = 0; i < db->capacity - 1; i++){
        
        size_t real_index = (index + i) % db->capacity;
        kv_entry_t* entry = &db->entries[real_index];

        // the key is already set. updating
        if(entry->key && (entry->key != (void*)TOMBSTONE || strcmp(entry->key, key))){

            char* newvalue = strdup(value);
            if(!newvalue) return -1;

            entry->value = newvalue;
            return 0;
        }

        // land on slot that is "empty"
        // null or tombstone
        if(!entry->key || entry->key == (void*)TOMBSTONE) {
            char* newkey = strdup(key);
            char* newvalue = strdup(value);
            if(!newkey || !newkey) {
                free(newkey);
                free(newvalue);
                return -1;
            }

            entry->key = newkey;
            entry->value = newvalue;

            db->count++;
            return 0;
        }
    }

    // database is full 
    return -2;
}


/**
 * See header file
 */
kv_t* kv_init(size_t capacity){
    if(capacity == 0) return NULL;

    kv_t* table = malloc(sizeof(kv_t));
    if(table == NULL){
        return NULL;
    }

    table->capacity = capacity;
    table->count = 0;

    table->entries = calloc(sizeof(kv_entry_t), capacity);
    if(table->entries == NULL){
        free(table);
        return NULL;
    }

    return table;
}

void kv_free(kv_t* db){
    free(db);
}