// ÅÅĞòËã·¨º¯ÊıÉùÃ÷
void InsertSort(int* arr, int n);
void MergeSort(int* arr, int l, int r);
void MergeSortWrapper(int* arr, int n);
void QuickSort(int* arr, int low, int high);
void QuickSortWrapper(int* arr, int n);
void CountSort(int* arr, int n);
void RadixCountSort(int* arr, int n);
void generateTestData(const char* filename, int size);
void readAndSort(const char* filename, void (*sortFunc)(int*, int), const char* sortName);
int* readDataFromFile(const char* filename, int* n);
void testLargeData();
void testSmallData();
void swap(int* a, int* b);
int partition(int* arr, int low, int high);
void merge(int* arr, int l, int m, int r);
void countSortByDigit(int* arr, int n, int exp);

