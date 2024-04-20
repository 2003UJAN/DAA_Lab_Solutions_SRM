#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Point;

// Global variable to store the bottommost point
Point p0;

// Swap two points
void swap(Point* a, Point* b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

// Calculate square of distance between two points
int distSq(Point p1, Point p2) {
    return (p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y);
}

// Orientation of triplet (p, q, r)
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0; // collinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// Comparator for qsort
int compare(const void* vp1, const void* vp2) {
    Point* p1 = (Point*)vp1;
    Point* p2 = (Point*)vp2;

    int orient = orientation(p0, *p1, *p2);
    if (orient == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;
    return (orient == 2) ? -1 : 1;
}

// Print convex hull points
void printHull(Point points[], int n) {
    // There must be at least 3 points
    if (n < 3) return;

    // Find the bottommost point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }

    // Place the bottom-most point at first position
    swap(&points[0], &points[min]);
    p0 = points[0];

    // Sort n-1 points with respect to the first point
    // The first point is already at index 0
    qsort(&points[1], n - 1, sizeof(Point), compare);

    // Initialize result
    Point hull[n];
    int m = 0; // Initialize size of the convex hull

    // Process sorted points one by one
    for (int i = 1; i < n; i++) {
        // Keep removing top while the angle formed by
        // points next-to-top, top, and points[i] makes
        // a non-left turn
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;

        hull[m] = points[i];
        m++; // Increment size of the convex hull
    }

    // Print Convex Hull
    printf("Convex Hull points:\n");
    for (int i = 0; i < m; i++)
        printf("(%d, %d)\n", hull[i].x, hull[i].y);
}
int main() {
    int n;
    printf("Enter the number of points: ");
    scanf("%d", &n);

    // Dynamic memory allocation for array of points
    Point *points = (Point*)malloc(n * sizeof(Point));
    if (points == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Input points
    printf("Enter the coordinates of each point (format: x y):\n");
    for (int i = 0; i < n; i++) {
        printf("Point %d: ", i + 1);
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    printHull(points, n);

    // Free allocated memory
    free(points);

    return 0;
}
	
