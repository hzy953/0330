#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "head.h"

// 插入排序
void InsertSort(int* arr, int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 归并排序辅助函数
void merge(int* arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L); free(R);
}

void MergeSort(int* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void MergeSortWrapper(int* arr, int n) {
    MergeSort(arr, 0, n - 1);
}

// 快速排序
void swap(int* a, int* b) {
    int t = *a; *a = *b; *b = t;
}

int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void QuickSort(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

void QuickSortWrapper(int* arr, int n) {
    QuickSort(arr, 0, n - 1);
}

// 计数排序
void CountSort(int* arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];
    int* count = (int*)calloc(max + 1, sizeof(int));
    for (int i = 0; i < n; i++) count[arr[i]]++;
    int idx = 0;
    for (int i = 0; i <= max; i++)
        while (count[i]--) arr[idx++] = i;
    free(count);
}

// 基数计数排序
void countSortByDigit(int* arr, int n, int exp) {
    int* output = (int*)malloc(n * sizeof(int));
    int count[10] = { 0 };
    for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
    free(output);
}

void RadixCountSort(int* arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];
    for (int exp = 1; max / exp > 0; exp *= 10)
        countSortByDigit(arr, n, exp);
}

// 生成测试数据
void generateTestData(const char* filename, int size) {
    FILE* fp;
    if (fopen_s(&fp, filename, "w") != 0 || !fp) {
        printf("无法创建文件\n");
        return;
    }
    srand((unsigned)time(NULL));
    for (int i = 0; i < size; i++)
        fprintf(fp, "%d\n", rand() % 10000); // 数据范围0-9999
    fclose(fp);
}

// 读取数据
int* readDataFromFile(const char* filename, int* n) {
    FILE* fp;
    if (fopen_s(&fp, filename, "r") != 0 || !fp) return NULL;
    int count = 0, temp;
    while (fscanf_s(fp, "%d", &temp) == 1) count++;
    rewind(fp);
    int* arr = (int*)malloc(count * sizeof(int));
    for (int i = 0; i < count; i++)
        fscanf_s(fp, "%d", &arr[i]);
    fclose(fp);
    *n = count;
    return arr;
}

// 文件排序测试
void readAndSort(const char* filename, void (*sortFunc)(int*, int), const char* sortName) {
    int n;
    int* arr = readDataFromFile(filename, &n);
    if (!arr) return;
    int* temp = (int*)malloc(n * sizeof(int));
    memcpy(temp, arr, n * sizeof(int));
    clock_t start = clock();
    sortFunc(temp, n);
    clock_t end = clock();
    printf("%s 用时: %.3f秒\n", sortName, (double)(end - start) / CLOCKS_PER_SEC);
    free(arr); free(temp);
}

// 大数据量测试
void testLargeData() {
    const int sizes[] = { 10000, 50000, 200000 };
    const char* filename = "test_large.txt";
    for (int i = 0; i < 3; i++) {
        generateTestData(filename, sizes[i]);
        int n;
        int* data = readDataFromFile(filename, &n);
        if (!data) continue;
        printf("\n数据量: %d\n", sizes[i]);
        void (*funcs[])(int*, int) = { InsertSort, MergeSortWrapper, QuickSortWrapper, CountSort, RadixCountSort };
        const char* names[] = { "插入排序", "归并排序", "快速排序", "计数排序", "基数排序" };
        for (int j = 0; j < 5; j++) {
            int* temp = (int*)malloc(n * sizeof(int));
            memcpy(temp, data, n * sizeof(int));
            clock_t start = clock();
            funcs[j](temp, n);
            clock_t end = clock();
            printf("%s: %.3f秒\n", names[j], (double)(end - start) / CLOCKS_PER_SEC);
            free(temp);
        }
        free(data);
    }
}

// 小数据量测试
void testSmallData() {
    const int size = 100, iter = 100000;
    int* data = (int*)malloc(size * sizeof(int));
    srand((unsigned)time(NULL));
    for (int i = 0; i < size; i++) data[i] = rand() % 10000;
    printf("\n小数据测试 (100元素 * 100000次):\n");
    void (*funcs[])(int*, int) = { InsertSort, MergeSortWrapper, QuickSortWrapper, CountSort, RadixCountSort };
    const char* names[] = { "插入排序", "归并排序", "快速排序", "计数排序", "基数排序" };
    for (int j = 0; j < 5; j++) {
        clock_t total = 0;
        int* temp = (int*)malloc(size * sizeof(int));
        for (int k = 0; k < iter; k++) {
            memcpy(temp, data, size * sizeof(int));
            clock_t start = clock();
            funcs[j](temp, size);
            total += clock() - start;
        }
        printf("%s: %.3f秒\n", names[j], (double)total / CLOCKS_PER_SEC);
        free(temp);
    }
    free(data);
}