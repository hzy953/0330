#include <stdio.h>
#include <stdlib.h>


void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sortColors(int* nums, int numsSize) {
    int p0 = 0, current = 0;
    int p2 = numsSize - 1;

    while (current <= p2) {
        if (nums[current] == 0) {
            swap(&nums[current], &nums[p0]);
            p0++;
            current++;
        }
        else if (nums[current] == 2) {
            swap(&nums[current], &nums[p2]);
            p2--;
        }
        else {
            current++;
        }
    }
}

// 示例测试代码
int main() {
    int N = 10;
    printf("请输入10个数（介于0，1，2之间）：");
    int arr[10];
    for (int i = 0;i < N;i++)
    {
        scanf_s("%d", &arr[i]);
    }
    int n = sizeof(arr) / sizeof(arr[0]);
    sortColors(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    system("pause");
    return 0;
}