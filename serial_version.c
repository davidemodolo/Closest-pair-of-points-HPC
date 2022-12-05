// import libraries
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

// struct for a point of n dimensions
typedef struct {
    int x;
    int y;
    int z;
    int w;
    int v;
} point;

// function to calculate the distance between two points of n dimensions
double distance(point *p1, point *p2){
    double sum = 0;
    sum += (p1->x - p2->x)*(p1->x - p2->x);
    sum += (p1->y - p2->y)*(p1->y - p2->y);
    sum += (p1->z - p2->z)*(p1->z - p2->z);
    sum += (p1->w - p2->w)*(p1->w - p2->w);
    sum += (p1->v - p2->v)*(p1->v - p2->v);
    return sqrt(sum);
}

int main(){
    // create M random points
    int M = 20000;
    point *points = (point *)malloc(M*sizeof(point));
    // set the seed for the random to time
    srand(time(NULL));
    // initialize M points
    for(int i=0; i<M; i++){
        points[i].x = rand() % 100;
        points[i].y = rand() % 100;
        points[i].z = rand() % 100;
        points[i].w = rand() % 100;
        points[i].v = rand() % 100;
    }
    // find the closest pair of points
    double min_dist = distance(&points[0], &points[1]);
    // save the index of the closest pair of points
    int index1 = 0;
    int index2 = 1;
    // keep the count of pairs with the same distance
    int count = 1;
    for(int i=0; i<M; i++){
        for(int j=i+1; j<M; j++){
            double dist = distance(&points[i], &points[j]);
            if(dist < min_dist && dist != 0.0){
                index1 = i;
                index2 = j;
                min_dist = dist;
                count = 1;
            }
            else if(dist == min_dist){
                count++;
            }
        }
    }

    // print the distance and the points
    printf("The closest pair of points is (%d, %d, %d, %d, %d) and (%d, %d, %d, %d, %d) with distance %f", points[index1].x, points[index1].y, points[index1].z, points[index1].w, points[index1].v, points[index2].x, points[index2].y, points[index2].z, points[index2].w, points[index2].v, min_dist);
    printf("\nWe have %d pairs with the same distance", count);
    // keep the terminal open
    getchar();

    // free the memory
    free(points);


    return 0;
}
