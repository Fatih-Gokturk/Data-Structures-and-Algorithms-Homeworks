#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct PrintJob {
    char fileName[50];
    struct PrintJob* next;
} PrintJob;

typedef struct Queue {
    PrintJob* front;
    PrintJob* rear;
} Queue;


void enqueuePrintJob(Queue* q, char* fileName);
void processNextJob(Queue* q);
void showQueue(Queue q);


void enqueuePrintJob(Queue* q, char* fileName) {
    PrintJob* newJob = (PrintJob*)malloc(sizeof(PrintJob));
    strcpy(newJob->fileName, fileName);
    newJob->next = NULL;

    if (q->rear == NULL) { 

        q->front = newJob;
        q->rear = newJob;
    } else { 

        q->rear->next = newJob;
        q->rear = newJob;
    }
    printf("'%s' yazdirma kuyruguna eklendi.\n", fileName);
}


void processNextJob(Queue* q) {

    if (q->front == NULL) { 
        printf("Kuyruk bos! Yazdirilacak dosya yok.\n");
        return;
    }


    PrintJob* temp = q->front;
    printf("Yazdiriliyor: %s\n", temp->fileName);

    q->front = q->front->next;


    if (q->front == NULL) { 
        q->rear = NULL;
    }

    free(temp);
}


void showQueue(Queue q) {
    if (q.front == NULL) {
        printf("Yazdirma kuyrugu bos.\n");
        return;
    }

    PrintJob* temp = q.front;
    printf("\nYazdirma Kuyrugu\n");
    int sira = 1;
    while (temp != NULL) {
        printf("%d. %s\n", sira, temp->fileName);
        temp = temp->next;
        sira++;
    }
    printf("\n");
}

int main() {
    Queue printerQueue;
    printerQueue.front = NULL;
    printerQueue.rear = NULL;

    int secim;
    char dosyaAdi[50];

    while (1) {
        printf("\n1) Yeni dosya ekle\n2) Yazdir\n3) Kuyrugu goster\n0) Cikis\nSeciminiz: ");
        scanf("%d", &secim);
        getchar();

        switch (secim) {
            case 1:
                printf("Eklenecek dosya adi: ");
                fgets(dosyaAdi, 50, stdin);
                dosyaAdi[strcspn(dosyaAdi, "\n")] = 0; 
                enqueuePrintJob(&printerQueue, dosyaAdi);
                break;
            case 2:
                processNextJob(&printerQueue);
                break;
            case 3:
                showQueue(printerQueue);
                break;
            case 0:
                while (printerQueue.front != NULL) {
                    PrintJob* temp = printerQueue.front;
                    printerQueue.front = printerQueue.front->next;
                    free(temp);
                }
                printf("Cikis yapiliyor...\n");
                return 0;
            default:
                printf("Gecersiz secim!\n");
        }
    }
    return 0;
}