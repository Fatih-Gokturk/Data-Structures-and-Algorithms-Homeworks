#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

int main() {
    struct Node *head = (struct Node*)malloc(sizeof(struct Node));
    struct Node *node2 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *node3 = (struct Node*)malloc(sizeof(struct Node));

    // Düğümleri bağlama
    head->data = 10;
    head->next = node2;

    node2->data = 20;
    node2->next = node3;

    node3->data = 30;
    node3->next = NULL;

    
    struct Node *current = head;

    printf("Liste elemanlari: ");
    

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    
    printf("\n");

    return 0;
}