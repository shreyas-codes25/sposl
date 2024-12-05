/// SCAN Disk Scheduling

#include <stdio.h>
#include <stdlib.h>

int main() {
    int r, hp, s = 0;

    printf("Enter the size of the request queue: ");
    scanf("%d", &r);

    int req[r], left[50], right[50];
    int l = 0, r1 = 0;

    printf("Enter the request queue: ");
    for (int i = 0; i < r; i++) {
        scanf("%d", &req[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &hp);

    // Separate requests into left and right of the head position
    for (int i = 0; i < r; i++) {
        if (req[i] <= hp) {
            left[l++] = req[i];
        } else {
            right[r1++] = req[i];
        }
    }

    // Sort left and right arrays
    for (int i = 0; i < l - 1; i++) {
        for (int j = 0; j < l - i - 1; j++) {
            if (left[j] > left[j + 1]) {
                int temp = left[j];
                left[j] = left[j + 1];
                left[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < r1 - 1; i++) {
        for (int j = 0; j < r1 - i - 1; j++) {
            if (right[j] > right[j + 1]) {
                int temp = right[j];
                right[j] = right[j + 1];
                right[j + 1] = temp;
            }
        }
    }

    // SCAN scheduling
    if (l > 0) s += abs(hp - left[l - 1]);
    for (int i = l - 1; i >= 0; i--) {
        printf("Req %d is completed\n", left[i]);
        if (i > 0) s += abs(left[i] - left[i - 1]);
    }
    if (r1 > 0) s += abs(left[0] - right[0]);
    for (int i = 0; i < r1; i++) {
        printf("Req %d is completed\n", right[i]);
        if (i < r1 - 1) s += abs(right[i] - right[i + 1]);
    }

    printf("Total seek time is: %d\n", s);
    return 0;
}
