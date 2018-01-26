#include "stdafx.h"
#include "hashset.h"

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