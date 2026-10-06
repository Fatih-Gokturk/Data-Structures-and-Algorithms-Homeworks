#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Word {
    char text[50];
    struct Word* next;
} Word;


void pushWord(Word** top, char* text);
void popWord(Word** top);
void showWords(Word* top);


void printReverse(Word* node) {
    if (node == NULL) return;
    printReverse(node->next);
    printf("%s ", node->text);
}


void pushWord(Word** top, char* text) {
    Word* newWord = (Word*)malloc(sizeof(Word));
    strcpy(newWord->text, text);
    newWord->next = *top; 
    *top = newWord;
}


void popWord(Word** top) {
    if (*top == NULL) {
        return;
    }
    Word* temp = *top;
    *top = (*top)->next;
    free(temp);
}


void showWords(Word* top) {
    printf("> show -> ");
    if (top != NULL) {
        printReverse(top);
    }
    printf("\n");
}

int main() {
    Word* top = NULL;
    char command[100];
    char op[20];
    char arg[50];

    printf("Komutlar: 'add', 'undo', 'show', 'exit'\n");

    while (1) {
        printf("> ");
        if (fgets(command, sizeof(command), stdin) == NULL) break;
        

        command[strcspn(command, "\n")] = 0;


        int parsed = sscanf(command, "%s %s", op, arg);

        if (parsed > 0) {
            if (strcmp(op, "add") == 0 && parsed == 2) {
                pushWord(&top, arg);
            } 
            else if (strcmp(op, "undo") == 0) {
                popWord(&top);
            } 
            else if (strcmp(op, "show") == 0) {
                showWords(top);
            } 
            else if (strcmp(op, "exit") == 0) {
                break;
            }
        }
    }


    while (top != NULL) {
        popWord(&top);
    }

    return 0;
}