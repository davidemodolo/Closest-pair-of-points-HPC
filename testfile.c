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
    if (rank < remainder) {
        // Processes with rank less than remainder get one additional point
        start = rank * (points_per_proc + 1);
        end = start + points_per_proc;
    } else {
        // Processes with rank greater than or equal to remainder get the same number of points
        start = rank * points_per_proc + remainder;
        end = start + points_per_proc - 1;
    }

    // Allocate memory for the points that will be handled by this process
    Point* my_points = (Point*)malloc(points_per_proc * sizeof(Point));
    for (int i = 0; i < points_per_proc; i++) {
        my_points[i].coordinates = (double*)malloc(points[0].num_dimensions * sizeof(double));
    }

    // Scatter the points to the other processes
    MPI_Scatter(points, points_per_proc, MPI_DOUBLE, my_points, points_per_proc, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);

    // Calculate the distances between the points
    double* distances = (double*)malloc(points_per_proc * sizeof(double));
    for (int i = 0; i < points_per_proc; i++) {
        distances[i] = distance(points[start + i], points[end + 1]);
    }

    // Gather the distances to the root process
    double* all_distances = NULL;
    if (rank == ROOT) {
        all_distances = (double*)malloc(num_points * sizeof(double));
    }
    MPI_Gather(distances, points_per_proc, MPI_DOUBLE, all_distances, points_per_proc, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);

    // Print the distances to the root process
    if (rank == ROOT) {
        for (int i = 0; i < num_points; i++) {
            printf("%lf", all_distances[i]);
        }
    }

    MPI_Finalize();
    return 0;
}
