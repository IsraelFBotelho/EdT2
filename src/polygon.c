#include <stdio.h>
#include <stdlib.h>
#include "polygon.h"

typedef struct polygonStruct{
    double x[4];
    double y[4];
    double center[2];

    int radiacao;
    
}PolygonStruct;

Polygon createPolygon(double *x, double*y, double *center, int radiacao){
    
    PolygonStruct *new = (PolygonStruct *) malloc(sizeof(PolygonStruct));

    new->radiacao = radiacao;
    new->x[0] = x[0];
    new->y[0] = y[0];
    new->x[1] = x[1];
    new->y[1] = y[1];
    new->x[2] = x[2];
    new->y[2] = y[2];
    new->x[3] = x[3];
    new->y[3] = y[3];

    double A = 1/2 * ((x[0]*y[1] - x[1]*y[0]) + (x[1]*y[2] - x[2]*y[1]) + (x[2]*y[3] - x[3]*y[2]));

    new->center[0] = 1/(6*A) * (((x[0]+x[1]) * (x[0]*y[1] - x[1]*y[0])) + ((x[1]+x[2]) * (x[1]*y[2] - x[2]*y[1])) + ((x[2]+x[3]) * (x[2]*y[3] - x[3]*y[2])));
    new->center[1] = 1/(6*A) * (((y[0]+y[1]) * (x[0]*y[1] - x[1]*y[0])) + ((y[1]+y[2]) * (x[1]*y[2] - x[2]*y[1])) + ((y[2]+y[3]) * (x[2]*y[3] - x[3]*y[2])));

    return new;
}

int isInsidePolygon(Polygon polygon, double x, double y){
    PolygonStruct *polygon_aux = (PolygonStruct *) polygon;

    double x_polygon[4] = {polygon_aux->x[0], polygon_aux->x[1], polygon_aux->x[2], polygon_aux->x[3]};
    double y_polygon[4] = {polygon_aux->y[0], polygon_aux->y[1], polygon_aux->y[2], polygon_aux->y[3]}; 

    int i, j, c = 0;
    for (i = 0, j = 3; i < 4; j = i++) {
    if ( ((y_polygon[i]>y) != (y_polygon[j]>y)) &&
        (x < (x_polygon[j]-x_polygon[i]) * (y-y_polygon[i]) / (y_polygon[j]-y_polygon[i]) + x_polygon[i]) )
        c = !c;
    }
    return c;
}