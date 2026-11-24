#include <stdio.h>
#include <stdbool.h>

void matrisSifirla(int matris[6][6]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matris[i][j] = 0;
        }
    }
}


void kenarEkle(int matris[6][6], int u, int v) {
    matris[u - 1][v - 1] = 1;
    matris[v - 1][u - 1] = 1;
}

// Görev 1
void matrisYazdir(int matris[6][6]) {
    printf("1. Komsuluk Matrisi (6x6):\n    ");
    for (int i = 1; i <= 6; i++) {
        printf("%d ", i);
    }
    printf("\n   -------------\n");

    for (int i = 0; i < 6; i++) {
        printf("%d | ", i + 1);
        for (int j = 0; j < 6; j++) {
            printf("%d ", matris[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Görev 2
void dereceHesapla(int matris[6][6]) {
    int genelDerece = 0;
    printf("2. Dugum Dereceleri:\n");

    for (int i = 0; i < 6; i++) {
        int dugumDerecesi = 0;
        for (int j = 0; j < 6; j++) {
            dugumDerecesi += matris[i][j];
        }
        genelDerece += dugumDerecesi;
        printf("   Dugum %d derecesi: %d\n", i + 1, dugumDerecesi);
    }
    printf("   Grafin Genel (Toplam) Derecesi: %d\n\n", genelDerece);
}

// Görev 3
void bipartiteKontrol(int matris[6][6], int baslangicDugumu) {
    int uzaklik[6];
    int renk[6];
    int kuyruk[6];
    int on = 0, arka = 0;

    for (int i = 0; i < 6; i++) {
        uzaklik[i] = -1;
        renk[i] = -1;
    }

    int startIdx = baslangicDugumu - 1;
    uzaklik[startIdx] = 0;
    renk[startIdx] = 0;
    kuyruk[arka++] = startIdx;

 
    while (on < arka) {
        int u = kuyruk[on++];
        for (int v = 0; v < 6; v++) {
            if (matris[u][v] == 1 && uzaklik[v] == -1) {
                uzaklik[v] = uzaklik[u] + 1;
                renk[v] = uzaklik[v] % 2;
                kuyruk[arka++] = v;
            }
        }
    }

    printf("3. Bipartite Kontrolu (Baslangic Dugumu: %d):\n", baslangicDugumu);
    for (int i = 0; i < 6; i++) {
        printf("   Dugum %d -> Uzaklik: %d | Parite/Renk: %s (%d)\n",
               i + 1,
               uzaklik[i],
               (renk[i] == 0) ? "Cift / Mavi" : "Tek / Kirmizi",
               renk[i]);
    }

 
    bool bipartiteMi = true;
    for (int u = 0; u < 6; u++) {
        for (int v = u + 1; v < 6; v++) {
            if (matris[u][v] == 1 && renk[u] == renk[v]) {
                printf("   [CAKISMA TESPIT EDILDI] (%d, %d) komsu dugumleri ayni renge/pariteye (%s) sahip!\n",
                       u + 1, v + 1, (renk[u] == 0) ? "Mavi/Cift" : "Kirmizi/Tek");
                bipartiteMi = false;
            }
        }
    }

    if (bipartiteMi) {
        printf("   SONUC: Graf Iki Parcalidir (BIPARTITE).\n");
        printf("   Kume U (Mavi / Istemciler): { ");
        for (int i = 0; i < 6; i++) if (renk[i] == 0) printf("%d ", i + 1);
        printf("}\n   Kume V (Kirmizi / Sunucular): { ");
        for (int i = 0; i < 6; i++) if (renk[i] == 1) printf("%d ", i + 1);
        printf("}\n");
    } else {
        printf("   SONUC: Graf Iki Parcali DEGILDIR (NOT BIPARTITE).\n");
    }
    printf("------------------------------------------------------------\n\n");
}

int main() {
    int komsulukMatrisi[6][6];
    int kenarlar[][2] = {
        {1, 2}, {1, 4}, {2, 3}, {3, 4}, {3, 6}, {4, 5}, {5, 6}
    };
    int kenarSayisi = sizeof(kenarlar) / sizeof(kenarlar[0]);


    printf("=== MEVCUT GRAF ANALIZI ===\n");
    matrisSifirla(komsulukMatrisi);
    for (int i = 0; i < kenarSayisi; i++) {
        kenarEkle(komsulukMatrisi, kenarlar[i][0], kenarlar[i][1]);
    }
    matrisYazdir(komsulukMatrisi);
    dereceHesapla(komsulukMatrisi);
    bipartiteKontrol(komsulukMatrisi, 1);

    // GÖREV 4
    printf("=== DINAMIK TEST: (2, 4) KENARI EKLENDIKTEN SONRA ===\n");
    kenarEkle(komsulukMatrisi, 2, 4);
    matrisYazdir(komsulukMatrisi);
    dereceHesapla(