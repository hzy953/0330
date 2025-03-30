#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "head.h"

int main() {
    while (1) {
        int choice;
        printf("选择模式：1生成测试数据，2运行测试，3读取文件并排序\n");
        scanf_s("%d", &choice);
        if (choice == 1) {
            char filename[100];
            int size;
            printf("输入文件名和大小：");
            scanf_s("%s %d", filename, (unsigned)_countof(filename), &size);
            generateTestData(filename, size);
            printf("已生成");
        }
        else if (choice == 2) {
            testLargeData();
            testSmallData();

        }
        else if (choice == 3) {
            char filename[100];
            printf("输入文件名：");
            scanf_s("%s", filename, (unsigned)_countof(filename));
            printf("选择排序算法：1插入，2归并，3快排，4计数，5基数\n");
            int algo;
            scanf_s("%d", &algo);
            void (*sortFunc)(int*, int) = NULL;
            const char* name = "";
            switch (algo) {
            case 1: sortFunc = InsertSort; name = "InsertSort"; break;
            case 2: sortFunc = MergeSortWrapper; name = "MergeSort"; break;
            case 3: sortFunc = QuickSortWrapper; name = "QuickSort"; break;
            case 4: sortFunc = CountSort; name = "CountSort"; break;
            case 5: sortFunc = RadixCountSort; name = "RadixCountSort"; break;
            default: printf("无效选择\n"); return 0;
            }
            readAndSort(filename, sortFunc, name);
        }
        system("pause");
    }
    return 0;
}
