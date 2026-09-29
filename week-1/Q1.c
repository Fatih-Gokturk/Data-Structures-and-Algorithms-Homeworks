#include <stdio.h>

int main() {
    int n = 10;          // 1 kez
    int sayilar[10];     // 1 kez
    int i;               // 1 kez

    // Sayı istiyorum
    for (i = 0; i < n; i++) { // ilk döngü = O(n)
        // i = 0   -> 1 kez
        // i < n   -> n + 1 kez
        // i++     -> n kez
        
        printf("Lutfen bir sayi giriniz: "); // n kez
        scanf("%d", &sayilar[i]);            // n kez
    }

    for (i = 0; i < n; i++) { // ikinci döngü = O(n)
        // i = 0   -> 1 kez
        // i < n   -> n + 1 kez
        // i++     -> n kez
        
        printf("%d ", sayilar[i]); // n kez
    }

    return 0; // 1 kez
    
    // S(n) -> sayilar dizisi 10 (n) alan kullanıyor. int n ve int i değişkenlerinin her biri 1 birim alan kullanıyor, bu nedenle S(n) = n + 2
    
    // ilk + ikinci döngü = O(2n)
    // Big O notasyonu = O(n)
    
    // T(n) = 7n + 8
}