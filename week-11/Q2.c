#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>


void grafOlustur(int graf[6][6]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            graf[i][j] = 0;
        }
    }


    int kenarlar[10][3] = {
        {0, 1, 7}, // A - B : 7
        {0, 2, 5}, // A - C : 5
        {0, 5, 1}, // A - F : 1
        {1, 2, 1}, // B - C : 1
        {1, 3, 1}, // B - D : 1
        {1, 4, 3}, // B - E : 3
        {2, 3, 2}, // C - D : 2
        {2, 4, 1}, // C - E : 1
        {3, 5, 7}, // D - F : 7
        {4, 5, 2}  // E - F : 2
    };

    for (int i = 0; i < 10; i++) {
        int u = kenarlar[i][0];
        int v = kenarlar[i][1];
        int agirlik = kenarlar[i][2];
        graf[u][v] = agirlik;
        graf[v][u] = agirlik;
    }
}


void tabloYazdir(int adim, int secilenIdx, int bilinen[6], int maliyet[6], int yol[6], int sonsuz) {
    printf("\n--- Adim %d (Secilen ve Isaretlenen Dugum: %c) ---\n", adim, 'A' + secilenIdx);
    printf("Dugum | Isaret | Maliyet | Yol\n");
    printf("------+--------+---------+-----\n");

    for (int i = 0; i < 6; i++) {
        printf("  %c   |   %d    |", 'A' + i, bilinen[i]);

        if (maliyet[i] == sonsuz) {
            printf(" SONSUZ  |");
        } else {
            printf("   %-5d |", maliyet[i]);
        }

        if (yol[i] == -1) {
            printf("  -\n");
        } else {
            printf("  %c\n", 'A' + yol[i]);
        }
    }
}

// Görev 1
void dijkstra(int graf[6][6], int kok, int maliyet[6], int yol[6], bool adimlariGoster) {
    const int SONSUZ = 999999;
    int bilinen[6];

    for (int i = 0; i < 6; i++) {
        bilinen[i] = 0;
        maliyet[i] = SONSUZ;
        yol[i] = -1;
    }

    maliyet[kok] = 0;

    for (int adim = 1; adim <= 6; adim++) {
        int enKucukMaliyet = SONSUZ;
        int u = -1;

        for (int i = 0; i < 6; i++) {
            if (bilinen[i] == 0 && maliyet[i] < enKucukMaliyet) {
                enKucukMaliyet = maliyet[i];
                u = i;
            }
        }

        if (u == -1) break;

        bilinen[u] = 1;

        for (int v = 0; v < 6; v++) {
            if (graf[u][v] > 0 && bilinen[v] == 0) {
                if (maliyet[u] + graf[u][v] < maliyet[v]) {
                    maliyet[v] = maliyet[u] + graf[u][v];
                    yol[v] = u;
                }
            }
        }

        if (adimlariGoster) {
            tabloYazdir(adim, u, bilinen, maliyet, yol, SONSUZ);
        }
    }
}

// Görev 2
void rotaYazdir(int kok, int hedef, int maliyet[6], int yol[6]) {
    int geciciYol[6];
    int uzunluk = 0;
    int mevcut = hedef;


    while (mevcut != -1) {
        geciciYol[uzunluk++] = mevcut;
        mevcut = yol[mevcut];
    }

    printf("%c -> %c En Dusuk Maliyetli Rota: ", 'A' + kok, 'A' + hedef);
    for (int i = uzunluk - 1; i >= 0; i--) {
        printf("%c", 'A' + geciciYol[i]);
        if (i > 0) {
            printf(" -> ");
        }
    }
    printf(" | Toplam Maliyet: %d\n", maliyet[hedef]);
}

int main() {
    int graf[6][6];
    int maliyet[6];
    int yol[6];
    char kokKarakter;

    grafOlustur(graf);


    printf("Kok dugumu giriniz (A-F): ");
    scanf(" %c", &kokKarakter);
    kokKarakter = (char)toupper((unsigned char)kokKarakter);

    if (kokKarakter < 'A' || kokKarakter > 'F') {
        printf("Gecersiz dugum girildi! Varsayilan olarak 'A' secildi.\n");
        kokKarakter = 'A';
    }

    int secilenKok = kokKarakter - 'A';
    printf("\n=== GOREV 1: KOK DUGUM '%c' ICIN DIJKSTRA ADIMLARI ===\n", kokKarakter);
    dijkstra(graf, secilenKok, maliyet, yol, true);


    printf("\n=== GOREV 2: KOK DUGUM 'A' ICIN ROTA CIKTILARI ===\n");
    int maliyetA[6], yolA[6];
    dijkstra(graf, 0, maliyetA, yolA, false); // 0 -> 'A'
    rotaYazdir(0, 1, maliyetA, yolA);        // A -> B
    rotaYazdir(0, 3, maliyetA, yolA);        // A -> D

    // --- GÖREV 3
    printf("\n=== GOREV 3: MERKEZI DUGUM ANALIZI ===\n");
    int toplamMaliyetler[6];
    int enDusukToplam = 999999;

    for (int i = 0; i < 6; i++) {
        dijkstra(graf, i, maliyet, yol, false);
        int agacToplami = 0;
        for (int j = 0; j < 6; j++) {
            agacToplami += maliyet[j];
        }
        toplamMaliyetler[i] = agacToplami;
        printf("Kok Dugum %c -> En Kisa Yol Agaci Toplam Maliyeti: %d\n", 'A' + i, agacToplami);

        if (agacToplami < enDusukToplam) {
            enDusukToplam = agacToplami;
        }
    }

    printf("\nSONUC: En dusuk toplam maliyete (%d) sahip en merkezi dugum(ler): ", enDusukToplam);
    bool ilkYazdirildi = false;
    for (int i = 0; i < 6; i++) {
        if (toplamMaliyetler[i] == enDusukToplam) {
            if (ilkYazdirildi) printf(" ve ");
            printf("%c", 'A' + i);
            ilkYazdirildi = true;
        }
    }
    printf("\n");

    return 0;
}