#include <stdio.h>
#include <stdlib.h>

typedef struct Dugum {
    int veri;
    struct Dugum* solDugum;
    struct Dugum* sagDugum;
} Dugum;

Dugum* dugumOlustur(int veri) {
    Dugum* yeniDugum = (Dugum*)malloc(sizeof(Dugum));
    yeniDugum->veri = veri;
    yeniDugum->solDugum = NULL;
    yeniDugum->sagDugum = NULL;
    return yeniDugum;
}

Dugum* ekle(Dugum* kok, int veri) {
    if (kok == NULL) {
        return dugumOlustur(veri);
    }
    if (veri < kok->veri) {
        kok->solDugum = ekle(kok->solDugum, veri);
    } else if (veri > kok->veri) {
        kok->sagDugum = ekle(kok->sagDugum, veri);
    }
    return kok;
}

int hazineAra(Dugum* kok, int arananSayi) {
    if (kok == NULL) {
        return 0;
    }

    printf("-> Ziyaret edilen dugum: %d\n", kok->veri);

    if (kok->veri == arananSayi) {
        return 1;
    }

    if (arananSayi < kok->veri) {
        return hazineAra(kok->solDugum, arananSayi);
    } else {
        return hazineAra(kok->sagDugum, arananSayi);
    }
}

int maksimumAdimSayisi(Dugum* kok) {
    if (kok == NULL) {
        return 0;
    }
    int solAdim = maksimumAdimSayisi(kok->solDugum);
    int sagAdim = maksimumAdimSayisi(kok->sagDugum);

    return (solAdim > sagAdim ? solAdim : sagAdim) + 1;
}

int main() {
    Dugum* kok = NULL;
    
    int hazineler[] = {50, 30, 70, 20, 40, 60, 80, 10};
    int elemanSayisi = sizeof(hazineler) / sizeof(hazineler[0]);

    for (int i = 0; i < elemanSayisi; i++) {
        kok = ekle(kok, hazineler[i]);
    }

    int enKotuDurum = maksimumAdimSayisi(kok);
    printf("Bilgi: Bu agacta hazineyi bulmak icin en kotu durumda %d adim gerekir.\n\n", enKotuDurum);

    int arananSayi;
    printf("Kazmak istediginiz hazine numarasini girin: ");
    scanf("%d", &arananSayi);

    printf("\n--- Arama Basliyor ---\n");
    if (hazineAra(kok, arananSayi)) {
        printf("\nSonuc: Hazine bulundu!\n");
    } else {
        printf("\nSonuc: Maalesef bosuna kazdin... \n");
    }

    return 0;
}