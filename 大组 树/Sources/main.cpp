#include <stdio.h>
#include <stdlib.h>
#include "head.h"

int main() {
    TreeNode* root = NULL;
    int choice, val;
    do {
        printf("\n���������������˵���\n");
        printf("1. ����ڵ�\n2. ɾ���ڵ�\n3. ���ҽڵ�\n");
        printf("4. �ݹ�ǰ�����\n5. �ǵݹ�ǰ�����\n6. �ݹ��������\n");
        printf("7. �ǵݹ��������\n8. �ݹ�������\n9. �ǵݹ�������\n");
        printf("10. �������\n11. �˳�\nѡ�������");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("����Ҫ�����ֵ��");
            scanf_s("%d", &val);
            root = insert(root, val);
            break;
        case 2:
            printf("����Ҫɾ����ֵ��");
            scanf_s("%d", &val);
            root = deleteNode(root, val);
            break;
        case 3:
            printf("����Ҫ���ҵ�ֵ��");
            scanf_s("%d", &val);
            printf(search(root, val) ? "�ҵ��ڵ�\n" : "δ�ҵ��ڵ�\n");
            break;
        case 4:
            printf("ǰ��������ݹ飩��");
            preOrderRecursive(root);
            break;
        case 5:
            printf("ǰ��������ǵݹ飩��");
            preOrderNonRecursive(root);
            break;
        case 6:
            printf("����������ݹ飩��");
            inOrderRecursive(root);
            break;
        case 7:
            printf("����������ǵݹ飩��");
            inOrderNonRecursive(root);
            break;
        case 8:
            printf("����������ݹ飩��");
            postOrderRecursive(root);
            break;
        case 9:
            printf("����������ǵݹ飩��");
            postOrderNonRecursive(root);
            break;
        case 10:
            printf("���������");
            levelOrder(root);
            break;
        case 11:
            printf("�����˳���\n");
            break;
        default:
            printf("��Ч���룡\n");
        }
        printf("\n");
    } while (choice != 11);

    return 0;
}