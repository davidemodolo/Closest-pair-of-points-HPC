#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROOT 0

// Structure for a point in any number of dimensions
typedef struct {
    double* coordinates;
    int num_dimensions;
} Point;

// Calculates the Euclidean distance between two points
double distance(Point p1, Point p2) {
    double sum = 0;
    for (int i = 0; i < p1.num_dimensions; i++) {
        sum += (p1.coordinates[i] - p2.coordinates[i]) * (p1.coordinates[i] - p2.coordinates[i]);
    }
    return sqrt(sum);
}

int main(int argc, char* argv[]) {
    int num_procs, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Read the points from the file (only done by root process)
    Point* points;
    int num_points;
    if (rank == ROOT) {
        // Open the file
        FILE* fp = fopen("points.txt", "r");
        if (fp == NULL) {
            perror("Error opening file");
            return 1;
        }

        // Read the number of points and dimensions from the first line of the file
        fscanf(fp, "%d %d", &num_points, &points[0].num_dimensions);

        // Allocate memory for the points
        points = (Point*)malloc(num_points * sizeof(Point));
        for (int i = 0; i < num_points; i++) {
            points[i].coordinates = (double*)malloc(points[0].num_dimensions * sizeof(double));
        }

        // Read the coordinates of the points from the file
        for (int i = 0; i < num_points; i++) {
            for (int j = 0; j < points[0].num_dimensions; j++) {
                fscanf(fp, "%lf", &points[i].coordinates[j]);
            }
        }

        // Close the file
        fclose(fp);
    }

    // Broadcast the number of points and dimensions to the other processes
    MPI_Bcast(&num_points, 1, MPI_INT, ROOT, MPI_COMM_WORLD);
    MPI_Bcast(&points[0].num_dimensions, 1, MPI_INT, ROOT, MPI_COMM_WORLD);

    // Determine the number of points each process will handle
    int points_per_proc = num_points / num_procs;
    int remainder = num_points % num_procs;
    int start, end;
    /*if (rank < remainder) {
        // Processes with rank less than remainder get one additional point
        start = rank * (points_per_proc +
    */