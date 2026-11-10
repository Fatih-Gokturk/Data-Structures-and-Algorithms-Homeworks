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


Node* insertBST(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertBST(root->left, data);
    } else if (data > root->data) {
        root->right = insertBST(root->right, data);
    }
    return root;
}


int height(Node* node) {
    if (node == NULL) {
        return 0;
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}


int balanceFactor(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}


Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;


    return y;
}


void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}


void preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

int main() {
    Node* root = NULL;
    int values[] = {10, 20, 30};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        root = insertBST(root, values[i]);
        int bf = balanceFactor(root);
        printf("%d eklendi. BF(kok) = %d\n", values[i], bf);


        if (bf < -1) {
            printf("RR dengesizligi: Sol rotasyon\n\n");
            root = rotateLeft(root);
        }
    }

    printf("Kok: %d\n", root->data);
    
    printf("Inorder: ");
    inorder(root);
    printf("\n");

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    return 0;
}