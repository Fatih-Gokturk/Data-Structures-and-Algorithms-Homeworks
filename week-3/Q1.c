#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

// 1. Listeyi ekrana bastırma (Sadece okuma yaptığı için Node* yeterli)
void printList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// 2. Listedeki düğüm sayısını bulma (Node* yeterli)
int count(struct Node *head) {
    int cnt = 0;
    struct Node *current = head;
    while (current != NULL) {
        cnt++;
        current = current->next;
    }
    return cnt;
}

// 3. Sıralı şekilde eleman ekleme (Head değişebileceği için Node** şart)
void addOrdered(struct Node **head, int value) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    // Liste boşsa veya yeni eleman baş elemandan küçük/eşitse başa ekle
    if (*head == NULL || (*head)->data >= value) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    // Uygun pozisyonu bulmak için arama yap
    struct Node *current = *head;
    while (current->next != NULL && current->next->data < value) {
        current = current->next;
    }

    // Araya veya sona ekleme
    newNode->next = current->next;
    current->next = newNode;
}

// 4. Belirli bir değeri listeden silme (Head değişebileceği için Node** şart)
void removeNode(struct Node **head, int value) {
    if (*head == NULL) return;

    // Silinecek eleman baş elemansa
    if ((*head)->data == value) {
        struct Node *temp = *head;
        *head = (*head)->next; // Head'i bir sonraki düğüme kaydır
        free(temp);            // Eski baş düğümü bellekten sil
        return;
    }

    struct Node *current = *head;
    while (current->next != NULL && current->next->data != value) {
        current = current->next;
    }

    // Eleman bulunduysa listeden kopar ve free et
    if (current->next != NULL) {
        struct Node *temp = current->next;
        current->next = current->next->next;
        free(temp);
    }
}

// 5. Listeyi tamamen boşaltma ve belleği temizleme (Head NULL olacağı için Node** şart)
void clear(struct Node **head) {
    struct Node *current = *head;
    struct Node *temp;
    
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp); // Tek tek bütün düğümleri iade et
    }
    
    *head = NULL; // Baş işaretçisini sıfırla
}

int main() {
    struct Node *head = NULL;

    // Ödevde verilen örnek sayılarla sıralı ekleme testi: 23, 11, 5, 9, 6, 4, 12, 24
    addOrdered(&head, 23);
    addOrdered(&head, 11);
    addOrdered(&head, 5);
    addOrdered(&head, 9);
    addOrdered(&head, 6);
    addOrdered(&head, 4);
    addOrdered(&head, 12);
    addOrdered(&head, 24);

    printf("Sirali Liste:\n");
    printList(head); // Beklenen: 4 -> 5 -> 6 -> 9 -> 11 -> 12 -> 23 -> 24 -> NULL

    printf("\nDugum Sayisi: %d\n", count(head));

    printf("\n9 degeri listeden siliniyor...\n");
    removeNode(&head, 9);
    printList(head);

    printf("\nListe tamamen temizleniyor (clear)...\n");
    clear(&head);
    printList(head);

    return 0;
}