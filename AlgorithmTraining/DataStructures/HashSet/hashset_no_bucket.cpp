#include "stdafx.h"
#include "hashset_no_bucket.h"
#include <cstddef>
#include <stdlib.h>

static const unsigned int primeFirst = 73;
static const unsigned int primeSecond = 5009;

int hashset_add_member(HashSet set, void *item);
void rehash_if_too_large(HashSet set);

HashSet hashset_create()
{
    HashSet set = (HashSet)calloc(1, sizeof(struct HashSetData));
    if (set == NULL) {
        return NULL;
    }

	set->bitsNumber = 3;
	set->capacity = (size_t)(1 << set->bitsNumber);
    set->mask = set->capacity - 1;
	set->items = (size_t*)calloc(set->capacity, sizeof(size_t));
    if (set->items == NULL) {
        hashset_destroy(set);
        return NULL;
    }

	set->bitsNumber = 0;
	set->itemsDeletedNumber = 0;
    return set;
}

void hashset_destroy(HashSet set)
{
    if (set) {
        free(set->items);
    }

    free(set);
}

int hashset_add(HashSet set, void *item)
{
    int addResult = hashset_add_member(set, item);
    rehash_if_too_large(set);
    return addResult;
}

int hashset_remove(HashSet set, void *item)
{
    size_t value = (size_t)item;
    size_t i = set->mask & (primeFirst * value);

    while (set->items[i] != 0) {
        if (set->items[i] == value) {
            set->items[i] = 1;
			set->itemsNumber--;
			set->itemsDeletedNumber++;
            return 1;
        }

        i = set->mask & (i + primeSecond);
    }

    return 0;
}

int hashset_is_member(HashSet set, void *item)
{
    size_t value = (size_t)item;
    size_t i = set->mask & (primeFirst * value);

    while (set->items[i] != 0) {
        if (set->items[i] == value) {
            return 1;
        }

        i = set->mask & (i + primeSecond);
    }

    return 0;
}

int hashset_add_member(HashSet set, void *item)
{
    size_t value = (size_t)item;
    size_t i;

    if (value == 0 || value == 1) {
        return -1;
    }

    i = set->mask & (primeFirst * value);

    while (set->items[i] != 0 && set->items[i] != 1) {
        if (set->items[i] == value) {
            return 0;
        } 

        i = set->mask & (i + primeSecond);
    }

	set->itemsNumber++;
    if (set->items[i] == 1) {
		set->itemsDeletedNumber--;
    }

    set->items[i] = value;
    return 1;
}

void rehash_if_too_large(HashSet set)
{
    size_t *oldItems;
    size_t oldCapacity, i;

	if (set->itemsNumber + set->itemsDeletedNumber >= (double)set->capacity * 0.85) {
        oldItems = set->items;
        oldCapacity = set->capacity;

		set->bitsNumber++;
		set->capacity = (size_t)(1 << set->bitsNumber);
        set->mask = set->capacity - 1;
        set->items = (size_t*)calloc(set->capacity, sizeof(size_t));
		set->itemsNumber = 0;
		set->itemsDeletedNumber = 0;

        for (i = 0; i < oldCapacity; i++) {
            hashset_add_member(set, (void*)oldItems[i]);
        }

        free(oldItems);
    }
}