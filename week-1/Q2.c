#include <stdio.h>

int main() {
    int sayi, temp, kalan, ters = 0;

    printf("Lutfen bir tam sayi giriniz: ");
    scanf("%d", &sayi);

    temp = sayi;

    while (sayi != 0) {
        kalan = sayi % 10;
        ters = (ters * 10) + kalan;
        sayi /= 10; 
    }

    if (temp == ters) {
        printf("%d bir palindrom sayidir.\n", temp);
    } else {
        printf("%d bir palindrom sayi degildir.\n", temp);
    }

    return 0;
}