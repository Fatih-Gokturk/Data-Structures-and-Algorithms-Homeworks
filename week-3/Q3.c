#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

void printList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void clear(struct Node **head) {
    struct Node *current = *head;
    struct Node *temp;
    
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    
    *head = NULL;
}

struct Node* findMiddle(struct Node* head) {
    if (head == NULL) return NULL;

    struct Node *slow = head;
    struct Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

void append(struct Node **head, int value) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

int main() {
    struct Node *head = NULL;

    append(&head, 10);
    append(&head, 20);
    append(&head, 30);
    append(&head, 40);
    append(&head, 50);

    printf("--- Tek Sayida Eleman ---\n");
    printList(head);
    struct Node *mid1 = findMiddle(head);
    if (mid1 != NULL) {
        printf("Ortadaki Eleman: %d\n\n", mid1->data);
    }

    append(&head, 60);

    printf("--- Cift Sayida Eleman ---\n");
    printList(head);
    struct Node *mid2 = findMiddle(head);
    if (mid2 != NULL) {
        printf("Ortadaki Eleman: %d\n", mid2->data);
    }

    clear(&head);

    return 0;
}