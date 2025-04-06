#include <stdio.h>
#include <stdlib.h>
#include "head.h"



void initStack(Stack* s) {
    s->top = NULL;
}

int isEmptyStack(Stack* s) {
    return s->top == NULL;
}

void push(Stack* s, TreeNode* node) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = node;
    newNode->next = s->top;
    s->top = newNode;
}

TreeNode* pop(Stack* s) {
    if (isEmptyStack(s)) return NULL;
    StackNode* temp = s->top;
    TreeNode* data = temp->data;
    s->top = temp->next;
    free(temp);
    return data;
}

void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

int isEmptyQueue(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, TreeNode* node) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = node;
    newNode->next = NULL;
    if (isEmptyQueue(q)) {
        q->front = q->rear = newNode;
    }
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

TreeNode* dequeue(Queue* q) {
    if (isEmptyQueue(q)) return NULL;
    QueueNode* temp = q->front;
    TreeNode* data = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return data;
}

TreeNode* search(TreeNode* root, int key) {
    while (root) {
        if (key == root->data) return root;
        root = key < root->data ? root->left : root->right;
    }
    return NULL;
}

TreeNode* insert(TreeNode* root, int key) {
    if (!root) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = key;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    return root;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return NULL;
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    }
    else {
        if (!root->left) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (!root->right) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        TreeNode* temp = root->right;
        while (temp->left) temp = temp->left;
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// µÝ¹é±éÀú
void preOrderRecursive(TreeNode* root) {
    if (root) {
        printf("%d ", root->data);
        preOrderRecursive(root->left);
        preOrderRecursive(root->right);
    }
}

void inOrderRecursive(TreeNode* root) {
    if (root) {
        inOrderRecursive(root->left);
        printf("%d ", root->data);
        inOrderRecursive(root->right);
    }
}

void postOrderRecursive(TreeNode* root) {
    if (root) {
        postOrderRecursive(root->left);
        postOrderRecursive(root->right);
        printf("%d ", root->data);
    }
}

// ·ÇµÝ¹é±éÀú
void preOrderNonRecursive(TreeNode* root) {
    if (!root) return;
    Stack s;
    initStack(&s);
    push(&s, root);
    while (!isEmptyStack(&s)) {
        TreeNode* node = pop(&s);
        printf("%d ", node->data);
        if (node->right) push(&s, node->right);
        if (node->left) push(&s, node->left);
    }
}

void inOrderNonRecursive(TreeNode* root) {
    Stack s;
    initStack(&s);
    TreeNode* curr = root;
    while (curr || !isEmptyStack(&s)) {
        while (curr) {
            push(&s, curr);
            curr = curr->left;
        }
        curr = pop(&s);
        printf("%d ", curr->data);
        curr = curr->right;
    }
}

void postOrderNonRecursive(TreeNode* root) {
    if (!root) return;
    Stack s1, s2;
    initStack(&s1);
    initStack(&s2);
    push(&s1, root);
    while (!isEmptyStack(&s1)) {
        TreeNode* node = pop(&s1);
        push(&s2, node);
        if (node->left) push(&s1, node->left);
        if (node->right) push(&s1, node->right);
    }
    while (!isEmptyStack(&s2)) {
        printf("%d ", pop(&s2)->data);
    }
}

// ²ãÐò±éÀú
void levelOrder(TreeNode* root) {
    if (!root) return;
    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    while (!isEmptyQueue(&q)) {
        TreeNode* node = dequeue(&q);
        printf("%d ", node->data);
        if (node->left) enqueue(&q, node->left);
        if (node->right) enqueue(&q, node->right);
    }
}