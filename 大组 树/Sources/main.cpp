#include <stdio.h>
#include <stdlib.h>
#include "head.h"

int main() {
    TreeNode* root = NULL;
    int choice, val;
    do {
        printf("\n二叉排序树操作菜单：\n");
        printf("1. 插入节点\n2. 删除节点\n3. 查找节点\n");
        printf("4. 递归前序遍历\n5. 非递归前序遍历\n6. 递归中序遍历\n");
        printf("7. 非递归中序遍历\n8. 递归后序遍历\n9. 非递归后序遍历\n");
        printf("10. 层序遍历\n11. 退出\n选择操作：");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("输入要插入的值：");
            scanf_s("%d", &val);
            root = insert(root, val);
            break;
        case 2:
            printf("输入要删除的值：");
            scanf_s("%d", &val);
            root = deleteNode(root, val);
            break;
        case 3:
            printf("输入要查找的值：");
            scanf_s("%d", &val);
            printf(search(root, val) ? "找到节点\n" : "未找到节点\n");
            break;
        case 4:
            printf("前序遍历（递归）：");
            preOrderRecursive(root);
            break;
        case 5:
            printf("前序遍历（非递归）：");
            preOrderNonRecursive(root);
            break;
        case 6:
            printf("中序遍历（递归）：");
            inOrderRecursive(root);
            break;
        case 7:
            printf("中序遍历（非递归）：");
            inOrderNonRecursive(root);
            break;
        case 8:
            printf("后序遍历（递归）：");
            postOrderRecursive(root);
            break;
        case 9:
            printf("后序遍历（非递归）：");
            postOrderNonRecursive(root);
            break;
        case 10:
            printf("层序遍历：");
            levelOrder(root);
            break;
        case 11:
            printf("程序退出。\n");
            break;
        default:
            printf("无效输入！\n");
        }
        printf("\n");
    } while (choice != 11);

    return 0;
}