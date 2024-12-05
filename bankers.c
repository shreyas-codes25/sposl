#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;

    // Input the number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    // Dynamically allocate memory for the matrices and arrays
    int **alloc = (int **)malloc(n * sizeof(int *));  // Allocation matrix
    int **max = (int **)malloc(n * sizeof(int *));    // Maximum matrix
    int **need = (int **)malloc(n * sizeof(int *));   // Need matrix
    int *avail = (int *)malloc(m * sizeof(int));      // Available resources
    int *f = (int *)malloc(n * sizeof(int));          // Finish flag array
    int *ans = (int *)malloc(n * sizeof(int));        // Safe sequence array
    int **avail_log = (int **)malloc((n + 1) * sizeof(int *)); // To store available resources at each step

    // Input allocation matrix
    printf("Enter the allocation matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        alloc[i] = (int *)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input maximum matrix
    printf("Enter the maximum matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        max[i] = (int *)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input available resources
    printf("Enter the available resources (%d):\n", m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Initialize finish array to 0
    for (int i = 0; i < n; i++) {
        f[i] = 0;
        avail_log[i] = (int *)malloc(m * sizeof(int));  // Allocate memory for each log
    }

    // Calculate the need matrix
    for (int i = 0; i < n; i++) {
        need[i] = (int *)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];  // Need = Max - Alloc
        }
    }

    // Banker's algorithm to find the safe sequence
    int ind = 0;  // Index to keep track of the sequence
    int count = 0;  // Number of processes finished
    int canAllocate;

    while (count < n) {
        canAllocate = 0;  // Flag to check if any process can be allocated resources

        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {  // Process not yet finished
                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;  // Resources not available
                        break;
                    }
                }

                if (flag == 0) {  // If all resources are available for the process
                    // Process can be safely allocated resources
                    ans[ind++] = i;

                    // Record available resources before allocation for logging
                    for (int y = 0; y < m; y++) {
                        avail_log[count][y] = avail[y];
                    }

                    for (int y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];  // Free the allocated resources
                    }
                    f[i] = 1;  // Mark process as finished
                    count++;
                    canAllocate = 1;  // Indicate that allocation was possible in this pass
                }
            }
        }

        if (!canAllocate) {
            // No process can be allocated resources, so break the loop
            printf("The given sequence is not safe.\n");
            return 0;
        }
    }

    // Display all matrices in a table format
    printf("\nProcess\t\tAllocation\tMax\t\tNeed\t\tAvailable\n");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t", i);  // Process label

        // Print Allocation matrix
        for (int j = 0; j < m; j++) {
            printf("%d ", alloc[i][j]);
        }
        printf("\t\t");

        // Print Max matrix
        for (int j = 0; j < m; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\t\t");

        // Print Need matrix
        for (int j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }

        // Print Available matrix
        printf("\t\t");
        for (int j = 0; j < m; j++) {
            printf("%d ", avail_log[i][j]);  // Log current available
        }

        printf("\n");
    }

    // Display all available resources after each step
    printf("\nAvailable Resources at Each Step:\n");
    for (int i = 0; i < count; i++) {
        printf("After executing P%d: ", ans[i]);
        for (int j = 0; j < m; j++) {
            printf("%d ", avail_log[i][j]);
        }
        printf("\n");
    }

    // If the system is in a safe state, print the safe sequence
    printf("\nFollowing is the SAFE Sequence:\n");
    for (int i = 0; i < n - 1; i++) {
        printf("P%d -> ", ans[i]);
    }
    printf("P%d\n", ans[n - 1]);

    // Free dynamically allocated memory
    for (int i = 0; i < n; i++) {
        free(alloc[i]);
        free(max[i]);
        free(need[i]);
        free(avail_log[i]);  // Freeing the log memory
    }
    free(alloc);
    free(max);
    free(need);
    free(avail);
    free(f);
    free(ans);
    free(avail_log);

    return 0;
}
