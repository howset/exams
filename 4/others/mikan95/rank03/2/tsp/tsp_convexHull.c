/*Key Differences
Shortest Closed Curve as stated in the problem:

A closed curve means the path starts and ends at the same point, forming a loop.
The curve must contain all given points, not necessarily visiting each point as part of the direct path.
So if the assignment refers to enclosing all points in a closed curve without visiting each directly,
a different algorithm (e.g., convex hull) is needed.

Shortest Path (TSP):
The traditional traveling salesman problem (TSP) ensures ALL points are visited exactly once
in the shortest distance, forming a closed loop.*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float x, y;
} Point;

// Function to calculate distance between two points
float distance(Point a, Point b) {
    return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Compare function for qsort (sorting by x, then by y)
int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x != p2->x)
        return (p1->x > p2->x) - (p1->x < p2->x);
    return (p1->y > p2->y) - (p1->y < p2->y);
}

// Cross product of vectors (p1p2 x p2p3)
float cross(Point p1, Point p2, Point p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

// Convex Hull using Graham's Scan
void convex_hull(Point *points, int n, Point *hull, int *hull_size) {
    qsort(points, n, sizeof(Point), compare);

    int k = 0;
    // Build lower hull
    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(hull[k - 2], hull[k - 1], points[i]) <= 0)
            k--;
        hull[k++] = points[i];
    }

    // Build upper hull
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && cross(hull[k - 2], hull[k - 1], points[i]) <= 0)
            k--;
        hull[k++] = points[i];
    }

    *hull_size = k - 1; // Last point is the same as the first
}

// Calculate the perimeter of the convex hull
float calculate_perimeter(Point *hull, int hull_size) {
    float perimeter = 0;
    for (int i = 0; i < hull_size; i++) {
        perimeter += distance(hull[i], hull[(i + 1) % hull_size]);
    }
    return perimeter;
}

int main() {
    FILE *input = stdin;
    Point points[100], hull[100];
    int n = 0, hull_size = 0;

    // Read input using fscanf
    while (fscanf(input, "%f, %f", &points[n].x, &points[n].y) == 2) {
        n++;
        if (n > 100) {
            fprintf(stderr, "Error: Too many points\n");
            return 1;
        }
    }

    if (n < 3) {
        fprintf(stderr, "Error: At least 3 points are required to form a closed curve\n");
        return 1;
    }

    // Compute convex hull
    convex_hull(points, n, hull, &hull_size);

    // Calculate and print the perimeter
    float perimeter = calculate_perimeter(hull, hull_size);
    fprintf(stdout, "%.2f\n", perimeter);

    return 0;
}

//to execute: gcc -Wall -Wextra -Werror tsp_convexHull.c -lm -o tsp_convexHull
// cat test_tsp/filename.txt | ./tsp_convexHull
