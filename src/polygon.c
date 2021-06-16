#include <stdio.h>
#include <stdlib.h>
#include "polygon.h"
#include "kdTree.h"

typedef struct polygonStruct{
    int edge;
    double *x;
    double *y;
    double center[2];
    double radiacao;
    
}PolygonStruct;

Polygon createPolygon(int edge, double *x, double*y, double radiacao){
    
    PolygonStruct *new = (PolygonStruct *) malloc(sizeof(PolygonStruct));

    new->edge = edge;
    new->radiacao = radiacao;
    new->x = (double *) malloc(edge * sizeof(double));
    new->y = (double *) malloc(edge * sizeof(double));

    for(int i = 0; i < edge; i++){
        new->x[i] = x[i];
        new->y[i] = y[i];
    }

    double A = 0;
    new->center[0] = 0;
    new->center[1] = 0;

    for(int i = 0; i < edge-1; i++){
        A += ((x[i]*y[i+1]) - (x[i+1]*y[i]));
        new->center[0] += (x[i]+x[i+1]) * ((x[i]*y[i+1]) - (x[i+1]*y[i]));
        new->center[1] += (y[i]+y[i+1]) * ((x[i]*y[i+1]) - (x[i+1]*y[i]));
    }

    A *= (1/2);
    new->center[0] *= (1/6*A);
    new->center[1] *= (1/6*A);

    return new;
}

void endAllPolygon(KdTree tree, NodeKdTree root){
    if(root == NULL){
        return;
    }
    
    endAllPolygon(tree, getKdNodeLeft(tree, root));
    endAllPolygon(tree, getKdNodeRight(tree, root));

    PolygonStruct *polygon = (PolygonStruct *) getKdTreeInfo(root);

    free(polygon->x);
    free(polygon->y);
    free(polygon);
}

double* getPolygonCenter(Polygon polygon){
    PolygonStruct *polygon_aux = (PolygonStruct *) polygon;

    return polygon_aux->center;
}

int isInsidePolygon(Polygon polygon, double x, double y){

    PolygonStruct *polygon_aux = (PolygonStruct*) polygon;
    int edge = polygon_aux->edge;

  int i, j, c = 0;
  for (i = 0, j = edge-1; i < edge; j = i++) {
    if ( ((polygon_aux->y[i]>y) != (polygon_aux->y[j]>y)) &&
	 (x < (polygon_aux->x[j]-polygon_aux->x[i]) * (y-polygon_aux->y[i]) / (polygon_aux->y[j]-polygon_aux->y[i]) + polygon_aux->x[i]) )
       c = !c;
  }
  return c;
}

double* getPolygonX(Polygon polygon){
    PolygonStruct* polygon_aux = (PolygonStruct *) polygon;
    
    return polygon_aux->x;
}

double* getPolygonY(Polygon polygon){
    PolygonStruct* polygon_aux = (PolygonStruct *) polygon;

    return polygon_aux->y;
}

int getPolygonEdge(Polygon polygon){
    PolygonStruct* polygon_aux = (PolygonStruct *) polygon;

    return polygon_aux->edge;
}

double getPolygonRadiacao(Polygon polygon){
    PolygonStruct *polygon_aux = (PolygonStruct *) polygon;

    return polygon_aux->radiacao;
}