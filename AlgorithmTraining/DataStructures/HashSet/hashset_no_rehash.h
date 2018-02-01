#ifndef HashSet_NoRehash_h
#define HashSet_NoRehash_h 1

typedef int (*HashSetHashFunction)(const void *elementAddress, int numberOFBuckets);

typedef int (*HashSetCompareFunction)(const void *elementAddress1, const void *elementAddress2);

typedef void (*HashSetMapFunction)(void *elementAddress, void *auxiliaryData);

typedef void (*HashSetFreeFunction)(void *elemenetAddress);

typedef struct {
  int elementSize;
  int numberOfBuckets;
  int numberOfElements;
  void *buckets;
  HashSetHashFunction hashFunc;
  HashSetCompareFunction compareFunc;
  HashSetFreeFunction freeFunc;
} hashset;

void hashSetCreateNew(hashset *set, int elementSize, int numberOfBuckets, 
		HashSetHashFunction hashFunc, HashSetCompareFunction compareFunc, HashSetFreeFunction freeFunc);

void hashSetDispose(hashset *hashset);

int hashSetCount(const hashset *hashset);

void hashSetEnter(hashset *hashset, const void *elementAddress);

void *hashSetLookup(const hashset *hashset, const void *elementAddress);

void hashSetMap(hashset *hashset, HashSetMapFunction mapFunc, void *auxiliaryData);

void *hashSetLookup(const hashset *set, const void *elementAddress);

#endif
