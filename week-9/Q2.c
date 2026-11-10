#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int height(Node* node) {
    if (node == NULL) return 0;
    int leftH = height(node->left);
    int rightH = height(node->right);
    return (leftH > rightH ? leftH : rightH) + 1;
}

int balanceFactor(Node* node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}


Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    return x; 
}


Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    return y; 
}


Node* insertAVL(Node* node, int data) {
    if (node == NULL) {
        return createNode(data);
    }
    if (data < node->data) {
        node->left = insertAVL(node->left, data);
    } else if (data > node->data) {
        node->right = insertAVL(node->right, data);
    } else {
        return node; 
    }


    int bf = balanceFactor(node);

    if (bf > 1 && data < node->left->data) {
        return rotateRight(node);
    }


    if (bf < -1 && data > node->right->data) {
        return rotateLeft(node);
    }

 
    if (bf > 1 && data > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (bf < -1 && data < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void runTest(const char* testName, int arr[], int n) {
    Node* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insertAVL(root, arr[i]);
    }
    printf("Test %s -> Kok: %d | Preorder: ", testName, root->data);
    preorder(root);
    printf("\n");
}

int main() {
    int testA[] = {30, 20, 10};
    int testB[] = {10, 20, 30};
    int testC[] = {30, 10, 20};
    int testD[] = {10, 30, 20};

    runTest("A (LL)", testA, 3);
    runTest("B (RR)", testB, 3);
    runTest("C (LR)", testC, 3);
    runTest("D (RL)", testD, 3);

    return 0;
}