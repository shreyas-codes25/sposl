#include <stdio.h>
#include <stdlib.h>

int main() {
    int r, hp;
    int req[50];
    int s = 0;
    int x, pos, i, j, k;
    int temp[50];
    int l = 0, r1 = 0;
    int left[50];
    int right[50];
    int temp1, temp2;

    printf("Enter the size of the request queue:");
    scanf("%d", &r);

    printf("Enter the request queue:");
    for (i = 0; i < r; i++) {
        scanf("%d", &req[i]);
    }

    printf("Which is the initial head point:");
    scanf("%d", &hp);

    int ch;
    printf("Enter 1 for FCFS\nEnter 2 for SSTF\nEnter 3 for SCAN:");
    scanf("%d", &ch);

    switch (ch) {
        case 1:
            // FCFS
            s = abs(hp - req[0]);
            for (i = 0; i < r - 1; i++) {
                s += abs(req[i] - req[i + 1]);
                printf("Req %d is completed\n", req[i]);
            }
            break;

        case 2:
            // SSTF
            for (i = 0; i < r; i++) {
                for (j = 0; j < r; j++) {
                    temp[j] = abs(hp - req[j]);
                }
                int min = req[0];
                for (k = 0; k < r; k++) {
                    if (min > temp[k]) {
                        min = temp[k];
                        pos = k;
                    }
                }

                s += abs(hp - req[pos]);
                printf("Req %d is completed\n", req[pos]);
                hp = req[pos];
                req[pos] = 9999; // Mark completed request as invalid
            }
            break;

        case 3:
            // SCAN
            for (k = 0; k < r; k++) {
                if (hp >= req[k]) {
                    left[l++] = req[k];
                } else {
                    right[r1++] = req[k];
                }
            }

            // Sorting arrays
            for (i = 0; i < r1 - 1; i++) {
                for (j = 0; j < r1 - i - 1; j++) {
                    if (right[j] > right[j + 1]) {
                        temp1 = right[j];
                        right[j] = right[j + 1];
                        right[j + 1] = temp1;
                    }
                }
            }

            for (i = 0; i < l - 1; i++) {
                for (j = 0; j < l - i - 1; j++) {
                    if (left[j] > left[j + 1]) {
                        temp2 = left[j];
                        left[j] = left[j + 1];
                        left[j + 1] = temp2;
                    }
                }
            }

            // Calculate total seek time
            s += abs(hp - left[l - 1]);
            for (i = 0; i < r1 - 1; i++) {
                s += abs(right[i] - left[i]);
                printf("Req %d is completed\n", right[i]);
            }
            s += abs(right[r1 - 1] - left[0]);

            for (j = l - 1; j >= 0; j--) {
                s += abs(left[j] - left[j - 1]);
                printf("Req %d is completed\n", left[j]);
            }
            break;
    }

    printf("Total seek time is:%d\n", s);
    return 0;
}


