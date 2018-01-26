#ifndef HashSet_h
#define HashSet_h 1

struct HashSetData {
   size_t bitsNumber;
   size_t mask;

   size_t capacity;
   size_t *items;
   size_t itemsNumber;
   size_t itemsDeletedNumber;
};

typedef struct HashSetData *HashSet;

HashSet hashset_create(void);

void hashset_destroy(HashSet set);

int hashset_add(HashSet set, void *item);

int hashset_remove(HashSet set, void *item);

int hashset_is_member(HashSet set, void *item);

#endif
