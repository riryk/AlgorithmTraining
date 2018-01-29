#ifndef HashSet_h
#define HashSet_h 1

typedef int (*HashSetHashFunction)(const void *elementAddress, int numberOFBuckets);

typedef int (*HashSetCompareFunction)(const void *elementAddress1, const void *elementAddress2);

typedef void (*HashSetMapFunction)(void *elementAddress, void *auxiliaryData);

typedef void (*HashSetFreeFunction)(void *elemenetAddress);

typedef struct {
  int elementSize;
  int numberOfBuckets;
  int numberOfElements;
  void *buckets;
  HashSetHashFunction hashFunction;
  HashSetCompareFunction compareFunction;
  HashSetFreeFunction freeFunction;
} hashset;

void hashSetCreateNew(hashset *hashset, int elementSize, int numberOfBuckets, 
		HashSetHashFunction hashFunc, HashSetCompareFunction compareFunc, HashSetFreeFunction freeFunc);

void hashSetDispose(hashset *hashset);

int hashSetCount(const hashset *hashset);

void hashSetEnter(hashset *hashset, const void *elementAddress);

void *hashSetLookup(const hashset *hashset, const void *elementAddress);

void hashSetMap(hashset *hashset, HashSetMapFunction mapFunc, void *auxiliaryData);

#endif
