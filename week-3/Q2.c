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

void insertAt(struct Node **head, int value, int position) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (position <= 0 || *head == NULL) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    struct Node *current = *head;
    int currentIndex = 0;

    while (current->next != NULL && currentIndex < position - 1) {
        current = current->next;
        currentIndex++;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void deleteAt(struct Node **head, int position) {
    if (*head == NULL || position < 0) return;

    if (position == 0) {
        struct Node *temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    struct Node *current = *head;
    int currentIndex = 0;

    while (current->next != NULL && currentIndex < position - 1) {
        current = current->next;
        currentIndex++;
    }

    if (current->next == NULL) {
        return;
    }

    struct Node *temp = current->next;
    current->next = temp->next;
    free(temp);
}

int main() {
    struct Node *head = NULL;

    // Basit birkac ekleme yapalim
    insertAt(&head, 10, 0);
    insertAt(&head, 20, 1);
    insertAt(&head, 30, 2);
    insertAt(&head, 40, 5); // eleman sayisindan buyuk, sona ekler

    printf("Liste son hali: ");
    printList(head);

    // Basit bir silme yapalim
    deleteAt(&head, 1); // 1. indisteki 20'yi silsin
    
    printf("Silinme sonrasi: ");
    printList(head);

    // Temizleyip cikalim
    clear(&head);

    return 0;
}