#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[right]);
    return i + 1;
}

int quickSelect(int arr[], int left, int right, int k) {
    if (left <= right) {
        int pivotIndex = partition(arr, left, right);
        if (pivotIndex == k) {
            return arr[pivotIndex];
        }
        else if (pivotIndex > k) {
            return quickSelect(arr, left, pivotIndex - 1, k);
        }
        else {
            return quickSelect(arr, pivotIndex + 1, right, k);
        }
    }
    return -1; // 处理无效输入
}

int main() {
    printf("输入的数据为：5 2 8 4 3 7 6\n");
    int arr[] = { 5, 2, 8, 4, 3, 7, 6 }; // 示例数组
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3; // 找第3小的数
    int result = quickSelect(arr, 0, n - 1, k - 1); // 索引从0开始
    printf("第%d小的数是：%d\n", k, result);
    system("pause");
    return 0;
}