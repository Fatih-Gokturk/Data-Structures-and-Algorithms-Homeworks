#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Song {
    char name[50];
    struct Song* next;
    struct Song* prev;
} Song;


void addSongToEnd(Song** head, char* name);
void removeSong(Song** head, char* name);
void playNext(Song** current);
void playPrevious(Song** current);
void displayPlaylist(Song* head);


void addSongToEnd(Song** head, char* name) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->name, name);
    newSong->next = NULL;
    newSong->prev = NULL;

    if (*head == NULL) {
        *head = newSong;
        printf("Sarki eklendi: %s\n", name);
        return;
    }

    Song* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newSong;
    newSong->prev = temp;
    printf("Sarki eklendi: %s\n", name);
}


void removeSong(Song** head, char* name) {
    if (*head == NULL) {
        printf("Liste bos.\n");
        return;
    }

    Song* temp = *head;

    while (temp != NULL && strcmp(temp->name, name) != 0) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Sarki bulunamadi.\n");
        return;
    }


    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        *head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    free(temp); 
    printf("%s basariyla silindi.\n", name);
}


void playNext(Song** current) {
    if (*current == NULL) {
        printf("Liste bos.\n");
        return;
    }
    
    if ((*current)->next != NULL) {
        *current = (*current)->next;
        printf("Su an caliyor: %s\n", (*current)->name);
    } else {
        printf("Listenin sonundasiniz. Sonraki sarki yok.\n");
    }
}


void playPrevious(Song** current) {
    if (*current == NULL) {
        printf("Liste bos.\n");
        return;
    }
    
    if ((*current)->prev != NULL) {
        *current = (*current)->prev;
        printf("Su an caliyor: %s\n", (*current)->name);
    } else {
        printf("Listenin basindasiniz. Onceki sarki yok.\n");
    }
}


void displayPlaylist(Song* head) {
    if (head == NULL) {
        printf("Liste bos.\n");
        return;
    }
    
    Song* temp = head;
    printf("\nCalma Listesi\n");
    while (temp != NULL) {
        printf("- %s\n", temp->name);
        temp = temp->next;
    }
}

int main() {
    Song* head = NULL;
    Song* current = NULL;
    int secim;
    char sarkiAdi[50];

    while (1) {
        printf("\n1. Sarki Ekle\n2. Sarki Sil\n3. Sonraki Sarki\n4. Onceki Sarki\n5. Listeyi Goster\n0. Cikis\nSeciminiz: ");
        scanf("%d", &secim);
        getchar();

        switch (secim) {
            case 1:
                printf("Eklenecek sarki adi: ");
                fgets(sarkiAdi, 50, stdin);
                sarkiAdi[strcspn(sarkiAdi, "\n")] = 0;
                addSongToEnd(&head, sarkiAdi);
                

                if (current == NULL) {
                    current = head; 
                }
                break;
            case 2:
                printf("Silinecek sarki adi: ");
                fgets(sarkiAdi, 50, stdin);
                sarkiAdi[strcspn(sarkiAdi, "\n")] = 0;
                

                if (current != NULL && strcmp(current->name, sarkiAdi) == 0) {
                    if (current->next != NULL) current = current->next;
                    else if (current->prev != NULL) current = current->prev;
                    else current = NULL;
                }
                
                removeSong(&head, sarkiAdi);
                break;
            case 3:
                playNext(&current);
                break;
            case 4:
                playPrevious(&current);
                break;
            case 5:
                displayPlaylist(head);
                break;
            case 0:

                while (head != NULL) {
                    Song* temp = head;
                    head = head->next;
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