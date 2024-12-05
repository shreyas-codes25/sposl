#include <stdio.h>

// Function to implement LRU Page Replacement Algorithm
void lru(int n, int str[], int nf) {
    int i, k, timer = 1, time[5], pos = 0, min = 0, frame[nf], hit = 0, fault = 0;

    // Initialize frame and time arrays
    for (k = 0; k < nf; k++) {
        frame[k] = -1;
        time[k] = 0;
    }

    for (i = 1; i <= n; i++) 
    {
        int flag = 0;
        for (k = 0; k < nf; k++)
	 {
            if (str[i] == frame[k]) { // page found
                flag = 1;
                time[k] = timer;
                timer++;
                hit++; // Increment page hit count
                break;
            }
        }

        if (flag == 0) { // page not found
            fault++;
            // Increment page fault count
            int min_time = time[0];
            pos = 0;
            for (k = 1; k < nf; k++) {
                if (time[k] < min_time) {
                    min_time = time[k];
                    pos = k;
                }
            }
            frame[pos] = str[i];
            time[pos] = timer;
            timer++;
        }

        // Display current page frames
        printf("%d\t\t", str[i]);
        for (k = 0; k < nf; k++) {
            printf("%d\t", frame[k]);
        }
        printf("\n");
    }

    printf("Number of Page Faults: %d\n", fault);
    printf("Number of Page Hits: %d\n", hit);
}

// Function to implement FIFO Page Replacement Algorithm
void fifo(int n, int str[], int nf) {
    int i, j = 0, k, frame[nf], flag, hit = 0, fault = 0;

    // Initialize frame array
    for (i = 0; i < nf; i++)
        frame[i] = -1;

    printf("\tRef String\tPage Frames\n");
    for (i = 1; i <= n; i++) {
        printf("%d\t\t", str[i]);
        flag = 0;
        for (k = 0; k < nf; k++) {
            if (frame[k] == str[i]) {
                flag = 1;
                hit++;
                break;
            }
        }
        if (flag == 0) {
            frame[j] = str[i];
            j = (j + 1) % nf;
            fault++;
        }

        // Display current page frames
        for (k = 0; k < nf; k++) {
            printf("%d\t", frame[k]);
        }
        printf("\n");
    }
    printf("Page Faults: %d\n", fault);
    printf("Page Hits: %d\n", hit);
}

int main() {
    int i, n, str[50], nf;

    // Input the length of reference string
    printf("\nEnter the length of reference string:\n");
    scanf("%d", &n);

    // Input the page numbers string
    printf("\nEnter the page numbers string:\n");
    for (i = 1; i <= n; i++)
        scanf("%d", &str[i]);

    // Input the number of frames
    printf("\nEnter the number of frames:");
    scanf("%d", &nf);

    int choice;
    printf("Choose the Page Replacement Algorithm:\n");
    printf("1. FIFO\n");
    printf("2. LRU\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fifo(n, str, nf);
            break;

        case 2:
            lru(n, str, nf);
            break;

        default:
            printf("Invalid choice\n");
    }

    return 0;
}


