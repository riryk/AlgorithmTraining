#ifndef HashTable_h
#define HashTable_h 1

struct hashtable_entry
{
    void *key, *value;
    unsigned int hash;
    struct hashtable_entry *next;
};

struct hashtable {
    unsigned int tablelength;
    struct hashtable_entry **table;
    unsigned int entrycount;
    unsigned int loadlimit;
    unsigned int primeindex;
    unsigned int (*hashfn) (void *key);
    int (*equalfn) (void *key1, void *key2);
};

struct hashtable* create_hashtable(
	unsigned int minsize,
    unsigned int (*hashfn) (void*),
    int (*equalfn) (void*,void*));

static int hashtable_expand(struct hashtable *h);

int hashtable_insert(struct hashtable *h, void *key, void *value);

void *hashtable_search(struct hashtable *h, void *key);

#endif
