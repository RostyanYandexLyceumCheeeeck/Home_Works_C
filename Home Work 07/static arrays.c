#include <stdio.h>
#include <windows.h>


int main() {

    size_t i, j, n = 4;
    int arr[n][n], x;

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &arr[i][j]);

    for(i = 0; i < n; i++){
        for(j = 0; j < i; j++){
            x = arr[i][j];
            arr[i][j] = arr[j][i];
            arr[j][i] = x;
        }
    }

    for(i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}
