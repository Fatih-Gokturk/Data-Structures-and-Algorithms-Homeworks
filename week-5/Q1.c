#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Hasta {
    int id;
    char isim[50];
    char durum[20];
};


struct Node {
    struct Hasta veri;
    struct Node* next;
};


struct Queue {
    struct Node* front;
    struct Node* rear;
};


struct Stack {
    struct Node* top;
};


struct LinkedList {
    struct Node* head;
};



void initQueue(struct Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

int isQueueEmpty(struct Queue* q) {
    return q->front == NULL;
}

void enqueue(struct Queue* q, struct Hasta h) {

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    if (!newNode) {
        printf("Bellek yetersiz!\n");
        return;
    }
    
    strcpy(h.durum, "bekliyor");
    newNode->veri = h;
    newNode->next = NULL;

    if (isQueueEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

struct Hasta dequeue(struct Queue* q) {

    struct Hasta bosHasta = {-1, "", ""};

    if (isQueueEmpty(q)) {
        printf("Kuyruk bos, cikarilacak hasta yok!\n");
        return bosHasta;
    }

    struct Node* temp = q->front;
    struct Hasta h = temp->veri;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return h;
}

void initStack(struct Stack* s) {
    s->top = NULL;
}

int isStackEmpty(struct Stack* s) {
    return s->top == NULL;
}

void push(struct Stack* s, struct Hasta h) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    if (!newNode) {
        printf("Bellek yetersiz!\n");
        return;
    }

    strcpy(h.durum, "muayenede");
    newNode->veri = h;
    newNode->next = s->top;
    s->top = newNode;
}

struct Hasta pop(struct Stack* s) {

    struct Hasta bosHasta = {-1, "", ""};

    if (isStackEmpty(s)) {
        printf("Yigin bos, cikarilacak hasta yok!\n");
        return bosHasta;
    }

    struct Node* temp = s->top;
    struct Hasta h = temp->veri;
    s->top = s->top->next;

    free(temp);
    return h;
}

void initList(struct LinkedList* list) {
    list->head = NULL;
}

void gecmiseEkle(struct LinkedList* list, struct Hasta h) {

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    if (!newNode) {
        printf("Bellek yetersiz!\n");
        return;
    }

    strcpy(h.durum, "tamamlandi");
    newNode->veri = h;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } 

    else {
        struct Node* curr = list->head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}



void kuyrukYazdir(struct Queue* q) {

    printf("--- Bekleyen Hastalar ---\n");

    if (isQueueEmpty(q)) {
        printf("Hasta yok.\n");
        return;
    }

    struct Node* curr = q->front;

    while (curr != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", curr->veri.id, curr->veri.isim, curr->veri.durum);
        curr = curr->next;
    }
}

void yiginYazdir(struct Stack* s) {

    printf("--- Muayene Odasindaki Hastalar ---\n");

    if (isStackEmpty(s)) {
        printf("Hasta yok.\n");
        return;
    }
    struct Node* curr = s->top;

    while (curr != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", curr->veri.id, curr->veri.isim, curr->veri.durum);
        curr = curr->next;
    }
}

void gecmisYazdir(struct LinkedList* list) {
    printf("--- Tamamlanan Hastalar ---\n");
    if (list->head == NULL) {
        printf("Hasta yok.\n");
        return;
    }

    struct Node* curr = list->head;


    while (curr != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", curr->veri.id, curr->veri.isim, curr->veri.durum);
        curr = curr->next;
    }
}



void bellekTemizle(struct Queue* q, struct Stack* s, struct LinkedList* list) {
    while (!isQueueEmpty(q)) dequeue(q);
    while (!isStackEmpty(s)) pop(s);
    struct Node* curr = list->head;
    while (curr != NULL) {
        struct Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
}



int main() {
    struct Queue beklemeKuyrugu;
    struct Stack muayeneOdasi;
    struct LinkedList tamamlananlar;


    initQueue(&beklemeKuyrugu);
    initStack(&muayeneOdasi);
    initList(&tamamlananlar);



    struct Hasta h1 = {1, "Ahmet", ""};
    struct Hasta h2 = {2, "Mehmet", ""};
    struct Hasta h3 = {3, "Ayse", ""};


    enqueue(&beklemeKuyrugu, h1);
    enqueue(&beklemeKuyrugu, h2);
    enqueue(&beklemeKuyrugu, h3);



    printf(">>> Baslangic Durumu:\n");
    kuyrukYazdir(&beklemeKuyrugu);
    printf("\n");



    printf(">>> Ahmet muayeneye aliniyor ve tamamlaniyor...\n");
    struct Hasta muayeneEdilen1 = dequeue(&beklemeKuyrugu);
    push(&muayeneOdasi, muayeneEdilen1);
    struct Hasta biten1 = pop(&muayeneOdasi);
    gecmiseEkle(&tamamlananlar, biten1);



    printf(">>> Mehmet muayeneye aliniyor ve tamamlaniyor...\n");
    struct Hasta muayeneEdilen2 = dequeue(&beklemeKuyrugu);
    push(&muayeneOdasi, muayeneEdilen2);
    struct Hasta biten2 = pop(&muayeneOdasi);
    gecmiseEkle(&tamamlananlar, biten2);




    printf("\n=== Tum Islemler Sonrasi ===\n\n");
    kuyrukYazdir(&beklemeKuyrugu);
    printf("\n");
    yiginYazdir(&muayeneOdasi);
    printf("\n");
    gecmisYazdir(&tamamlananlar);



    bellekTemizle(&beklemeKuyrugu, &muayeneOdasi, &tamamlananlar);

    return 0;
}