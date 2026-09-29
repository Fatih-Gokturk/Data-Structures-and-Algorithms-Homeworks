#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node *next;
};

int main() {
    // Pointer oluşturuyorum.
    struct Node *head = NULL;
    head = (struct Node*)malloc(sizeof(struct Node));

    
    head->data = 10;
    head->next = NULL;

    printf("Olusturulan Node icindeki deger: %d\n", head->data);

    return 0;
}