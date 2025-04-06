
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 栈结构用于非递归遍历
typedef struct StackNode {
    TreeNode* data;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
} Stack;

void initStack(Stack*);
int isEmptyStack(Stack*);
void push(Stack*, TreeNode*);
TreeNode* pop(Stack*);

typedef struct QueueNode {
    TreeNode* data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front, * rear;
} Queue;


void initQueue(Queue*);
int isEmptyQueue(Queue*);
void enqueue(Queue*, TreeNode*);
TreeNode* dequeue(Queue*);
TreeNode* search(TreeNode*, int);
TreeNode* insert(TreeNode*, int);
TreeNode* deleteNode(TreeNode*, int);
void preOrderRecursive(TreeNode*);
void inOrderRecursive(TreeNode*);
void postOrderRecursive(TreeNode*);
void preOrderNonRecursive(TreeNode*);
void inOrderNonRecursive(TreeNode*);
void postOrderNonRecursive(TreeNode*);
void levelOrder(TreeNode*);