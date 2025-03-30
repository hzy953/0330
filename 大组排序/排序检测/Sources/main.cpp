#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "head.h"

int main() {
    while (1) {
        int choice;
        printf("ѡ��ģʽ��1���ɲ������ݣ�2���в��ԣ�3��ȡ�ļ�������\n");
        scanf_s("%d", &choice);
        if (choice == 1) {
            char filename[100];
            int size;
            printf("�����ļ����ʹ�С��");
            scanf_s("%s %d", filename, (unsigned)_countof(filename), &size);
            generateTestData(filename, size);
            printf("������");
        }
        else if (choice == 2) {
            testLargeData();
            testSmallData();

        }
        else if (choice == 3) {
            char filename[100];
            printf("�����ļ�����");
            scanf_s("%s", filename, (unsigned)_countof(filename));
            printf("ѡ�������㷨��1���룬2�鲢��3���ţ�4������5����\n");
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
            default: printf("��Чѡ��\n"); return 0;
            }
            readAndSort(filename, sortFunc, name);
        }
        system("pause");
    }
    return 0;
}
