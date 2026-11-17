#include <stdio.h>
#define N 5

// Her iki çözümün de kodunu bir yazdım.

char harfler[N] = {'A', 'B', 'C', 'D', 'E'};
const char *sehirler[N] = {"Istanbul", "Ankara", "Izmir", "Bursa", "Antalya"};


int adj[N][N] = {
    {0, 1, 0, 1, 0},
    {1, 0, 1, 0, 1},
    {0, 1, 0, 0, 0},
    {1, 0, 0, 0, 1},
    {0, 1, 0, 1, 0}
};

void bfs(int baslangic) {
    int visited[N] = {0};
    int queue[N];
    int front = 0, rear = 0;

    visited[baslangic] = 1;
    queue[rear++] = baslangic;

    printf("BFS Sirasi: ");
    while (front < rear) {
        int u = queue[front++];
        printf("%c (%s) ", harfler[u], sehirler[u]);

        for (int i = 0; i < N; i++) {
            if (adj[u][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
}

void dfs_yardimci(int u, int visited[]) {
    visited[u] = 1;
    printf("%c (%s) ", harfler[u], sehirler[u]);

    for (int i = 0; i < N; i++) {
        if (adj[u][i] == 1 && !visited[i]) {
            dfs_yardimci(i, visited);
        }
    }
}

void dfs(int baslangic) {
    int visited[N] = {0};
    printf("DFS Sirasi: ");
    dfs_yardimci(baslangic, visited);
    printf("\n");
}

int main() {
    bfs(0);
    dfs(0);
    return 0;
}