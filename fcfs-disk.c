#include <stdio.h>
#include <stdlib.h>

int main() {
    int r, hp, s = 0;

    printf("Enter the size of the request queue: ");
    scanf("%d", &r);

    int req[r];
    printf("Enter the request queue: ");
    for (int i = 0; i < r; i++) {
        scanf("%d", &req[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &hp);

    // FCFS scheduling
    s = abs(hp - req[0]);
    for (int i = 0; i < r - 1; i++) {
        s += abs(req[i] - req[i + 1]);
        printf("Req %d is completed\n", req[i]);
    }
    printf("Req %d is completed\n", req[r - 1]);

    printf("Total seek time is: %d\n", s);
    return 0;
}
