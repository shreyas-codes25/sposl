#include <stdio.h>
#include <stdlib.h>

int main() {
    int r, hp, s = 0;

    printf("Enter the size of the request queue: ");
    scanf("%d", &r);

    int req[r], temp[r];
    printf("Enter the request queue: ");
    for (int i = 0; i < r; i++) {
        scanf("%d", &req[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &hp);

    // SSTF scheduling
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < r; j++) {
            temp[j] = abs(hp - req[j]);
        }
        int min = temp[0], pos = 0;
        for (int k = 1; k < r; k++) {
            if (min > temp[k] && req[k] != 9999) {
                min = temp[k];
                pos = k;
            }
        }

        s += abs(hp - req[pos]);
        printf("Req %d is completed\n", req[pos]);
        hp = req[pos];
        req[pos] = 9999; // Mark completed request
    }

    printf("Total seek time is: %d\n", s);
    return 0;
}

//////////////////////////////////
