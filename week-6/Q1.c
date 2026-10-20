#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;


Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    
    return root;
}


void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}


int search(Node* root, int value) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == value) {
        return 1;
    }
    

    if (value < root->data) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}


int findMin(Node* root) {
    Node* current = root;

    while (current->left != NULL) {
        current = current->left;
    }
    return current->data;
}

int main() {
    Node* root = NULL;
    int numbers[] = {40, 20, 60, 10, 30, 50, 70};

    for (int i = 0; i < 7; i++)
        root = insert(root, numbers[i]);


    printf("Inorder: ");
    inorder(root);
    printf("\n");


    if (search(root, 30))
        printf("30 agacta bulundu.\n");
    else
        printf("30 agacta bulunamadi.\n");

    if (search(root, 90))
        printf("90 agacta bulundu.\n");
    else
        printf("90 agacta bulunamadi.\n");

    if (root != NULL)
        printf("En kucuk eleman: %d\n", findMin(root));

    return 0;
}

/*

KISA DEĞERLENDİRME SORULARI VE CEVAPLARI
------------------------------------------

1. 25 değeri eklenirse hangi düğümün altına yerleşir?
   Cevap: 30 düğümünün sol altına yerleşir. 
   Adımlar: 40'tan küçük -> sola (20), 20'den büyük -> sağa (30), 30'dan küçük -> 30'un soluna.

2. Inorder fonksiyonunda printf() ilk satıra taşınırsa hangi dolaşma elde edilir?
   Cevap: Preorder dolaşma elde edilir Sıralama: kök -> sol -> sağ olur.

3. findMin() içinde left yerine right takip edilirse hangi değer bulunur?
   Cevap: 70

*/