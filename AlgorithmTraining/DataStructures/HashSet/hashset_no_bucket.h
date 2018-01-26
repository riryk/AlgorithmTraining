#ifndef HashSetNoBucket_h
#define HashSetNoBucket_h 1

struct HashSetNoBucketsData {
   size_t bitsNumber;
   size_t mask;

   size_t capacity;
   size_t *items;
   size_t itemsNumber;
   size_t itemsDeletedNumber;
};

typedef struct HashSetNoBucketsData *HashSetNoBuckets;

HashSetNoBuckets hashset_create(void);

void hashset_destroy(HashSetNoBuckets set);

int hashset_add(HashSetNoBuckets set, void *item);

int hashset_remove(HashSetNoBuckets set, void *item);

int hashset_is_member(HashSetNoBuckets set, void *item);

#endif
