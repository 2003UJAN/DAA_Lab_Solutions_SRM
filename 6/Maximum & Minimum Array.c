#include <stdio.h>

void MaxMin(int i, int j, int *max, int *min, int a[]) {
    if (i == j) {
        // Single element in the array
        *max = *min = a[i];
    } else if (i == j - 1) {
        // Two elements in the array
        if (a[i] < a[j]) {
            *max = a[j];
            *min = a[i];
        } else {
            *max = a[i];
            *min = a[j];
        }
    } else {
        // More than two elements in the array, divide and conquer
        int mid = (i + j) / 2;
        int max1, min1;

        // Solve the subproblems
        MaxMin(i, mid, max, min, a);
        MaxMin(mid + 1, j, &max1, &min1, a);

        // Combine the solutions
        if (*max < max1) {
            *max = max1;
        }
        if (*min > min1) {
            *min = min1;
        }
    }
}

int main() {
    int i, n, max, min;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter the elements of the array:-\n");
    for (i = 0; i < n; i++) {
        printf("Enter element %d: ", i+1);
        scanf("%d", &a[i]);
    }

    MaxMin(0, n - 1, &max, &min, a);
    
    printf("Elements of array are: ");
    for (int i = 0; i < n; i++) 
        printf("%d ",a[i]);
    printf("\nMaximum element: %d\n", max);
    printf("\nMinimum element: %d\n", min);

    return 0;
}