//#include <stdio.h>
//
//// Function to implement FIFO Page Replacement Algorithm
//void fifo(int n, int a[], int no) {
//    int i, j,k, frame[10], avail, count = 0;
//    for (i = 0; i < no; i++)
//        frame[i] = -1;
//    j = 0;
//    printf("\tRef String\tPage Frames\n");
//    for (i = 1; i <= n; i++) {
//        printf("%d\t\t", a[i]);
//        avail = 0;
//        for ( k = 0; k < no; k++)
//            if (frame[k] == a[i])
//                avail = 1;
//        if (avail == 0) {
//            frame[j] = a[i];
//            j = (j + 1) % no;
//            count++;
//            int k;
//            for ( k = 0; k < no; k++)
//                printf("%d\t", frame[k]);
//        }
//        printf("\n");
//    }
//    printf("Page Faults: %d\n", count);
//}
//
//// Function to implement LRU Page Replacement Algorithm
//void lru(int no_of_frames, int no_of_pages, int pages[]) {
//    int frames[10], counter = 0, time[10], flag1, LRUflag2, i, j, pos, faults = 0;
//    for (i = 0; i < no_of_frames; ++i) {
//        frames[i] = -1;
//    }
//
//    printf("\nF1\tF2\tF3\n");
//
//    for (i = 0; i < no_of_pages; ++i) {
//        flag1 = LRUflag2 = 0;
//
//        for (j = 0; j < no_of_frames; ++j) {
//            if (frames[j] == pages[i]) {
//                counter++;
//                time[j] = counter;
//                flag1 = LRUflag2 = 1;
//                break;
//            }
//        }
//
//        if (flag1 == 0) {
//            for (j = 0; j < no_of_frames; ++j) {
//                if (frames[j] == -1) {
//                    counter++;
//                    faults++;
//                    frames[j] = pages[i];
//                    time[j] = counter;
//                    LRUflag2 = 1;
//                    break;
//                }
//            }
//        }
//
//        if (LRUflag2 == 0) {
//            pos = findLRU(time, no_of_frames);
//            counter++;
//            faults++;
//            frames[pos] = pages[i];
//            time[pos] = counter;
//        }
//
//        printf("\n");
//
//        for (j = 0; j < no_of_frames; ++j) {
//            printf("%d\t", frames[j]);
//        }
//    }
//
//    printf("\nTotal Page Faults = %d\n", faults);
//}
//
//// Function to find LRU
//int findLRU(int time[], int n) {
//    int i, minimum = time[0], pos = 0;
//
//    for (i = 1; i < n; ++i) {
//        if (time[i] < minimum) {
//            minimum = time[i];
//            pos = i;
//        }
//    }
//
//    return pos;
//}
//
//int main() {
//    int choice;
//    printf("Choose the Page Replacement Algorithm:\n");
//    printf("1. FIFO\n");
//    printf("2. LRU\n");
//    printf("Enter your choice (1 or 2): ");
//    scanf("%d", &choice);
//
//    switch (choice) {
//        case 1: {
//            int i, n, a[50], no;
//            printf("\nEnter the length of reference:\n");
//            scanf("%d", &n);
//            printf("\nEnter the page numbers:\n");
//            for (i = 1; i <= n; i++)
//                scanf("%d", &a[i]);
//            printf("\nEnter the number of frames:");
//            scanf("%d", &no);
//            fifo(n, a, no);
//            break;
//        }
//
//        case 2: {
//        	int i;
//            int no_of_frames, no_of_pages, pages[30];
//            printf("Enter number of frames: ");
//            scanf("%d", &no_of_frames);
//            printf("Enter number of pages: ");
//            scanf("%d", &no_of_pages);
//            printf("Enter reference string:\n");
//
//            for ( i = 0; i < no_of_pages; ++i) {
//                scanf("%d", &pages[i]);
//            }
//
//            lru(no_of_frames, no_of_pages, pages);
//            break;
//        }
//
//        default:
//            printf("Invalid choice\n");
//    }
//
//    return 0;
//}
//-----------------------------------------------------------------------------------------
//#include <stdio.h>
//
//// Function to implement LRU Page Replacement Algorithm
//void lru(int n, int str[], int nf) {
//    int i, k, timer = 1, time[5], pos = 0, min = 0, frame[nf], hit = 0, fault = 0;
//
//    // Initialize frame and time arrays
//    for (k = 0; k < nf; k++) {
//        frame[k] = -1;
//        time[k] = 0;
//    }
//
//    for (i = 1; i <= n; i++) {
//        int flag = 0;
//        for (k = 0; k < nf; k++) {
//            if (str[i] == frame[k]) { // page found
//                flag = 1;
//                time[k] = timer;
//                timer++;
//                hit++; // Increment page hit count
//                break;
//            }
//        }
//
//        if (flag == 0) { // page not found
//            fault++;
//            // Increment page fault count
//            int min_time = time[0];
//            pos = 0;
//            for (k = 1; k < nf; k++) {
//                if (time[k] < min_time) {
//                    min_time = time[k];
//                    pos = k;
//                }
//            }
//            frame[pos] = str[i];
//            time[pos] = timer;
//            timer++;
//        }
//    }
//
//    printf("Number of Page Faults: %d\n", fault);
//    printf("Number of Page Hits: %d\n", hit);
//}
//
//// Function to implement FIFO Page Replacement Algorithm
//void fifo(int n, int str[], int nf) {
//    int i, j = 0, k, frame[nf], flag, hit = 0, fault = 0;
//
//    // Initialize frame array
//    for (i = 0; i < nf; i++)
//        frame[i] = -1;
//
//    printf("\tRef String\tPage Frames\n");
//    for (i = 1; i <= n; i++) {
//        printf("%d\t\t", str[i]);
//        flag = 0;
//        for (k = 0; k < nf; k++) {
//            if (frame[k] == str[i]) {
//                flag = 1;
//                hit++;
//                break;
//            }
//        }
//        if (flag == 0) {
//            frame[j] = str[i];
//            j = (j + 1) % nf;
//            fault++;
//        }
//
//        // Display current page frames
//        for (k = 0; k < nf; k++) {
//            printf("%d\t", frame[k]);
//        }
//        printf("\n");
//    }
//    printf("Page Faults: %d\n", fault);
//    printf("Page Hits: %d\n", hit);
//}
//
//int main() {
//    int i, n, str[50], nf;
//
//    // Input the length of reference string
//    printf("\nEnter the length of reference string:\n");
//    scanf("%d", &n);
//
//    // Input the page numbers string
//    printf("\nEnter the page numbers string:\n");
//    for (i = 1; i <= n; i++)
//        scanf("%d", &str[i]);
//
//    // Input the number of frames
//    printf("\nEnter the number of frames:");
//    scanf("%d", &nf);
//
//    int choice;
//    printf("Choose the Page Replacement Algorithm:\n");
//    printf("1. FIFO\n");
//    printf("2. LRU\n");
//    printf("Enter your choice (1 or 2): ");
//    scanf("%d", &choice);
//
//    switch (choice) {
//        case 1:
//            fifo(n, str, nf);
//            break;
//
//        case 2:
//            lru(n, str, nf);
//            break;
//
//        default:
//            printf("Invalid choice\n");
//    }
//
//    return 0;
//}

