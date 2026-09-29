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

    head->data = 10;
    head->next = node2;

    node2->data = 20;
    node2->next = node3;

    node3->data = 30;
    node3->next = NULL;

    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = 40;
    newNode->next = NULL;

    struct Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = newNode;

    current = head;
    printf("Son liste elemanlari:\n");
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }

    struct Node *temp;
    current = head;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}